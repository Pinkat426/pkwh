/**
 * @file bsp_led_driver.h
 * @brief 该头文件定义了 LED 驱动相关的宏和函数声明，用于控制 STM32 开发板上的
 * LED。
 *
 * @author levon
 * @date 2025-4-13
 */

#ifndef __BSP_LED_DRIVER_H__
#define __BSP_LED_DRIVER_H__

/******************************** Includes ***********************************/

/******************************** Includes ***********************************/
/******************************** Defines ************************************/

#define INITED 1
#define NOT_INITED 0
#define LED_ON 1
#define LED_OFF 0
#define OS_SUPPORTING

#define DEBUG_PK
#ifdef DEBUG_PK
#include "SEGGER_RTT.h"
#define DEBUG_PRINTF(...) SEGGER_RTT_printf(0, __VA_ARGS__)
#else // DEBUG_PK
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#endif // DEBUG_PK

/******************************** Defines ************************************/
/******************************** typedef ************************************/

typedef struct bsp_led_driver bsp_led_driver_t;

typedef enum {
  LED_OK = 0,
  LED_ERROR,
  LED_ERROR_TIMEOUT,
  LED_ERROR_RESOURCES,
  LED_ERROR_PARAMS,
  LED_ERROR_NOMEMORY,
  LED_ERROR_ISR,
  LED_RESERVED = 0xFF,
} led_status_t;

typedef struct {
  uint8_t r, g, b;
} led_color_t;

typedef enum {
  proportion_1_1 = 0,
  proportion_1_2,
  proportion_1_3,
  proportion_1_4,
  proportion_x_x = 0xff,
} proportion_t;

typedef struct {
  led_status_t (*pf_led_on)(void);
  led_status_t (*pf_led_off)(void);
} led_operation_t;

typedef struct {
  led_status_t (*pf_get_time_ms)(uint32_t *const); // 为什么不用定义形参名？
} time_base_ms_t;

#ifdef OS_SUPPORTING
typedef struct {
  led_status_t (*pf_os_delay_ms)(const uint32_t);
} os_delay_ms_t;
#endif // OS_SUPPORTING
typedef led_status_t (*pf_led_control_t)(bsp_led_driver_t *const self,
                                         uint32_t,    // Cycle time in ms
                                         uint32_t,    // Blink repetition count
                                         proportion_t // Blink proportion
);

typedef struct bsp_led_driver {

  /*****************************Internal State********************************/
  uint8_t inited;     // 0: not inited, 1: inited
  uint8_t led_on_off; // 0: off, 1: on
  /*****************************Blink Configuration***************************/
  uint32_t cycle_time_ms;          // Cycle time in ms
  uint32_t blink_repetition_count; // Blink repetition count
  proportion_t proportion_on_off;  // Blink proportion
  /*****************************Interface*************************************/
  led_operation_t *p_led_opes_inst; // LED operation interface
  time_base_ms_t *p_time_base_ms;   // Time base interface
#ifdef OS_SUPPORTING
  os_delay_ms_t *p_os_delay_ms; // OS delay interface
#endif                          // OS_SUPPORTING
  /*****************************Control API***********************************/
  pf_led_control_t pf_led_controler; // LED control API
} bsp_led_driver_t;

/******************************** Declaration ********************************/
/**
 * @brief 初始化 bsp_led_driver_t 结构体
 * @param self 指向 bsp_led_driver_t 结构体的指针
 * @param led_opes 指向 led_operation_t 结构体的指针，包含 LED 操作接口
 * @param os_delay 指向 os_delay_ms_t 结构体的指针，包含 OS 延时接口
 * @param time_base 指向 time_base_ms_t 结构体的指针，包含时间基准接口
 * @return led_status_t 初始化状态
 */
led_status_t bsp_led_driver_inst(bsp_led_driver_t *const self,
                                 led_operation_t *const led_opes,
#ifdef OS_SUPPORTING
                                 os_delay_ms_t *const os_delay,
#endif // OS_SUPPORTING
                                 time_base_ms_t *const time_base);
void test_led_driver(void);
#endif // __BSP_LED_DRIVER_H
