/**
  * @file ntc.h
  * @brief NTC temperature sensor driver head file
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2025/08/26
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
  * 	2025/08/26	0.1			Leon Lee		Preliminary version.
  */

#ifndef __NTC_H__
#define __NTC_H__

#include <stdint.h>
#include "RTE_Components.h"
#include CMSIS_device_header

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

int ntc_temp_calc(float *temp_celsius, uint16_t adc_value, uint8_t adc_bits);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __NTC_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
