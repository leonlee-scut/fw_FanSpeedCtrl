/**
  * @file bsp_gpio.h
  * @brief GPIO driver header file
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

#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "RTE_Components.h"
#include CMSIS_device_header
#include "PinNames.h"
#include "PortNames.h"

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

#define pinReset(pin)       pinWrite(pin, GPIO_PIN_RESET)
#define pinSet(pin)         pinWrite(pin, GPIO_PIN_SET)

#define pinRESET(pin)       pinWrite(pin, GPIO_PIN_RESET)
#define pinSET(pin)         pinWrite(pin, GPIO_PIN_SET)

#define pinLow(pin)         pinWrite(pin, GPIO_PIN_RESET)
#define pinHigh(pin)        pinWrite(pin, GPIO_PIN_SET)

#define pinLOW(pin)         pinWrite(pin, GPIO_PIN_RESET)
#define pinHIGH(pin)        pinWrite(pin, GPIO_PIN_SET)

/**
  * @brief Get GPIO port from PinName
  * 
  * @param pin Pin name of a GPIO pin 
  * @return GPIO_TypeDef* GPIO Port
  */
__STATIC_INLINE GPIO_TypeDef *GPIOx(PinName pin)
{
    uint32_t port_reg_size = 0x0400;
    uint32_t portNmu = (pin & 0xF0) >> 4;

    return (GPIO_TypeDef *)(GPIOA_BASE + port_reg_size * portNmu);
}

/**
  * @brief Get pin number from PinName
  * 
  * @param pin Pin name of a GPIO pin 
  * @return int 
  */
__STATIC_INLINE uint8_t pinNum(PinName pin)
{
    return pin & 0x0F;
}

/**
  * @brief Configure port pin
  * 
  * @param pin Pin name of the GPIO pin
  * @param conf GPIO_CONF
  * @param mode GPIO_MODE
  * @return true  - success
  * @return false - error
  */
// __STATIC_INLINE bool pinConfigure(PinName pin, GPIO_CONF conf, GPIO_MODE mode)
// {
//     return GPIO_PinConfigure(GPIOx(pin), pinNum(pin), conf, mode);
// }

/**
  * @brief Write a GPIO pin by PinName
  * 
  * @param pin PinName
  * @param val Value (0 or 1)
  */
__STATIC_INLINE void pinWrite(PinName pin, uint32_t val)
{
    GPIO_TypeDef *port = GPIOx(pin);
    uint32_t pinBit = 1UL << pinNum(pin);
    port->BSRR = pinBit << (val != GPIO_PIN_RESET ? 0 : 16);
}


/**
  * @brief Read a GPIO pin by PinName
  * 
  * @param pin PinName
  * @return pin value (0 or 1) 
  */
__STATIC_INLINE uint32_t pinRead(PinName pin)
{
    GPIO_TypeDef *port = GPIOx(pin);
    uint32_t pinBit = 1UL << pinNum(pin);
    
    return port->IDR & pinBit ? GPIO_PIN_SET : GPIO_PIN_RESET;
}


/**
  * @brief Toggle a GPIO pin by PinName
  * 
  * @param pin PinName
  */
__STATIC_INLINE void pinToggle(PinName pin)
{
    GPIOx(pin)->ODR ^= 1UL << pinNum(pin);
}


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __BSP_GPIO_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
