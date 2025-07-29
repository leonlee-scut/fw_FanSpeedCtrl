/*
 *************** (C) COPYRIGHT 2015 South China Univ. of Tech. *****************
 * File Name     : led.c
 * Author        : Leon
 * Version       : V1.0
 * Date          : 2015年9月24日-上午9:00:10
 * Description   :
 *******************************************************************************
 * History:
 *   2015年9月24日 上午9:00:10  ver 1.00    Preliminary version, first Release
 *
 *******************************************************************************
 * SVN CONTROL
 *=====================
 *  File name    : $HeadURL$
 *  Revision     : $Revision$
 *  Last modified: $Date$
 *             by: $Author$
 *******************************************************************************
 */
#define _LED_MOD_

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os2.h"

#include "bsp.h"

#include "led.h"

/* Public variables ----------------------------------------------------------*/
/* Private typedefs ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define LED_BLINK_NORMAL_PATTERN            {1,1,1,1,1,1,1,1,1,1}
#define LED_BLINK_NORMAL_SHORT_PATTERN      {1,0,0,0,0,0,0,0,0,0}
#define LED_BLINK_NORMAL_SHORT_2_PATTERN    {1,0,1,0,0,0,0,0,0,0}
#define LED_BLINK_HW_ERROR_PATTERN          {1,1,1,0,0,0,0,1,1,1}
#define LED_BLINK_SW_ERROR_PATTERN          {1,1,0,0,1,1,0,0,1,1}
#define LED_BLINK_LOW_BATTERY_PATTERN       {1,0,0,1,0,0,0,0,0,0}
#define LED_BLINK_OVER_WIND_SPEED_PATTERN   {1,1,0,0,0,1,1,0,0,0}
#define LED_BLINK_NO_FLASH_PATTERN          {2,2,2,2,2,2,2,2,2,2}


#ifndef LED_CPU_RUNNING
#define LED_CPU_RUNNING                     (LED_GREEN)
#endif

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const static uint8_t _led_blink_pattern[LED_BLINK_MAX][10]
    = {LED_BLINK_NORMAL_PATTERN,
       LED_BLINK_NORMAL_SHORT_PATTERN,
       LED_BLINK_NORMAL_SHORT_2_PATTERN,
       LED_BLINK_HW_ERROR_PATTERN,
       LED_BLINK_SW_ERROR_PATTERN ,
       LED_BLINK_LOW_BATTERY_PATTERN,
       LED_BLINK_OVER_WIND_SPEED_PATTERN,
       LED_BLINK_NO_FLASH_PATTERN };

static uint8_t *_led_blink_mode;
static uint8_t  _led_blink_ticks;

#define LED_BLINK_TICKS_MAX             sizeof(_led_blink_pattern[0])

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void ledThread(void *argument);

/* Public functions ----------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *      LED_BlinkSet: Description
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_BlinkSet(LED_BLINK_t led_blink_type)
{
    if (led_blink_type < LED_BLINK_MAX)
    {
        _led_blink_mode = (uint8_t *)(_led_blink_pattern[led_blink_type]);
    }
}

/*-----------------------------------------------------------------------------
 *      LED_TaskCreator: Description
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_ThreadCreate(void)
{
    _led_blink_ticks = 0;
   _led_blink_mode = (uint8_t *)_led_blink_pattern[LED_BLINK_NORMAL];
    // _led_blink_mode = (uint8_t *)_led_blink_pattern[1];
    // _led_blink_mode = (uint8_t *)_led_blink_pattern[2];
    // _led_blink_mode = (uint8_t *)_led_blink_pattern[3];
    // _led_blink_mode = (uint8_t *)_led_blink_pattern[4];
    // _led_blink_mode = (uint8_t *)_led_blink_pattern[LED_NO_BLINK];
    osThreadAttr_t attr = {
        .priority = osPriorityLow,
        .stack_size = 256,
        };
    
    osThreadNew(ledThread, NULL, &attr);
}

/*-----------------------------------------------------------------------------
 *      tskLED: Description
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
__NO_RETURN void ledThread(void *argument)
{
    bool is_flash = true;

    while(1)
    {
        if (++_led_blink_ticks >= 2*LED_BLINK_TICKS_MAX)
        {
            _led_blink_ticks = 0;
        }

        if (_led_blink_ticks < LED_BLINK_TICKS_MAX)
        {
            switch (_led_blink_mode[_led_blink_ticks])
            {
                case 0:
                    is_flash = true;
                    LED_off(LED_CPU_RUNNING);
                    break;

                case 1:
                    is_flash = true;
                    LED_on(LED_CPU_RUNNING);
                    break;

                default:
                    is_flash = false;
                    LED_on(LED_CPU_RUNNING);
                    break;
            }
            // if (_led_blink_mode[_led_blink_ticks] == 1)
            // {
            //     LED_on(LED_CPU_RUNNING);
            // }
            // else
            // {
            //     LED_off(LED_CPU_RUNNING);
            // }
        }
        else
        {
            if (is_flash)
            {
                LED_off(LED_CPU_RUNNING);
            }
            else
            {
                LED_on(LED_CPU_RUNNING);
            }
        }

        if ((_led_blink_ticks % 10) == 0)
        {
            // BSP_WDG_Feed();
        }

        osDelay(100);
    }
}

/***************************************************** End of file: led.c *****/
