/**
 * @file bsp_led_driver.c
 * @brief 该头文件定义了 LED 驱动相关的宏和函数声明，用于控制 STM32 开发板上的
 * LED。
 *
 * @author levon
 *
 * @author levon
 * @date 2025-4-13
 */
/******************************** Includes ***********************************/
#include "bsp_led_driver.h"
#include <stdint.h>
/******************************** Includes ***********************************/
/******************************** Static Functions ***************************/
/**
 * @brief led_blink实现闪烁
 * @param bsp_led_driver_t self LED 驱动结构体指针
 */
static led_status_t led_blink(bsp_led_driver_t *self) {
  led_status_t ret = LED_OK;
  // 检查参数有效性
  if (NULL == self || NOT_INITED == self->inited) {
    ret = LED_ERROR_PARAMS;
    return ret;
  }
  // analyze the feature of led
  uint32_t cycle_time_ms_local = self->cycle_time_ms;
  uint32_t blink_repetition_count_local = self->blink_repetition_count;
  uint32_t proportion_on_off_local = self->proportion_on_off;
  uint32_t led_toggle_times = 0;

  if (proportion_1_1 == proportion_on_off_local) {
    led_toggle_times = cycle_time_ms_local / 2;
  } else if (proportion_1_2 == proportion_on_off_local) {
    led_toggle_times = cycle_time_ms_local / 3;
  } else if (proportion_1_3 == proportion_on_off_local) {
    led_toggle_times = cycle_time_ms_local / 4;
  } else {
    ret = LED_ERROR_PARAMS;
    return ret;
  }
  for (uint32_t i = 0; i < blink_repetition_count_local; i++) {
    for (uint32_t j = 0; j < cycle_time_ms_local; j++) {
      self->p_os_delay_ms->pf_os_delay_ms(1);
      if (j < led_toggle_times) {
        // LED_ON
        self->p_led_opes_inst->pf_led_on();
      } else {
        // LED_OFF
        self->p_led_opes_inst->pf_led_off();
      }
    }
  }
  return ret;
}
/**
 * @brief pf_led_controler 实现控制
 * @param bsp_led_driver_t self LED 驱动结构体指针
 * @param uint32_t cycle_time_ms 闪烁周期时间
 * @param uint32_t blink_repetition_count 闪烁重复次数
 * @param proportion_t proportion_on_off 闪烁占空比
 * @return led_status_t 控制结果
 */
static led_status_t led_control(bsp_led_driver_t *const self,
                                uint32_t cycle_time_ms,
                                uint32_t blink_repetition_count,
                                proportion_t proportion_on_off) {
  led_status_t ret = LED_OK;
  // 检查参数有效性
  if (NULL == self || NOT_INITED == self->inited) {
    ret = LED_ERROR_PARAMS;
    return ret;
  }
  // 检查控制参数有效性
  if (!((cycle_time_ms < 10000) && (blink_repetition_count < 1000) &&
        (proportion_on_off < 4))) {
    ret = LED_ERROR_PARAMS;
    return ret;
  }
  // 设置闪烁参数
  self->cycle_time_ms = cycle_time_ms;
  self->blink_repetition_count = blink_repetition_count;
  self->proportion_on_off = proportion_on_off;
  // 调用 led_blink 函数实现闪烁
  ret = led_blink(self);
  return ret;
}

/**
 * @brief led_driver初始化,在创造实例后调用
 * @param bsp_led_driver_t self LED 驱动结构体指针
 * @return led_status_t
 */
static led_status_t led_driver_init(bsp_led_driver_t *const self) {
  led_status_t ret = LED_OK;
  // 检查参数有效性
  if (NULL == self) {
    ret = LED_ERROR_PARAMS;
    return ret;
  }
  self->p_led_opes_inst->pf_led_off();
  self->p_os_delay_ms->pf_os_delay_ms(600);
  uint32_t time_stamp = 0;
  self->p_time_base_ms->pf_get_time_ms(&time_stamp);
  return ret;
}

/**
 * @brief 构建示例，需将函数实现挂载
 * @param self LED 驱动结构体指针
 * @param led_opes 指向 led_operation_t 结构体的指针，包含 LED 操作接口
 * @param os_delay_ms 指向 os_delay_ms_t 结构体的指针，包含操作系统延迟接口
 * @param time_base_ms 指向 time_base_ms_t 结构体的指针，包含时间基准接口
 * @return led_status_t
 */
led_status_t bsp_led_driver_inst(bsp_led_driver_t *const self,
                                 led_operation_t *const led_opes,
                                 os_delay_ms_t *const os_delay_ms,
                                 time_base_ms_t *const time_base_ms) {
  led_status_t ret = LED_OK;

  // 检查参数有效性
  if (NULL == self || NULL == led_opes || NULL == os_delay_ms ||
      NULL == time_base_ms) {
    ret = LED_ERROR_PARAMS;
    return ret;
  }
  // 检查资源是否被初始化
  if (INITED == self->inited) {
    ret = LED_ERROR_RESOURCES;
    return ret;
  }

  // 挂载函数指针
  self->p_led_opes_inst = led_opes;
  self->p_os_delay_ms = os_delay_ms;
  self->p_time_base_ms = time_base_ms;
  self->pf_led_controler = led_control;

  self->blink_repetition_count = 0;
  self->cycle_time_ms = 0;
  self->proportion_on_off = proportion_x_x;

  ret = led_driver_init(self);
  if (LED_OK != ret) {
    self->p_led_opes_inst = NULL;
    self->p_os_delay_ms = NULL;
    self->p_time_base_ms = NULL;
    return ret;
    self->inited = NOT_INITED;
  }
  self->inited = INITED;
  DEBUG_PRINTF("bsp_led_driver_inst success!\r\n");
  return ret;
}

/********************************test******************************************/
void test_led_driver(void) { DEBUG_PRINTF("test_led_driver start!\r\n"); }
