/**
  * @file iir_filter.c
  * @brief 
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

#include "iir_filter.h"


/**
  * @brief Initialize the IIR filter structure
  * @param[in] filter Pointer to the IIR filter structure
  * @param[in] coeff_shift The shift value for the filter coefficients
  * @param[in] coeff_shift_max The maximum shift value for the filter coefficients
  * @param[in] feedforward_value The feedforward value for the filter
  */
void iir_filter_init(IIR_FILTER_t* filter, uint16_t coeff_shift, uint16_t coeff_shift_max, int32_t feedforward_value)
{
    filter->coeff_shift = coeff_shift;
    filter->coeff_shift_max = coeff_shift_max;
    filter->feedforward_value = feedforward_value;
    filter->filtered_value = 0;
}

/**
  * @brief Apply the IIR filter to the value
  * @param[in] filter Pointer to the IIR filter structure
  * @param[in] value The value to be filtered
  * @return The filtered value
  *
  * This function applies the IIR filter to the given value. The IIR filter
  * is a low-pass filter. The output of the filter is the filtered value.
  *
  * The IIR filter is defined by the following difference equation:
  *   y[n] = x[n] + (x[n-1] - y[n-1]) >> coeff_shift
  * where x[n] is the input value at time n, y[n] is the output value at time n,
  * x[n-1] is the input value at time n-1, y[n-1] is the output value at time n-1,
  * and coeff_shift is the shift value for the filter coefficients.
  *
  * The filtered value is rounded to the nearest integer by adding the
  * carry bit from the multiplication to the result.
  *
  * For more information on the IIR filter please refer to Cypress application
  * note AN2099.
  */
int32_t iir_filter(IIR_FILTER_t* filter, int32_t value)
{
    int32_t filValueRounded;

    value <<= filter->coeff_shift_max;

    // Check if the value is outside the range of the feedforward value
    // and the filtered value
    if ((value > (filter->filtered_value + filter->feedforward_value)) || 
        (value < (filter->filtered_value - filter->feedforward_value))) 
    {
        // If the value is outside the range, set the filtered value to the
        // input value
        filter->filtered_value = value;
    }
    else
    {
        // If the value is inside the range, apply the IIR filter to the
        // input value
        filter->filtered_value += (value - filter->filtered_value) >> filter->coeff_shift;
    }

    // Round the filtered value to the nearest integer
    filValueRounded = (filter->filtered_value >> filter->coeff_shift_max) 
                    + ((filter->filtered_value & 0x80uL) >> (filter->coeff_shift_max - 1));
    return filValueRounded;
}


/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
