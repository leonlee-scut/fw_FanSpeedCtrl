/**
  * @file fan.h
  * @brief 4-wire PWM Fan driver head file
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2025/08/27
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
  * 	2025/08/27	0.1			Leon Lee		Preliminary version.
  */

#ifndef __FAN_H__
#define __FAN_H__

#include <stdint.h>

#define FAN_CURVE_TSTART_DEFAULT  30      // Default start temperature in Celsius
#define FAN_CURVE_TMIN_DEFAULT    35      // Default minimum temperature in Celsius
#define FAN_CURVE_TMAX_DEFAULT    75      // Default maximum temperature in Celsius
#define FAN_CURVE_DMIN_DEFAULT    30      // Default minimum duty cycle in percentage

#define FAN_SET_CURVE_DEFAULT()   fan_set_curve(FAN_CURVE_TSTART_DEFAULT,\
                                                FAN_CURVE_TMIN_DEFAULT, \
                                                FAN_CURVE_TMAX_DEFAULT,\
                                                FAN_CURVE_DMIN_DEFAULT)

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

typedef struct fan
{
    uint16_t frequency;     // Current frequency in Hz
    uint16_t speed;         // Current speed in RPM
    uint16_t mag_per_rev;   // Magnetic poles per revolution
}FAN_TypeDef;

typedef struct 
{
    uint8_t T_start;    // TSTART为风扇开始转动时的温度
    uint8_t T_min;      // TMIN为占空比开始从DMIN增大时的对应温度
    uint8_t T_max;      // TMAX为占空比达到100%时的对应温度
    uint8_t D_min;      // DMIN为最低占空比，单位%
} FAN_Curv_TypeDef;

void fan_setup(FAN_TypeDef* fan, uint16_t mag_per_rev);
void fan_set_frequency(FAN_TypeDef* fan, uint16_t frequency);
uint16_t fan_get_speed(FAN_TypeDef* fan);
void fan_set_speed(FAN_TypeDef* fan, float temp_celsius);

void fan_set_curve(uint8_t T_start, uint8_t T_min, uint8_t T_max, uint8_t D_min);
void fan_get_curve(uint8_t* T_start, uint8_t* T_min, uint8_t* T_max, uint8_t* D_min);

FAN_Curv_TypeDef* fan_get_curve_ptr(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __FAN_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
