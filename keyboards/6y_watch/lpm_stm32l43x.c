// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "leds.h"
#include "usb_util.h"
#include "lpm_stm32l43x.h"
#include "usb_main.h"
#include "debounce.h"
#include "vbus.h"
#include "ch455x.h"
#include "display.h"

// pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
// pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

// extern matrix_row_t matrix[MATRIX_ROWS];
// static matrix_row_t empty_matrix[MATRIX_ROWS] = {0};

static bool     lpm_time_up = false;
static uint32_t lpm_timer_buffer;

static pm_t power_mode = PM_RUN;
static void stm32_clock_fast_init(void);

bool lpm_set(pm_t mode) {
    switch (mode) {
        case PM_SLEEP:
            /* Wake source: Any interrupt or event */
            if (power_mode != PM_RUN) return false;

            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            break;
        case PM_STOP1:
            if (power_mode != PM_RUN) {
                return false;
            }
            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STOP1;
            break;
        default:
            return false;
    }
    return true;
}

static void enter_low_power_mode_prepare(void) {
    usbStop(&USBD1);
    usbDisconnectBus(&USBD1);
    PWR->CR2 &= ~PWR_CR2_USV;

    /* Enable key matrix wake up */
    // for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    //     if (row_pins[x] != NO_PIN) {
    //         // setPinInputHigh(row_pins[x]);
    //         palEnableLineEvent(row_pins[x], PAL_EVENT_MODE_BOTH_EDGES);
    //     }
    // }

    // for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
    //     setPinOutput(col_pins[i]);
    //     writePinLow(col_pins[i]);
    // }
}

static void lpm_wakeup(void) {
    chSysLock();
    // stm32_clock_init();
    // hsi48_init();

    // 为了修复via的问题，只能用这个
    stm32_clock_fast_init();
    chSysUnlock();
    chSysLock();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    PWR->SCR |= PWR_SCR_CWUF;
    PWR->SCR |= PWR_SCR_CSBF;
    // PWR->CR2 |= PWR_CR2_USV; /* PWR_CR2_USV is available on STM32L4x2xx and STM32L4x3xx devices only. */
    // usb_wakeup(&USBD1);
    // usb_start(&USBD1);
    // init_usb_driver(&USBD1);
    // restart_usb_driver(&USBD1);
    /* TIMx is disable during stop/standby/sleep mode, init after wakeup */
    // stInit();
    timer_init();
    chSysUnlock();

    // if (readPin(VBUS_DETECT_PIN)) {
        PWR->CR2 |= PWR_CR2_USV;
        usb_start(&USBD1);
        usbConnectBus(&USBD1); // this fixes caps lock
        // wait_ms(500);          // Do need to wait here, or "usb_connected_state" will be false.
        // if (usb_connected_state()) {
        //     set_output(OUTPUT_USB);
        // }
    // }
    /* Disable all wake up pins */
    // for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    //     if (row_pins[x] != NO_PIN) {
    //         palDisableLineEvent(row_pins[x]);
    //     }
    // }

    ch455x_wakeup();
}

void enter_power_mode_stop1(void) {
    if (!lpm_set(PM_STOP1)) {
        return;
    }
    enter_low_power_mode_prepare();

    lpm_timer_stop();

    __WFI();

    lpm_wakeup();
    lpm_timer_reset();
    // pm_reset();
    // debounce_free();
    // matrix_init();
    power_mode = PM_RUN;
}

void stm32_clock_fast_init(void) {
#if !STM32_NO_INIT
    /* Clocks setup.*/
    msi_init();   // 6.x us
    hsi16_init(); // 4.x us
    hsi48_init();

    /* PLLs activation, if required.*/
    pll_init();
    pllsai1_init();
    pllsai2_init();
    /* clang-format off */
    /* Other clock-related settings (dividers, MCO etc).*/
  RCC->CFGR = STM32_MCOPRE | STM32_MCOSEL | STM32_STOPWUCK |
              STM32_PPRE2  | STM32_PPRE1  | STM32_HPRE;
    /* CCIPR register initialization, note, must take care of the _OFF
       pseudo settings.*/
    {
    uint32_t ccipr = STM32_DFSDMSEL  | STM32_SWPMI1SEL | STM32_ADCSEL    |
                     STM32_CLK48SEL  | STM32_LPTIM2SEL | STM32_LPTIM1SEL |
                     STM32_I2C3SEL   | STM32_I2C2SEL   | STM32_I2C1SEL   |
                     STM32_UART5SEL  | STM32_UART4SEL  | STM32_USART3SEL |
                     STM32_USART2SEL | STM32_USART1SEL | STM32_LPUART1SEL;
/* clang-format on */
#    if STM32_SAI2SEL != STM32_SAI2SEL_OFF
        ccipr |= STM32_SAI2SEL;
#    endif
#    if STM32_SAI1SEL != STM32_SAI1SEL_OFF
        ccipr |= STM32_SAI1SEL;
#    endif
        RCC->CCIPR = ccipr;
    }

    /* Set flash WS's for SYSCLK source */
    if (STM32_FLASHBITS > STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }

    /* Switching to the configured SYSCLK source if it is different from MSI.*/
#    if (STM32_SW != STM32_SW_MSI)
    RCC->CFGR |= STM32_SW; /* Switches on the selected clock source.   */
    /* Wait until SYSCLK is stable.*/
    while ((RCC->CFGR & RCC_CFGR_SWS) != (STM32_SW << 2))
        ;
#    endif

    /* Reduce the flash WS's for SYSCLK source if they are less than MSI WSs */
    if (STM32_FLASHBITS < STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }
#endif /* STM32_NO_INIT */
}

void lpm_init(void) {
    lpm_timer_reset();
}

void lpm_timer_reset(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = sync_timer_read32();
}

void lpm_timer_stop(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = 0;
}

// static bool lpm_any_matrix_action(void) {
//     return memcmp(matrix, empty_matrix, sizeof(empty_matrix));
// }

void housekeeping_task_kb(void) {
    if (!lpm_time_up && sync_timer_elapsed32(lpm_timer_buffer) > 10000) {
        lpm_time_up      = true;
        lpm_timer_buffer = 0;
    }

    if (!readPin(VBUS_DETECT_PIN) && lpm_time_up && get_current_display_mode() != FUTURE_CALLI_MODE_SYMBOL) {
        ch455x_sleep();
        leds_all_off();
        enter_power_mode_stop1();
    }
    // if (!lpm_any_matrix_action() && lpm_time_up) {
    //     ch455x_sleep();
    //     enter_power_mode_stop1();
    // }
}
