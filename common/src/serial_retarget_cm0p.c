/**
  * @file serial_retarget_cm0p.c
  * @brief Serial retarget i/o routines for Cortex-M0+.
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/07/01
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
  * 	2024/07/01	0.1			Leon Lee		Preliminary version.
  *     2025/08/01  0.2         Leon Lee        Re-write to support Cortex-M0+
  */

#include "RTE_Components.h"
#include CMSIS_device_header
#include "cmsis_os2.h"

#include "assert.h"
#include "critical_section.h"
#include "fifo.h"
#include "fxn.h"
#include "serial_retarget.h"


#define TX_FIFO_AVAILABLE_EVT   (1<<0)
#define RX_FIFO_AVAILABLE_EVT   (1<<15)


FIFO_CREATE(tx_fifo, uint8_t, TX_FIFO_BUFFER_SIZE);
FIFO_CREATE(rx_fifo, uint8_t, RX_FIFO_BUFFER_SIZE);

static UART_HandleTypeDef *stdio_uart = NULL;
static osThreadId_t txThreadId = NULL;
static osThreadId_t rxThreadId = NULL;


/**
  * @brief Initialize the serial retarget i/o routines with the given UART and baud rate.
  *
  * @param uart A pointer to the UART_HandleTypeDef structure that describes the UART module.
  * @param baudrate The baud rate to use for the UART.
  * @return 0 on success, -1 on failure.
  */
int serial_retarget_init(UART_HandleTypeDef *uart, enum UART_BAUDRATE baudrate)
{
    ASSERT(uart != NULL);
    HAL_StatusTypeDef status;
    stdio_uart = uart;
    stdio_uart->Init.BaudRate = baudrate;
    stdio_uart->Init.WordLength = UART_WORDLENGTH_8B;
    stdio_uart->Init.StopBits = UART_STOPBITS_1;
    stdio_uart->Init.Parity = UART_PARITY_NONE;
    stdio_uart->Init.Mode = UART_MODE_TX_RX;
    stdio_uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    stdio_uart->Init.OverSampling = UART_OVERSAMPLING_16;

    status = HAL_UART_Init(stdio_uart);
    if (status != HAL_OK)
    {
        return -1; // Initialization failed
    }

    // Lock the stdio_uart
    stdio_uart->gState = HAL_UART_STATE_BUSY;
    stdio_uart->Lock = HAL_LOCKED;

    // Enable the UART receive data register not empty interrupt
    __HAL_UART_ENABLE_IT(stdio_uart, UART_IT_RXNE);

    return 0; // Initialization successful
}

/**
  * @brief Put a character to stdout
  *
  * This function sends a character to the stdout (UART).
  * It first checks if there is space in the transmit FIFO. If there is, the character
  * is pushed into the FIFO. If the FIFO is full, it waits until there is space.
  *
  * @param ch The character to be output
  * @return int The character written, or -1 if there was an error
  */
int stdout_putchar (int ch)
{
    // Convert the character to an 8-bit unsigned integer
    uint8_t val = (uint8_t) ch;

    // Keep pushing the character into the transmit FIFO until it is successful
    while (fifo_push(tx_fifo, &val) != FIFO_OK)
    {
        if (osKernelGetState() == osKernelRunning)
        {
            // If the system is running in an OS thread, wait for the transmit FIFO to
            // be available by flag polling.
            txThreadId = osThreadGetId();
            ASSERT(txThreadId != NULL);
            // if (txThreadId == NULL) return -1;
            osThreadFlagsWait(TX_FIFO_AVAILABLE_EVT, osFlagsWaitAny, osWaitForever);
            txThreadId = NULL;
        }
        else
        {
            // If the system is running in a non-OS thread, wait for the transmit FIFO to
            // be available by busy-waiting.
            txThreadId = (void *)-1;
            while (txThreadId == (void *)-1);
        }
    }

    // Enable the UART transmit data register empty interrupt
    __HAL_UART_ENABLE_IT(stdio_uart, UART_IT_TXE);

    // Return the character written
    return ch;
}


/**
  * @brief Get a character from stdin
  * 
  * This function waits for a character to be available in the receive FIFO.
  * If the receive FIFO is empty, it waits until a character becomes available.
  * If the system is running in an OS thread, it waits by flag polling.
  * If the system is running in a non-OS thread, it waits by busy-waiting.
  * 
  * @return int the next character from the input, or -1 on read error
  */
int stdin_getchar(void)
{
    uint8_t ch = 0;

    // Wait for a character to be available in the receive FIFO
    while (fifo_pop(rx_fifo, &ch) != FIFO_OK)
    {
        if (osKernelGetState() == osKernelRunning)
        {
            // If the system is running in an OS thread, wait for the receive FIFO to
            // be available by flag polling.
            rxThreadId = osThreadGetId();
            ASSERT(rxThreadId != NULL);
            // if (rxThreadId == NULL) return -1;
            osThreadFlagsWait(RX_FIFO_AVAILABLE_EVT, osFlagsWaitAny, osWaitForever);
            rxThreadId = NULL;
        }
        else
        {
            // If the system is running in a non-OS thread, wait for the receive FIFO to
            // be available by busy-waiting.
            rxThreadId = (void *)-1;
            while (rxThreadId == (void *)-1);
        }
    }

    // Return the next character from the input
    return (int) ch;
}


/**
  * @brief Put a character to stderr
  * 
  * @param ch Character to be output
  * @return int The character written, or -1 if error
  */
int stderr_putchar (int ch) __ALIAS("stdout_putchar");
// {
//     return stdout_putchar(ch);
// }


/**
  * @brief USART1 Interrupt Handler
  * 
  * This function is the Interrupt Service Routine (ISR) for USART1.
  * It is called when an interrupt event occurs on USART1.
  * 
  */
void STDIO_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    ASSERT(huart == stdio_uart);
    
    /* USART in mode Receiver ------------------------------------------------*/
    // Check if the USART is enabled to receive and an interrupt is pending
    if (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE)  && 
        __HAL_UART_GET_IT(huart, UART_IT_RXNE))
    {
        // Pop the received character from the USART receive data register
        uint8_t ch = READ_REG(stdio_uart->Instance->RDR);
        // Push the character into the receive FIFO
        fifo_push(rx_fifo, &ch);

        // If the receive thread is waiting for the receive FIFO to be available,
        // set the thread flag to indicate that the FIFO is available.
        switch ((uint32_t)rxThreadId)
        {
            case NULL:
                break;

            case -1:
                rxThreadId = NULL;
                break;

            default:
                osThreadFlagsSet(rxThreadId, RX_FIFO_AVAILABLE_EVT);
                break;
        }
    }
    

    /* USART in mode Transmitter ---------------------------------------------*/
    // Check if the USART is enabled to transmit and an interrupt is pending
    if (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_TXE)  &&
        __HAL_UART_GET_IT(huart, UART_IT_TXE))
    {
        // Pop the next character from the transmit FIFO
        uint8_t ch;
        if (fifo_pop(tx_fifo, &ch) != FIFO_OK)
        {
            // Disable transmit interrupts if the FIFO is empty
            __HAL_UART_DISABLE_IT(stdio_uart, UART_IT_TXE);
        }
        else
        {
            // Write the character to the USART transmit data register
            WRITE_REG(stdio_uart->Instance->TDR , (uint32_t)ch); 
        }

        // 
        // If the transmit thread is waiting for the transmit FIFO to be available,
        // set the thread flag to indicate that the FIFO is available.
        switch ((uint32_t)txThreadId)
        {
            case NULL:
                break;

            case -1:
                txThreadId = NULL;
                break;

            default:
                osThreadFlagsSet(txThreadId, TX_FIFO_AVAILABLE_EVT);
                break;
        }
    }

    /* USART in mode Transmitter (transmission end) --------------------------*/
    if (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_TC) &&
        __HAL_UART_GET_IT(huart, UART_IT_TC))
    {
        __HAL_UART_DISABLE_IT(stdio_uart, UART_IT_TC);
    }
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
  