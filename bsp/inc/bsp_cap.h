/**
  * @file bsp_cap.h
  * @brief 
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2025/08/14
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
  * 	2025/08/14	0.1			Leon Lee		Preliminary version.
  */

#ifndef __BSP_CAP_H__
#define __BSP_CAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum
{
    CAP_CH1 = 0,
    CAP_CH2,
    CAP_CHn
};

int bsp_cap_init(uint8_t ch, TIM_HandleTypeDef* htim, uint32_t tim_channel);
int bsp_cap_start(uint8_t ch);
int bsp_cap_stop(uint8_t ch);
uint32_t bsp_cap_get_count(uint8_t ch);
uint32_t bsp_cap_get_freq(uint8_t ch);

void CAP_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void bsp_cap_period_elapsed_callback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_CAP_H__ */

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
