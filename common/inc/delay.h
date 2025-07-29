/**
  * @file delay.h
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

#ifndef __DELAY_H__
#define __DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

#include <stdint.h>

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __DELAY_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
