/**
  * @file bsp.h
  * @brief Board Support Package header file
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/06/02
  * 
  * @copyright Copyright (c) 2024 South China University of Technology.
  * All rights reserved.
  * 
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * 
  * @par History:
  * 	Date		Version		Author			Description
  * 	2024/06/02	0.1			Leon Lee		Preliminary version.
  */

#ifndef __BSP_H__
#define __BSP_H__

#include <stdbool.h>
#include "RTE_Components.h"
#include CMSIS_device_header
#include "MX_Device.h"
#include "bsp_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

// Configuration 
// GPIO for output
#define LED_RED                     PA_11
#define LED_GREEN                   PA_12
#define LED1                        LED_RED
#define LED2                        LED_GREEN

// GPIO for input
 
// I2C interface
#define I2C1_SCL                    PA_9
#define I2C1_SDA                    PA_10 

// SPI1 interface
// #define SPI1_SCK                    PB_3
// #define SPI1_MISO                   PB_4
// #define SPI1_MOSI                   PB_5
// #define SPI1_NSS                    PA_15

// SPI2 interface
// #define SPI2_SCK                    PB_8
// #define SPI2_MISO                   PB_6
// #define SPI2_MOSI                   PB_7
// #define SPI2_NSS                    PB_9

// USART1 interface
#define USART1_TX                   PB_6
#define USART1_RX                   PB_7

// USART2 interface
#define USART2_TX                   PA_2
#define USART2_RX                   PA_3

// Re-target UART
#define DEBUG_USART                 &huart1
#define COMM_USART                  &huart2

// External ADC Trigger Timer
// #define EXT_ADC_TRIG_TIMER_HANDLE   &htim16
// #define EXT_ADC_TRIG_TIMER          TIM16
// #define USER_TIM_PRESCALER          128
// #define USER_TIM_PERIOD             62500

// Marcos
#define LED_ON(led)                 pinSet(led)
#define LED_OFF(led)                pinReset(led)
#define LED_TOGGLE(led)             pinToggle(led)

#define LED_on(led)                 pinSet(led)
#define LED_off(led)                pinReset(led)
#define LED_toggle(led)             pinToggle(led)


// extern SPI_HandleTypeDef    hspi1;
// extern SPI_HandleTypeDef    hspi2;
// extern TIM_HandleTypeDef    htim16;
// extern CRC_HandleTypeDef    hcrc;

extern UART_HandleTypeDef   huart1;
extern UART_HandleTypeDef   huart2;
extern I2C_HandleTypeDef    hi2c1;
extern ADC_HandleTypeDef    hadc1;
extern DMA_HandleTypeDef    hdma_adc1;

void bsp_init(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __BSP_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
