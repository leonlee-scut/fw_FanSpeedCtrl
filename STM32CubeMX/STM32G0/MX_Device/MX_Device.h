/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 25/07/2025 22:37:58
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated with a generator out of the
 *               STM32CubeMX project and its generated files (DO NOT EDIT!)
 ******************************************************************************/

#ifndef MX_DEVICE_H__
#define MX_DEVICE_H__

/* MX_Device.h version */
#define MX_DEVICE_VERSION                       0x01000000


/*------------------------------ I2C1           -----------------------------*/
#define MX_I2C1                                 1

/* Filter Settings */
#define MX_I2C1_ANF_ENABLE                      1
#define MX_I2C1_DNF                             0

/* Peripheral Clock Frequency */
#define MX_I2C1_PERIPH_CLOCK_FREQ               64000000

/* Pins */

/* I2C1_SCL */
#define MX_I2C1_SCL_Pin                         PA9
#define MX_I2C1_SCL_GPIO_Pin                    GPIO_PIN_9
#define MX_I2C1_SCL_GPIOx                       GPIOA
#define MX_I2C1_SCL_GPIO_Mode                   GPIO_MODE_AF_OD
#define MX_I2C1_SCL_GPIO_PuPd                   GPIO_NOPULL
#define MX_I2C1_SCL_GPIO_Speed                  GPIO_SPEED_FREQ_LOW
#define MX_I2C1_SCL_GPIO_AF                     GPIO_AF6_I2C1

/* I2C1_SDA */
#define MX_I2C1_SDA_Pin                         PA10
#define MX_I2C1_SDA_GPIO_Pin                    GPIO_PIN_10
#define MX_I2C1_SDA_GPIOx                       GPIOA
#define MX_I2C1_SDA_GPIO_Mode                   GPIO_MODE_AF_OD
#define MX_I2C1_SDA_GPIO_PuPd                   GPIO_NOPULL
#define MX_I2C1_SDA_GPIO_Speed                  GPIO_SPEED_FREQ_LOW
#define MX_I2C1_SDA_GPIO_AF                     GPIO_AF6_I2C1

/*------------------------------ USART1         -----------------------------*/
#define MX_USART1                               1

/* Virtual mode */
#define MX_USART1_VM                            VM_ASYNC
#define MX_USART1_VM_ASYNC                      1

/* Pins */

/* USART1_RX */
#define MX_USART1_RX_Pin                        PB7
#define MX_USART1_RX_GPIO_Pin                   GPIO_PIN_7
#define MX_USART1_RX_GPIOx                      GPIOB
#define MX_USART1_RX_GPIO_Mode                  GPIO_MODE_AF_PP
#define MX_USART1_RX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART1_RX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART1_RX_GPIO_AF                    GPIO_AF0_USART1

/* USART1_TX */
#define MX_USART1_TX_Pin                        PB6
#define MX_USART1_TX_GPIO_Pin                   GPIO_PIN_6
#define MX_USART1_TX_GPIOx                      GPIOB
#define MX_USART1_TX_GPIO_Mode                  GPIO_MODE_AF_PP
#define MX_USART1_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART1_TX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART1_TX_GPIO_AF                    GPIO_AF0_USART1

/*------------------------------ USART2         -----------------------------*/
#define MX_USART2                               1

/* Virtual mode */
#define MX_USART2_VM                            VM_ASYNC
#define MX_USART2_VM_ASYNC                      1

/* Pins */

/* USART2_RX */
#define MX_USART2_RX_Pin                        PA3
#define MX_USART2_RX_GPIO_Pin                   GPIO_PIN_3
#define MX_USART2_RX_GPIOx                      GPIOA
#define MX_USART2_RX_GPIO_Mode                  GPIO_MODE_AF_PP
#define MX_USART2_RX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART2_RX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART2_RX_GPIO_AF                    GPIO_AF1_USART2

/* USART2_TX */
#define MX_USART2_TX_Pin                        PA2
#define MX_USART2_TX_GPIO_Pin                   GPIO_PIN_2
#define MX_USART2_TX_GPIOx                      GPIOA
#define MX_USART2_TX_GPIO_Mode                  GPIO_MODE_AF_PP
#define MX_USART2_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART2_TX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART2_TX_GPIO_AF                    GPIO_AF1_USART2

#endif  /* MX_DEVICE_H__ */
