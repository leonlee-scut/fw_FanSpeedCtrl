/**
  * @file bsp_cap.c
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

#include "bsp.h"
#include "bsp_cap.h"

typedef struct 
{
    uint32_t count;
    uint32_t frequency;
    uint32_t channel;
    TIM_HandleTypeDef* htim;
} CAP_TypeDef;

CAP_TypeDef __cap[CAP_CHn] = {0};


int bsp_cap_init(uint8_t ch, TIM_HandleTypeDef* htim, uint32_t tim_channel)
{
    assert(ch < CAP_CHn);
    assert(htim != NULL);
    assert(tim_channel == CAP_CH1_TIM_CHANNEL || tim_channel == CAP_CH2_TIM_CHANNEL);

    __cap[ch].htim = htim;
    __cap[ch].channel = tim_channel;

    return 0;
}

int bsp_cap_start(uint8_t ch)
{
    assert(ch < CAP_CHn);
    __cap[ch].count = 0;
    __cap[ch].frequency = 0;

    HAL_TIM_Base_Start_IT(__cap[ch].htim);
    HAL_TIM_IC_Start_IT(__cap[ch].htim, __cap[ch].channel);

    return 0;
}

int bsp_cap_stop(uint8_t ch)
{
    assert(ch < CAP_CHn);
    HAL_TIM_IC_Stop_IT(__cap[ch].htim, __cap[ch].channel);

    return 0;
}


uint32_t bsp_cap_get_count(uint8_t ch)
{
    assert(ch < CAP_CHn);

    return __cap[ch].count;
}


uint32_t bsp_cap_get_freq(uint8_t ch)
{
    assert(ch < CAP_CHn);

    return __cap[ch].frequency;
}

__WEAK void bsp_cap_period_elapsed_callback(TIM_HandleTypeDef* htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);

    /* NOTE : This function should not be modified. When the callback is needed,
              function bsp_cap_period_elapsed_callback must be implemented in the user file.
    */
}


__STATIC_INLINE void __cap_reset_count(uint8_t ch)
{
    __cap[ch].frequency = __cap[ch].count;
    __cap[ch].count = 0;
}


__STATIC_INLINE void __cap_inc_count(uint8_t ch)
{
    uint32_t value = __HAL_TIM_GET_COMPARE(__cap[ch].htim, __cap[ch].channel);
    __cap[ch].count++;
}


void CAP_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint8_t i;
    for (i = CAP_CH1; i < CAP_CHn; i++)
    {
        if (htim == __cap[i].htim)
        {
            __cap_reset_count(i);
        }
    }

    bsp_cap_period_elapsed_callback(htim);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    uint8_t i;
    for (i = CAP_CH1; i < CAP_CHn; i++)
    {
        if (htim == __cap[i].htim)
        {
            if (htim->Channel == __cap[i].channel)
            {
                __cap_inc_count(i);
                break;
            }
        }
    }
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
