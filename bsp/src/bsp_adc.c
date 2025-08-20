/**
  * @file bsp_adc.cpp
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

#include "bsp.h"


ADC_HandleTypeDef *__adc;
DMA_HandleTypeDef *__adc_dma;
TIM_HandleTypeDef *__adc_trig_timer;

static uint16_t __adc_buffer[ADC_CHn] = {0};

static void __clear_adc_buffer(void)
{
    for (int i = ADC_CH1; i < ADC_CHn; i++)
    {
        __adc_buffer[i] = 0;
    }
}

int bsp_adc_init(ADC_HandleTypeDef* hadc, DMA_HandleTypeDef* hdma, TIM_HandleTypeDef* htim)
{
    assert(hadc != NULL);
    assert(hdma != NULL);
    assert(htim != NULL);

    __adc = hadc;
    __adc_dma = hdma;
    __adc_trig_timer = htim;

    // Clear the ADC buffer
    __clear_adc_buffer();

    // Start ADC Calibration
    if (HAL_ADCEx_Calibration_Start(__adc) != HAL_OK)
    {
        // Calibration Error
        return -1;
    }  

    return 0;
}


void bsp_adc_start(void)
{
    // Clear the ADC buffer
    __clear_adc_buffer();
    
    // Setup ADC DMA and start ADC in DMA mode
    HAL_ADC_Start_DMA(__adc, (uint32_t*)__adc_buffer, ADC_CHANNELS);

    // Start the ADC trigger timer
    HAL_TIM_Base_Start(__adc_trig_timer);
}


void bsp_adc_stop(void)
{
    // Stop the ADC trigger timer
    HAL_TIM_Base_Stop(__adc_trig_timer);

    // Stop the ADC
    HAL_ADC_Stop_DMA(__adc);
}


uint16_t bsp_adc_read_raw(uint8_t chn)
{
    assert(chn < ADC_CHn);
    return __adc_buffer[chn];
}


__WEAK void bsp_adc_complete_callback(uint32_t* pData, uint32_t length)
{
    UNUSED(pData);
    UNUSED(length); 
    // User can override this function to handle ADC conversion complete event
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == __adc)
    {
        bsp_adc_complete_callback((uint32_t*)__adc_buffer, ADC_CHANNELS);
    }
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
