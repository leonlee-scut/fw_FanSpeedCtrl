/**
  * @file bsp_pwm.h 
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


#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#include <stdint.h>
#include "RTE_Components.h"
#include CMSIS_device_header

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

typedef enum {
    PWM_STATUS_STOPPED,
    PWM_STATUS_RUNNING
} PWM_StatusTypeDef;

int pwm_init(TIM_HandleTypeDef* htim, uint32_t OC_Channel);
int pwm_start(void);
int pwm_stop(void);
int pwm_set_duty_cycle(uint32_t duty_cycle);
uint32_t pwm_get_duty_cycle(void);
uint32_t pwm_get_frequency(void);
PWM_StatusTypeDef pwm_get_status(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __BSP_PWM_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
