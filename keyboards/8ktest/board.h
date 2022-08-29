/*
    ChibiOS - Copyright (C) 2006..2020 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

// #ifndef BOARD_H
// #define BOARD_H

#include_next <board.h>

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

// #define BOARD_OTG_NOVBUSSENS
#define BOARD_OTG2_USES_ULPI

/*
 * IO pins assignments.
 */
// #define GPIOA_USB_OTG_HS_D0                  3U
// #define GPIOA_USB_OTG_HS_CK                   5U

// #define GPIOB_USB_OTG_HS_D1                  0U
// #define GPIOB_USB_OTG_HS_D2                  1U
// #define GPIOB_USB_OTG_HS_D7                  5U
// #define GPIOB_USB_OTG_HS_D3                10U
// #define GPIOB_USB_OTG_HS_D4                 11U
// #define GPIOB_USB_OTG_HS_D5                 12U
// #define GPIOB_USB_OTG_HS_D6                 13U

// #define GPIOC_USB_OTG_HS_STP       0U
// #define GPIOC_USB_OTG_HS_DIR                  2U
// #define GPIOC_USB_OTG_HS_NXT               3U

#define GPIOA_BUTTON                0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_USB_OTG_HS_D0                  3U
#define GPIOA_LRCK                  4U
#define GPIOA_USB_OTG_HS_CK                   5U
#define GPIOA_SDO                   6U
#define GPIOA_SDI                   7U
#define GPIOA_PIN8                  8U
#define GPIOA_VBUS_FS               9U
#define GPIOA_OTG_FS_ID             10U
#define GPIOA_OTG_FS_DM             11U
#define GPIOA_OTG_FS_DP             12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_USB_OTG_HS_D1                  0U
#define GPIOB_USB_OTG_HS_D2                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_SWO                   3U
#define GPIOB_PIN4                  4U
#define GPIOB_USB_OTG_HS_D7                  5U
#define GPIOB_SCL                   6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_SDA                   9U
#define GPIOB_USB_OTG_HS_D3                10U
#define GPIOB_USB_OTG_HS_D4                 11U
#define GPIOB_USB_OTG_HS_D5                 12U
#define GPIOB_USB_OTG_HS_D6                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_PIN15                 15U

#define GPIOC_USB_OTG_HS_STP       0U
#define GPIOC_PIN1                  1U
#define GPIOC_USB_OTG_HS_DIR                  2U
#define GPIOC_USB_OTG_HS_NXT               3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_MCLK                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_SCLK                  10U
#define GPIOC_PIN11                 11U
#define GPIOC_SDIN                  12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/



/*
 * GPIOA setup:
 *
 * PA0  - BUTTON                    (input floating).
 * PA1  - PIN1                      (input pullup).
 * PA2  - PIN2                      (input pullup).
 * PA3  - PIN3                      (input pullup).
 * PA4  - LRCK                      (alternate 6).
 * PA5  - SPC                       (alternate 5).
 * PA6  - SDO                       (alternate 5).
 * PA7  - SDI                       (alternate 5).
 * PA8  - PIN8                      (input pullup).
 * PA9  - VBUS_FS                   (input floating).
 * PA10 - OTG_FS_ID                 (alternate 10).
 * PA11 - OTG_FS_DM                 (alternate 10).
 * PA12 - OTG_FS_DP                 (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - PIN15                     (input pullup).
 */


#undef VAL_GPIOA_MODER
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_BUTTON) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN2) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_OTG_HS_D0) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_LRCK) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_OTG_HS_CK) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_SDO) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_SDI) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOA_VBUS_FS) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_ID) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DP) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_PIN15))
                                     
#undef VAL_GPIOA_OTYPER                                    
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_BUTTON) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_OTG_HS_D0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LRCK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_OTG_HS_CK) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SDO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SDI) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_VBUS_FS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_ID) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DM) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DP) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
                                  
#undef VAL_GPIOA_OSPEEDR                                 
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_BUTTON) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOA_USB_OTG_HS_D0) |          \
                                     PIN_OSPEED_HIGH(GPIOA_LRCK) |          \
                                     PIN_OSPEED_HIGH(GPIOA_USB_OTG_HS_CK) |         \
                                     PIN_OSPEED_MEDIUM(GPIOA_SDO) |         \
                                     PIN_OSPEED_MEDIUM(GPIOA_SDI) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOA_VBUS_FS) |       \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_ID) |     \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DM) |     \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DP) |     \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN15))
                                    

#undef VAL_GPIOA_PUPDR                                     
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_BUTTON) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_OTG_HS_D0) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_LRCK) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_USB_OTG_HS_CK) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_SDO) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_SDI) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_VBUS_FS) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_ID) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DM) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DP) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN15))
 #undef VAL_GPIOA_ODR                                        
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_BUTTON) |           \
                                     PIN_ODR_HIGH(GPIOA_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOA_USB_OTG_HS_D0) |             \
                                     PIN_ODR_HIGH(GPIOA_LRCK) |             \
                                     PIN_ODR_HIGH(GPIOA_USB_OTG_HS_CK) |              \
                                     PIN_ODR_HIGH(GPIOA_SDO) |              \
                                     PIN_ODR_HIGH(GPIOA_SDI) |              \
                                     PIN_ODR_HIGH(GPIOA_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOA_VBUS_FS) |          \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_ID) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DM) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DP) |        \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_PIN15))
    #undef     VAL_GPIOA_AFRL                            
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_BUTTON, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_USB_OTG_HS_D0, 10U) |          \
                                     PIN_AFIO_AF(GPIOA_LRCK, 6U) |          \
                                     PIN_AFIO_AF(GPIOA_USB_OTG_HS_CK, 10U) |           \
                                     PIN_AFIO_AF(GPIOA_SDO, 5U) |           \
                                     PIN_AFIO_AF(GPIOA_SDI, 5U))
      #undef     VAL_GPIOA_AFRH                                  
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_VBUS_FS, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_ID, 10U) |    \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DM, 10U) |    \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DP, 10U) |    \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (input pullup).
 * PB1  - PIN1                      (input pullup).
 * PB2  - PIN2                      (input pullup).
 * PB3  - SWO                       (alternate 0).
 * PB4  - PIN4                      (input pullup).
 * PB5  - PIN5                      (input pullup).
 * PB6  - SCL                       (alternate 4).
 * PB7  - PIN7                      (input pullup).
 * PB8  - PIN8                      (input pullup).
 * PB9  - SDA                       (alternate 4).
 * PB10 - CLK_IN                    (input pullup).
 * PB11 - PIN11                     (input pullup).
 * PB12 - PIN12                     (input pullup).
 * PB13 - PIN13                     (input pullup).
 * PB14 - PIN14                     (input pullup).
 * PB15 - PIN15                     (input pullup).
 */
#undef VAL_GPIOB_MODER 
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D1) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D2) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D7) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SCL) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SDA) |        \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D3) |         \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D4) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D5) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D6) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN15))
                                     
                                     #undef VAL_GPIOB_OTYPER 
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D7) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_SCL) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_SDA) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D4) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D5) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D6) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN15))

                                     #undef VAL_GPIOB_OSPEEDR 
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D1) |          \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D2) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOB_SWO) |           \
                                     PIN_OSPEED_HIGH(GPIOB_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D7) |          \
                                     PIN_OSPEED_HIGH(GPIOB_SCL) |           \
                                     PIN_OSPEED_HIGH(GPIOB_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOB_SDA) |           \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D3) |        \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D4) |         \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D5) |         \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D6) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN15))

                                     #undef VAL_GPIOB_PUPDR 
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D1) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D2) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_SWO) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_USB_OTG_HS_D7) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_SCL) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_SDA) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D3) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D4) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D5) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D6) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN15))

                                     #undef VAL_GPIOB_ODR 
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D1) |             \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D2) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D7) |             \
                                     PIN_ODR_HIGH(GPIOB_SCL) |              \
                                     PIN_ODR_HIGH(GPIOB_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOB_SDA) |              \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D3) |           \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D4) |            \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D5) |            \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D6) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN15))

                                     #undef VAL_GPIOB_AFRL 
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_USB_OTG_HS_D1, 10U) |          \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D2, 10U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_SWO, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D7, 10U) |          \
                                     PIN_AFIO_AF(GPIOB_SCL, 4U) |           \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0U))

                                     #undef VAL_GPIOB_AFRH 
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_SDA, 4U) |           \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D3, 10U) |        \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D4, 10U) |         \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D5, 10U) |         \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D6, 10U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN15, 0U))

/*
 * GPIOC setup:
 *
 * PC0  - OTG_FS_POWER_ON           (output pushpull maximum).
 * PC1  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - PDM_OUT                   (input pullup).
 * PC4  - PIN4                      (input pullup).
 * PC5  - PIN5                      (input pullup).
 * PC6  - PIN6                      (input pullup).
 * PC7  - MCLK                      (alternate 6).
 * PC8  - PIN8                      (input pullup).
 * PC9  - PIN9                      (input pullup).
 * PC10 - SCLK                      (alternate 6).
 * PC11 - PIN11                     (input pullup).
 * PC12 - SDIN                      (alternate 6).
 * PC13 - PIN13                     (input pullup).
 * PC14 - PIN14                     (input pullup).
 * PC15 - PIN15                     (input pullup).
 */

#undef VAL_GPIOC_MODER
#define VAL_GPIOC_MODER             (PIN_MODE_ALTERNATE(GPIOC_USB_OTG_HS_STP) |\
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_USB_OTG_HS_DIR) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_USB_OTG_HS_NXT) |        \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_MCLK) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_SCLK) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIN) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN15))

                                     #undef VAL_GPIOC_OTYPER
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_USB_OTG_HS_STP) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_USB_OTG_HS_DIR) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_USB_OTG_HS_NXT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MCLK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SCLK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIN) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))

                                     #undef VAL_GPIOC_OSPEEDR
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_USB_OTG_HS_STP) |\
                                     PIN_OSPEED_HIGH(GPIOC_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOC_USB_OTG_HS_DIR) |          \
                                     PIN_OSPEED_HIGH(GPIOC_USB_OTG_HS_NXT) |       \
                                     PIN_OSPEED_HIGH(GPIOC_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOC_MCLK) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOC_SCLK) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOC_SDIN) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN15))

                                     #undef VAL_GPIOC_PUPDR
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_USB_OTG_HS_STP) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_USB_OTG_HS_DIR) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_USB_OTG_HS_NXT) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_MCLK) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_SCLK) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIN) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN15))

                                     #undef VAL_GPIOC_ODR
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_USB_OTG_HS_STP) |  \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOC_USB_OTG_HS_DIR) |             \
                                     PIN_ODR_HIGH(GPIOC_USB_OTG_HS_NXT) |          \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOC_MCLK) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOC_SCLK) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOC_SDIN) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN15))

                                     #undef VAL_GPIOC_AFRL
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_USB_OTG_HS_STP, 10U) |\
                                     PIN_AFIO_AF(GPIOC_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_USB_OTG_HS_DIR, 10U) |          \
                                     PIN_AFIO_AF(GPIOC_USB_OTG_HS_NXT, 10U) |       \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_MCLK, 6U))

                                     #undef VAL_GPIOC_AFRH
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_SCLK, 6U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_SDIN, 6U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))

// #endif /* BOARD_H */
