/**
  * @file serial_retarget.h
  * @brief Serial io retarget header file
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/07/11
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
  * 	2024/07/11	0.1			Leon Lee		Preliminary version.
  */

#ifndef __SERIAL_RETARGET_H__
#define __SERIAL_RETARGET_H__

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */
#include "RTE_Components.h"
#include CMSIS_device_header
#include "uart_baudrate.h"

#define TX_FIFO_BUFFER_SIZE     1024
#define RX_FIFO_BUFFER_SIZE     512

#define IS_POWER_OF_TWO(x)      (((x) != 0) && (((x) & ((x) - 1)) == 0))

#if !IS_POWER_OF_TWO(TX_FIFO_BUFFER_SIZE)
#error "TX_FIFO_BUFFER_SIZE is not a power of 2"
#endif

#if !IS_POWER_OF_TWO(RX_FIFO_BUFFER_SIZE)
#error "RX_FIFO_BUFFER_SIZE is not a power of 2"
#endif

int serial_retarget_init(UART_HandleTypeDef *uart, enum UART_BAUDRATE baudrate);

// int stdout_putchar(int ch);
// int stderr_putchar(int ch);
// int stdin_getchar(void);

#ifdef __cplusplus
}
#endif /* extern "C" */



#endif // __SERIAL_RETARGET_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
