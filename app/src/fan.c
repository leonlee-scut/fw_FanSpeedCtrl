/**
  * @file fan.c
  * @brief 4-wire PWM Fan driver source file
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

#include "bsp.h"
#include "fan.h"
#include "assert.h"

/**
  * @brief 
  * 
  */
static FAN_Curv_TypeDef __fan_curve = {
    .T_start = FAN_CURVE_TSTART_DEFAULT, // Start temperature in Celsius 
    .T_min = FAN_CURVE_TMIN_DEFAULT,     // Minimum temperature in Celsius
    .T_max = FAN_CURVE_TMAX_DEFAULT,     // Maximum temperature in Celsius
    .D_min = FAN_CURVE_DMIN_DEFAULT      // Minimum duty cycle in percentage
};


/**
  * @brief Setup a FAN instance
  * 
  * Initialize a FAN instance with a given magnetic pole count per revolution.
  * 
  * @param[in] fan The FAN instance to be initialized
  * @param[in] mag_per_rev The number of magnetic poles per revolution
  * 
  */
void fan_setup(FAN_TypeDef* fan, uint16_t mag_per_rev)
{
    assert(fan != NULL);
    assert(mag_per_rev > 0);
    
    fan->frequency = 0;
    fan->speed = 0;
    fan->mag_per_rev = mag_per_rev;
}


/**
  * @brief Set the frequency of the fan
  * 
  * Set the frequency of the fan and calculate the speed of the fan in RPM.
  * 
  * @param[in] fan The FAN instance
  * @param[in] frequency The frequency of the fan in Hz
  */
void fan_set_frequency(FAN_TypeDef* fan, uint16_t frequency)
{
    assert(fan != NULL);
    
    fan->frequency = frequency;
    fan->speed = (frequency * 60) / fan->mag_per_rev;
}


/**
  * @brief Get the current speed of the fan
  * 
  * Get the current speed of the fan in RPM.
  * 
  * @param[in] fan The FAN instance
  * 
  * @return The current speed of the fan in RPM
  */
uint16_t fan_get_speed(FAN_TypeDef* fan)
{
    assert(fan != NULL);
    
    return fan->speed;
}

/**
  * @brief Set the speed of the fan based on temperature
  * 
  * Set the speed of the fan based on the given temperature in Celsius.
  * The speed is determined by the fan curve defined by T_start, T_min, T_max, and D_min.
  * 
  * @param[in] fan The FAN instance
  * @param[in] temp_celsius The temperature in Celsius
  */
void fan_set_speed(FAN_TypeDef* fan, float temp_celsius)
{
    assert(fan != NULL);
    
    uint8_t duty_cycle;

    if (temp_celsius < __fan_curve.T_start) 
    {
        duty_cycle = 0;
    }
    else if (temp_celsius <= __fan_curve.T_min) 
    {
        duty_cycle = __fan_curve.D_min;
    } 
    else if (temp_celsius >= __fan_curve.T_max) 
    {
        duty_cycle = 100;
    } 
    else 
    {
        duty_cycle = __fan_curve.D_min + 
                    (uint8_t)((100 - __fan_curve.D_min) * 
                              (temp_celsius - __fan_curve.T_min) / 
                              (__fan_curve.T_max - __fan_curve.T_min));
    }

    // Set the PWM duty cycle here
    // Example: pwm_set_duty_cycle(duty_cycle);
    bsp_pwm_set_duty_cycle((uint32_t)duty_cycle);
}


/**
  * @brief Set the fan curve
  * 
  * Set the fan curve using the given parameters.
  * The fan curve is defined by four parameters:
  * - T_start: The temperature in Celsius below which the fan is turned off
  * - T_min: The temperature in Celsius above which the fan starts to spin and at which the fan runs at the minimum speed
  * - T_max: The temperature in Celsius above which the fan runs at the maximum speed
  * - D_min: The minimum duty cycle in percentage that the fan should be running at above T_min
  * 
  * @param[in] T_start The temperature in Celsius below which the fan is turned off
  * @param[in] T_min The temperature in Celsius above which the fan starts to spin and at which the fan runs at the minimum speed
  * @param[in] T_max The temperature in Celsius above which the fan runs at the maximum speed
  * @param[in] D_min The minimum duty cycle in percentage that the fan should be running at above T_min
  */
void fan_set_curve(uint8_t T_start, uint8_t T_min, uint8_t T_max, uint8_t D_min)
{
    assert(T_start < T_min && T_min < T_max);
    assert(D_min <= 100);

    __fan_curve.T_start = T_start;
    __fan_curve.T_min = T_min;
    __fan_curve.T_max = T_max;
    __fan_curve.D_min = D_min;
}

/**
  * @brief Get the fan curve
  * 
  * Get the current fan curve parameters.
  * 
  * @param[out] T_start The temperature in Celsius below which the fan is turned off
  * @param[out] T_min The temperature in Celsius above which the fan starts to spin and at which the fan runs at the minimum speed
  * @param[out] T_max The temperature in Celsius above which the fan runs at the maximum speed
  * @param[out] D_min The minimum duty cycle in percentage that the fan should be running at above T_min
  */
void fan_get_curve(uint8_t* T_start, uint8_t* T_min, uint8_t* T_max, uint8_t* D_min)
{
    assert(T_start != NULL && T_min != NULL && T_max != NULL && D_min != NULL);

    *T_start = __fan_curve.T_start;
    *T_min = __fan_curve.T_min;
    *T_max = __fan_curve.T_max;
    *D_min = __fan_curve.D_min;
}

/**
  * @brief Get the fan curve pointer
  * 
  * Get the pointer to the fan curve structure.
  * 
  * @return The pointer to the fan curve structure
  */
FAN_Curv_TypeDef* fan_get_curve_ptr(void)
{
    return &__fan_curve;
}


/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
