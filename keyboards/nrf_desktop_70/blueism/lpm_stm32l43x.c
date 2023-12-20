// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "usb_util.h"
#include "lpm_stm32l43x.h"
#include "usb_main.h"
#include "uart.h"
#include "config_blueism.h"
#include "hid_leds.h"
#include "debounce.h"
#include "wireless_sys.h"
#include "outputselect.h"

#define BOARD_PM

#ifdef BOARD_PM

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

extern matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t empty_matrix[MATRIX_ROWS] = {0};

static bool     lpm_time_up = false;
static uint32_t lpm_timer_buffer;

static pm_t        power_mode = PM_RUN;
static inline void stm32_clock_fast_init(void);

// extern host_driver_t chibios_driver;

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

static inline void enter_low_power_mode_prepare(void) {
    usbStop(&USBD1);
    usbDisconnectBus(&USBD1);
    PWR->CR2 &= ~PWR_CR2_USV;

    /* Enable key matrix wake up */
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            // setPinInputHigh(row_pins[x]);
            palEnableLineEvent(row_pins[x], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }

    for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
        setPinOutput(col_pins[i]);
        writePinLow(col_pins[i]);
    }

    // palEnableLineEvent(VBUS_DETECT_PIN, PAL_EVENT_MODE_BOTH_EDGES);

#    ifdef HIDS_LEDS_ENABLE
    disable_leds_cb();
#    endif
}

static inline void lpm_wakeup(void) {
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
    stInit();
    timer_init();
    chSysUnlock();

    if (readPin(VBUS_DETECT_PIN)) {
        PWR->CR2 |= PWR_CR2_USV;
        usb_start(&USBD1);
        usbConnectBus(&USBD1); // this fixes caps lock
        wait_ms(500);  //Do need to wait here, or "usb_connected_state" will be false.
        if(usb_connected_state()){
            set_output(OUTPUT_USB);
        }
    }
    /* Disable all wake up pins */
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            palDisableLineEvent(row_pins[x]);
        }
    }

    // palDisableLineEvent(VBUS_DETECT_PIN);

#    ifdef HIDS_LEDS_ENABLE
    enable_leds_cb();
#    endif

    // if (usb_connected_state()) {
    // if (readPin(VBUS_DETECT_PIN)) {

    // chSysLock();
    // hsi48_init();
    // chSysUnlock();
    // hsi48_init();
    /* Remove USB isolation.*/
    // PWR->CR2 |= PWR_CR2_USV; /* PWR_CR2_USV is available on STM32L4x2xx and STM32L4x3xx devices only. */
    // usb_power_connect();
    // PWR->CR2 |= PWR_CR2_USV;
    // usbStart(&USBD1);
    // usb_start(&USBD1);
    // _usb_wakeup(&USBD1);

    // clear_keyboard();
    // restart_usb_driver(&USBD1);
    // _usb_wakeup(&USBD1);
    // usb_start(&USBD1);
    // wait_ms(15);
    // }

    // hsi48_init();
    // PWR->CR2 |= PWR_CR2_USV;
    // // host_set_driver(&chibios_driver);
    //     usb_start(&USBD1);

    // 不要用这个选项,会导致usb卡键
    //  restart_usb_driver(&USBD1);

    // uart_init(z)
    sdInit();
    SerialConfig config = {115200, 0, 0, 0};
    sdStart(&SERIAL_DRIVER, &config);

    // wait_ms(1);
}

void enter_power_mode(pm_t mode) {
    if (!lpm_set(mode)) {
        return;
    }
    enter_low_power_mode_prepare();

    __WFI();

    lpm_wakeup();
    lpm_timer_reset();

    debounce_free();
    matrix_init();
    power_mode = PM_RUN;
}

void enter_power_mode_stop1(void) {
    if (!lpm_set(PM_STOP1)) {
        return;
    }
    enter_low_power_mode_prepare();

    __WFI();

    lpm_wakeup();
    // lpm_timer_reset();
    pm_reset();
    debounce_free();
    matrix_init();
    power_mode = PM_RUN;
}

void enter_power_mode_sleep(void) {
    if (!lpm_set(PM_SLEEP)) {
        return;
    }
    enter_low_power_mode_prepare();

    __WFI();

    lpm_wakeup();
    // lpm_timer_reset();
    pm_reset();
    debounce_free();
    matrix_init();
    power_mode = PM_RUN;
}

void stm32_clock_fast_init(void) {
#    if !STM32_NO_INIT
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
#        if STM32_SAI2SEL != STM32_SAI2SEL_OFF
        ccipr |= STM32_SAI2SEL;
#        endif
#        if STM32_SAI1SEL != STM32_SAI1SEL_OFF
        ccipr |= STM32_SAI1SEL;
#        endif
        RCC->CCIPR = ccipr;
    }

    /* Set flash WS's for SYSCLK source */
    if (STM32_FLASHBITS > STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }

    /* Switching to the configured SYSCLK source if it is different from MSI.*/
#        if (STM32_SW != STM32_SW_MSI)
    RCC->CFGR |= STM32_SW; /* Switches on the selected clock source.   */
    /* Wait until SYSCLK is stable.*/
    while ((RCC->CFGR & RCC_CFGR_SWS) != (STM32_SW << 2))
        ;
#        endif

    /* Reduce the flash WS's for SYSCLK source if they are less than MSI WSs */
    if (STM32_FLASHBITS < STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }
#    endif /* STM32_NO_INIT */
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

static inline bool lpm_any_matrix_action(void) {
    return memcmp(matrix, empty_matrix, sizeof(empty_matrix));
}

void lpm_task(void) {
    // if (readPin(VBUS_DETECT_PIN)) {
    //     lpm_timer_stop();
    //     return;
    // }

    if (!lpm_time_up && sync_timer_elapsed32(lpm_timer_buffer) > 1000) {
        lpm_time_up      = true;
        lpm_timer_buffer = 0;
    }

    if (!readPin(VBUS_DETECT_PIN) && readPin(CAPS_LED_PIN) && lpm_time_up && !lpm_any_matrix_action()) {
        // lpm_timer_reset();  //解决usb插入后拔出，键盘卡死的问题,未解决
        enter_power_mode_stop1();
    }
}

// void housekeeping_task_kb(void) {
//     lpm_task();
//     // auto_low_power();
//     // if (!lpm_time_up&& last_input_activity_elapsed() > 1000) {
//     //     lpm_time_up      = true;
//     //     enter_power_mode_stop1();w
//     // }
//     housekeeping_task_user();
//     //

//     // if (readPin(VBUS_DETECT_PIN)) {
//     //     lpm_timer_stop();
//     //     return;
//     // }

//     // if (!lpm_time_up && sync_timer_elapsed32(lpm_timer_buffer) > 1000) {
//     //     lpm_time_up      = true;
//     //     enter_power_mode_stop1();
//     // }

//     // if (!readPin(VBUS_DETECT_PIN) && readPin(CAPS_LED_PIN) && lpm_time_up && !lpm_any_matrix_action()) {
//     //     enter_power_mode_stop1();
//     // }
// }

static uint32_t pm_timer;

void pm_reset(void) {
    pm_timer = timer_read32();
}

void housekeeping_task_kb(void) {
    // output_scan();
    if (timer_elapsed32(pm_timer) >= 1500) // check if lpm has already timeout and if enough time has passed
    {
        pm_timer = timer_read32();
        // // 如果满足pm条件，进入pm
        // if (!readPin(VBUS_DETECT_PIN) && readPin(CAPS_LED_PIN) && !lpm_any_matrix_action()) {
        //     enter_power_mode_stop1();
        // } else {
        //     // pm_reset();
        // }
        // if(usb_connected_state()) return;

        if (!readPin(VBUS_DETECT_PIN) && readPin(CAPS_LED_PIN) && !lpm_any_matrix_action()) {
            enter_power_mode_stop1();
        }
    }
}

// void palCallback_vbus_reset_full(void *arg) {
//     // if (readPin(VBUS_DETECT_PIN)) {
//         soft_reset_keyboard();
// }

// void palCallback_vbus_reset(void *arg) {
//     // if (readPin(VBUS_DETECT_PIN)) {
//         // soft_reset_keyboard();
//     // }

//     palEnableLineEvent(VBUS_DETECT_PIN, PAL_EVENT_MODE_RISING_EDGE);
//     palSetLineCallback(VBUS_DETECT_PIN, palCallback_vbus_reset_full, NULL);

// }

// void vbus_reset(void) {
//     palEnableLineEvent(VBUS_DETECT_PIN, PAL_EVENT_MODE_FALLING_EDGE );
//     palSetLineCallback(VBUS_DETECT_PIN, palCallback_vbus_reset, NULL);
// }

#endif
