/*
 *************** (C) COPYRIGHT 2015 South China Univ. of Tech. *****************
 * File Name     : led.h
 * Author        : Leon
 * Version       : V1.0
 * Date          : 2015年9月24日-上午8:59:56
 * Description   :
 *******************************************************************************
 * History:
 *   2015年9月24日 上午8:59:56  ver 1.00    Preliminary version, first Release
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H__
#define __LED_H__


#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
    LED_BLINK_NORMAL = 0,
    LED_BLINK_NORMAL_SHORT,
    LED_BLINK_NORMAL_SHORT_2,
    LED_BLINK_HW_ERROR,
    LED_BLINK_SW_ERROR,
    LED_BLINK_LOW_BATTERY,
    LED_BLINK_OVER_WIND_SPEED,
    LED_NO_BLINK,
    LED_BLINK_MAX
}LED_BLINK_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
// #define LED_off(led)            BSP_DO_set((BSP_DO_t)led)
// #define LED_on(led)             BSP_DO_clr((BSP_DO_t)led)

// #define LED_RedOn()             BSP_DO_set(LED_RED)
// #define LED_RedOff()            BSP_DO_clr(LED_RED)
// #define LED_RedToggle()         BSP_DO_toggle(LED_RED)

// #define LED_GreenOn()           BSP_DO_set(LED_GREEN)
// #define LED_GreenOff()          BSP_DO_clr(LED_GREEN)
// #define LED_GreenToggle()       BSP_DO_toggle(LED_GREEN)

// #define LED_YellowOn()          do {LED_RedOn(); LED_GreenOn();} while(0)
// #define LED_YellowOff()         do {LED_RedOff(); LED_GreenOff();} while(0)

/* Exported functions --------------------------------------------------------*/
void LED_BlinkSet(LED_BLINK_t led_blink_type);
void LED_ThreadCreate(void);

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /* __INC_LED_H__ */
/**************************************************** End of file: led.h ******/
