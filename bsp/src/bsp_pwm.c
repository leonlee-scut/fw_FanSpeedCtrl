/**
  * @file bsp_pwm.c 
  * @brief 
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2025/08/11
  * 
  * @copyright Copyright (c) 2025 South China University of Technology.
  * All rights reserved.
  * 
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * 
  * @par History:
  * 	Date		Version		Author			Description
  * 	2025/08/11	0.1			Leon Lee		Preliminary version.
  */

#include "bsp.h"
#include "bsp_pwm.h"


static uint32_t __duty_cycle = 0;               // PWM duty cycle in percentage
static uint32_t __frequency = 0;                // PWM carrier frequency in Hz
static uint32_t __period = 0;                   // PWM period in timer counts
static TIM_HandleTypeDef* __pwm_timer;
static uint32_t __oc_channel = TIM_CHANNEL_1;   // Output Compare channel for PWM


/**
  * @brief Initialize the PWM with the specified timer and output compare channel.
  *
  * This function initializes the PWM by configuring the timer and setting the
  * output compare channel. It calculates the frequency based on the timer's
  * prescaler and period.
  *
  * @param[in] htim Pointer to the TIM_HandleTypeDef structure that contains
  *                 the configuration information for the specified timer.
  * @param[in] OC_Channel The output compare channel to be used for PWM.
  * @return 0 on success, negative on failure
  */
int bsp_pwm_init(TIM_HandleTypeDef* htim,  uint32_t OC_Channel)
{
    assert(htim != NULL);
    assert(OC_Channel == TIM_CHANNEL_1 || OC_Channel == TIM_CHANNEL_2 ||
           OC_Channel == TIM_CHANNEL_3 || OC_Channel == TIM_CHANNEL_4); 

    __pwm_timer = htim;
    __oc_channel = OC_Channel;
    __frequency = HAL_RCC_GetPCLK1Freq();           // Get peripheral clock frequency
    __period = __pwm_timer->Init.Period;
    __frequency /= __period + 1;                    // Calculate frequency from period
    __frequency /= __pwm_timer->Init.Prescaler + 1; // Adjust frequency by prescaler

    bsp_pwm_set_duty_cycle(0);                          // Initialize duty cycle to 0
    bsp_pwm_stop();                                     // Ensure PWM is stopped initially
    
    return 0;
}   


/**
  * @brief Start PWM output.
  *
  * This function starts the PWM output by starting the timer and enabling the
  * PWM output on channel 1.
  *
  * @return 0 on success, negative on failure
  */
int bsp_pwm_start(void)
{
    HAL_TIM_Base_Start(__pwm_timer);
    HAL_TIM_PWM_Start(__pwm_timer, __oc_channel);   // Start PWM on specified channel
    return 0;
}


/**
  * @brief Stop PWM output.
  *
  * This function stops the PWM output by stopping the timer and disabling the
  * PWM output on channel 1.
  *
  * @return 0 on success
  */
int bsp_pwm_stop(void)
{
    HAL_TIM_PWM_Stop(__pwm_timer, __oc_channel);    // Stop PWM on specified channel
    HAL_TIM_Base_Stop(__pwm_timer);
    return 0;
}


/**
  * @brief Set the duty cycle of the PWM output.
  *
  * This function sets the duty cycle of the PWM output as a percentage of the
  * period. The duty cycle should be in the range 0 to 100. The internal
  * representation of the duty cycle is the number of timer counts that the output
  * is high within the period.
  *
  * @param[in] duty_cycle Duty cycle as a percentage of the period
  * @return 0 on success, negative on failure
  */
int bsp_pwm_set_duty_cycle(uint32_t duty_cycle)
{
    __duty_cycle = (duty_cycle > 100) ? 100 : duty_cycle;
    WRITE_REG(__pwm_timer->Instance->CCR1, __duty_cycle * (__period + 1) / 100);

    return 0;
}


/**
  * @brief Get the current duty cycle of the PWM output.
  *
  * This function returns the current duty cycle of the PWM output as a percentage
  * of the period. The duty cycle represents the fraction of the period during
  * which the PWM output is high.
  *
  * @return Current duty cycle as a percentage of the period.
  */

uint32_t bsp_pwm_get_duty_cycle(void)
{
    return __duty_cycle;
}


/**
  * @brief Get the current frequency of the PWM output.
  *
  * This function returns the current frequency of the PWM output in hertz (Hz).
  * The frequency is determined based on the timer configuration including
  * the timer period and prescaler. It represents the carrier frequency of the
  * PWM signal.
  *
  * @return Current frequency in hertz (Hz).
  */

uint32_t bsp_pwm_get_frequency(void)
{
    return __frequency;
}


/**
  * @brief Get the current status of the PWM output.
  *
  * This function returns the current status of the PWM output, indicating whether
  * it is running or stopped. The status is determined based on the timer state
  * and whether the timer is enabled.
  *
  * @return Current status of the PWM output (PWM_STATUS_RUNNING or PWM_STATUS_STOPPED).
  */
PWM_StatusTypeDef bsp_pwm_get_status(void)
{
    if (HAL_TIM_Base_GetState(__pwm_timer) == HAL_TIM_STATE_BUSY &&
        HAL_TIM_GetChannelState(__pwm_timer, __oc_channel) == HAL_TIM_CHANNEL_STATE_BUSY)
    {
        return PWM_STATUS_RUNNING;                  // PWM is running
    }

    return PWM_STATUS_STOPPED;
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
