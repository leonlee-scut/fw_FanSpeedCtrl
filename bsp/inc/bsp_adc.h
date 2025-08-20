/**
  * @file bsp_adc.h
  * @brief 
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2025/08/16
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
  * 	2025/08/16	0.1			Leon Lee		Preliminary version.
  */

#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include <stdint.h>
#include "RTE_Components.h"
#include CMSIS_device_header

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

enum
{
    ADC_CH1 = 0,
    ADC_CH2,
    ADC_CH3,
    ADC_CH4,
    ADC_CH5,
    ADC_CH6,
    ADC_CH7,
    ADC_CH8,
    ADC_CHn
};

int bsp_adc_init(ADC_HandleTypeDef* hadc, DMA_HandleTypeDef* hdma, TIM_HandleTypeDef* htim);
void bsp_adc_start(void);
void bsp_adc_stop(void);
uint16_t bsp_adc_read_raw(uint8_t chn);

void bsp_adc_complete_callback(uint32_t *pData, uint32_t length);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __BSP_ADC_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
