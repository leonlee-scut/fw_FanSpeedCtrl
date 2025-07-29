/**
  * @file PinNames.h
  * @brief Pins name define head file for STM32G070KBTx device
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/06/02
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
  * 	2024/06/02	0.1			Leon Lee		Preliminary version.
  */

#ifndef __PINNAMES_H__
#define __PINNAMES_H__   
typedef enum {
    PA_0       = 0x00,
    PA_1       = 0x01,
    PA_2       = 0x02,
    PA_3       = 0x03,
    PA_4       = 0x04,
    PA_5       = 0x05,
    PA_6       = 0x06,
    PA_7       = 0x07,
    PA_8       = 0x08,
    PA_9       = 0x09,
    PA_10      = 0x0A,
    PA_11      = 0x0B,
    PA_12      = 0x0C,
    PA_13      = 0x0D,
    PA_14      = 0x0E,
    PA_15      = 0x0F,
    PB_0       = 0x10,
    PB_1       = 0x11,
    PB_2       = 0x12,
    PB_3       = 0x13,
    PB_4       = 0x14,
    PB_5       = 0x15,
    PB_6       = 0x16,
    PB_7       = 0x17,
    PB_8       = 0x18,
    PB_9       = 0x19,
    // PB_10      = 0x1A,
    // PB_11      = 0x1B,
    // PB_12      = 0x1C,
    // PB_13      = 0x1D,
    // PB_14      = 0x1E,
    // PB_15      = 0x1F,
    PC_6       = 0x26,
    // PC_13      = 0x2D,
    PC_14      = 0x2E,
    PC_15      = 0x2F,
    // PD_0       = 0x30,
    // PD_1       = 0x31,
    // PH_0       = 0x70,
    // PH_1       = 0x71,
    /**** ADC internal channels ****/

    // ADC_TEMP = 0xF0, // Internal pin virtual value
    // ADC_VREF = 0xF1, // Internal pin virtual value

    // STDIO for console print

    /**** USB pins ****/
    // USB_DM = PA_11,
    // USB_DP = PA_12,

    /**** OSCILLATOR pins ****/
    RCC_OSC32_IN = PC_14,
    RCC_OSC32_OUT = PC_15,
    // RCC_OSC_IN = PH_0,
    // RCC_OSC_OUT = PH_1,

    /**** DEBUG pins ****/
    SYS_JTCK_SWCLK = PA_14,
    // SYS_JTDI = PA_15,
    // SYS_JTDO_TRACESWO = PB_3,
    SYS_JTMS_SWDIO = PA_13,
    // SYS_NJTRST = PB_4,
    SYS_WKUP = PA_0,

    // Not connected
    // NC = (int)0xFFFFFFFF
} PinName;

#endif /* __PINNAMES_H__ */

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
