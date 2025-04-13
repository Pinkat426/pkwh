/**
 * @file bsp_key_driver.h
 * @author levon
 * @brief
 * @date 2025-04-13
 */
#ifndef __BSP_LED_DRIVER_H__
#define __BSP_LED_DRIVER_H__

/******************************** Includes ***********************************/
#include "gpio.h"
/******************************** Includes ***********************************/
/******************************** Defines ************************************/

#define BUTTON_NOT_PRESSED 0
#define BUTTON_PRESSED 1

typedef enum { NO_DETECT, DETECTING, DETECTED } KeyState;

int8_t BSP_UserKey_Detect(void);

#endif // __BSP_LED_DRIVER_H__
