/**
  * @file iir_filter.h
  * @brief IIR filter function head file
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/08/30
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
  * 	2024/08/30	0.1			Leon Lee		Preliminary version.
  */

#ifndef __IIR_FILTER_H__
#define __IIR_FILTER_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

typedef struct 
{
    uint16_t coeff_shift;
    uint16_t coeff_shift_max;
    int32_t feedforward_value;
    int32_t filtered_value;
} IIR_FILTER_t;

void iir_filter_init(IIR_FILTER_t *filter, uint16_t coeff_shift, uint16_t coeff_shift_max, int32_t feedforward_value);
int32_t iir_filter(IIR_FILTER_t *filter, int32_t value);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __IIR_FILTER_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
