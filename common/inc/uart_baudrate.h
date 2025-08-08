/**
  * @file uart_baudrate.h
  * @brief Define UART baudrate enum head file
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/07/07
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
  * 	2024/07/07	0.1			Leon Lee		Preliminary version.
  */
  
 #ifndef __UART_BAUDRATE_H__
 #define __UART_BAUDRATE_H__
 
 enum UART_BAUDRATE
 {
   UART_BAUDRATE_9600 = 9600,
   UART_BAUDRATE_19200 = 19200,
   UART_BAUDRATE_38400 = 38400,
   UART_BAUDRATE_57600 = 57600,
   UART_BAUDRATE_115200 = 115200,
   UART_BAUDRATE_230400 = 230400,
   UART_BAUDRATE_460800 = 460800,
   UART_BAUDRATE_921600 = 921600
 };
 
 
 
 #endif // __UART_BAUDRATE_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
  