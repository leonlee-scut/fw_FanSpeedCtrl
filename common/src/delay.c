/**
  * @file delay.c
  * @brief Delay function for STM32Fxxx 32-bit MCU
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/08/28
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
  * 	2024/08/28	0.1			Leon Lee		Preliminary version.
  */

#include "RTE_Components.h"
#include CMSIS_device_header
#include "cmsis_os2.h"
#include "delay.h"


/**
  * @brief Delay for microseconds
  * @param us: delay duration in microseconds
  * @author Leon Lee (leonlee.scut@gmail.com)
  */
void delay_us(uint32_t us)
{
    uint32_t start_time;
    __IO uint32_t current_time;
    uint32_t delay_time;

    // Get the current time
    start_time = SysTick->VAL;

    // Calculate the delay time
    delay_time = us * (SystemCoreClock / 1000000);

    // Wait until the delay time is reached
    do
    {
        current_time = SysTick->VAL;
    } while ((start_time - current_time) < delay_time);
}

/**
 * @brief Delay for milliseconds
 * @param ms: delay duration in milliseconds
 * @author Leon Lee (leonlee.scut@gmail.com)
 */
void delay_ms(uint32_t ms)
{
    if (osKernelGetState() == osKernelRunning)
    {
        osDelay(ms);
    }
    else
    {
        HAL_Delay(ms);
    }
}
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/

