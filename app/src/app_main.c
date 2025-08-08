/**
  * @file app_main.c
  * @brief 
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2025/07/28
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
  * 	2025/07/28	0.1			Leon Lee		Preliminary version.
  */

#include "RTE_Components.h"
#include CMSIS_device_header
#include <cmsis_os2.h>

#include "delay.h"
#include "serial_retarget.h"
#include "bsp.h"
#include "led.h"
#include "debug.h"

__NO_RETURN static void app_main_thread(void* argument)
{
    (void)argument;
    // ...
    for (;;) 
    {
        osDelay(1000); // Delay for 1 second
        debug("Hello, World!\n");
    } 
}

int app_main(void)
{

    // Initialize the BSP (Board Support Package)
    bsp_init();

    // Initialize the serial retargeting with USART1 and a baud rate of 115200
    if (serial_retarget_init(DEBUG_USART, UART_BAUDRATE_115200) != 0) 
    {
        // Initialization failed, handle error
        return -1;
    }

    debug("BSP Initialized\n");
    debug("Serial Retarget Initialized\n");

    // System Initialization
    SystemCoreClockUpdate();
    // ...

    osKernelInitialize();                       // Initialize CMSIS-RTOS
    osThreadNew(app_main_thread, NULL, NULL);   // Create application main thread
    LED_ThreadCreate();                         // Create LED thread
    osKernelStart();                            // Start thread execution

    return 0;
}


/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
