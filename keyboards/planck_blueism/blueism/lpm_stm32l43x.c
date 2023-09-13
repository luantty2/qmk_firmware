// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "lpm_stm32l43x.h"
#include "usb_main.h"
#include "uart.h"

pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static pm_t        power_mode = PM_RUN;
static inline void stm32_clock_fast_init(void);

bool lpm_set(pm_t mode) {
    switch (mode) {
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
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            palEnableLineEvent(col_pins[x], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
}

static inline void lpm_wakeup(void) {
    chSysLock();
    // stm32_clock_init();
    stm32_clock_fast_init();
    chSysUnlock();
    chSysLock();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    PWR->SCR |= PWR_SCR_CWUF;
    PWR->SCR |= PWR_SCR_CSBF;
    /* TIMx is disable during stop/standby/sleep mode, init after wakeup */
    stInit();
    timer_init();
    chSysUnlock();
    /* Disable all wake up pins */
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            palDisableLineEvent(col_pins[x]);
        }
    }

    // hsi48_init();
    // PWR->CR2 |= PWR_CR2_USV;
    restart_usb_driver(&USBD1);
    // uart_init(z)
    sdInit();
    SerialConfig config = {115200, 0, 0, 0};
    sdStart(&SERIAL_DRIVER, &config);
    power_mode = PM_RUN;
}

void enter_power_mode(pm_t mode) {
    if (!lpm_set(mode)) {
        return;
    }
    enter_low_power_mode_prepare();

    __WFI();

    lpm_wakeup();
}

void enter_power_mode_stop1(void) {
    if (!lpm_set(PM_STOP1)) {
        return;
    }
    enter_low_power_mode_prepare();

    __WFI();

    lpm_wakeup();
}

void stm32_clock_fast_init(void) {
#if !STM32_NO_INIT
    /* Clocks setup.*/
    msi_init();   // 6.x us
    hsi16_init(); // 4.x us

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
