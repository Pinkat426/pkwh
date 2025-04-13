#ifndef BSP_LED_HANDLER_H
#define BSP_LED_HANDLER_H

#include "bsp_led_driver.h"

#define INIT_PATTERN (bsp_led_driver_t *)(0xA6A6A6A6)
/* Init space with this pattern */

typedef struct bsp_led_driver bsp_led_driver_t;

typedef enum {
  HANDLER_NOT_INITED = 1, /* LED handler is not inited */
  HANDLER_INITED = 0,     /* LED handler is inited     */
} led_handler_init_t;

typedef enum {
  LED_1 = 0, /* LED index number which passed to app */
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_10,
  MAX_INSTACE_NUMBER,
  LED_NOT_INITIALIZED = 0xFFFF
} led_index_t;

/**
 * @brief LED处理状态枚举类型定义
 *
 * 此枚举类型用于定义LED处理过程中可能遇到的各种状态，包括成功、通用错误以及特定错误。
 * 它为LED处理函数提供了一种标准化的方式来指示操作的结果状态。
 */
typedef enum {
  LED_HANDLER_OK = 0, /**< 成功: LED处理操作按预期完成 */
  LED_HANDLER_ERROR = 1, /**< 通用错误: 表示LED处理中遇到的非特定错误 */
  LED_HANDLER_ERR_TIMEOUT = 2, /**< 超时错误: 处理操作未能在预期时间内完成 */
  LED_HANDLER_ERR_SOURCE = 3, /**< 来源错误: 错误源自不正确的源或调用上下文 */
  LED_HANDLER_ERR_PARAM =
      4, /**< 参数错误: 提供给LED处理函数的参数无效或不正确 */
  LED_HANDLER_ERR_NOMEMORY = 5, /**< 内存错误: 操作因内存不足而失败 */
  LED_HANDLER_ERR_ISR = 6, /**< 中断服务例程错误: 在中断服务例程中操作失败 */
  LED_HANDLER_ERR_RESERVED = 0XFF, /**< 预留错误: 用作未来扩展的占位符 */
} led_handler_status_t;

typedef struct {
  led_handler_status_t (*pf_get_time_ms)(uint32_t *const);
} handler_time_base_ms_t;

#ifdef OS_SUPPORTING
typedef struct {
  led_handler_status_t (*pf_os_delay_ms)(const uint32_t);
} handler_os_delay_t;

typedef struct {
  /* OS queue create */
  led_handler_status_t (*pf_os_queue_create)(uint32_t const item_num,
                                             uint32_t const item_size,
                                             void **const queue_handler);
  /* OS queue put */
  led_handler_status_t (*pf_os_queue_put)(void *const queue_handler,
                                          void *const item, uint32_t timeout);

  /* OS queue get */
  led_handler_status_t (*pf_os_queue_get)(void *const queue_handler,
                                          void *const msg, uint32_t timeout);

  led_handler_status_t (*pf_os_queue_delete)(void *const queue_handler);
} handler_os_queue_t;

typedef struct {
  led_handler_status_t (*pf_os_critical_enter)(void); /* 进入临界区 */
  led_handler_status_t (*pf_os_critical_exit)(void);  /* 退出临界区 */
} handler_os_critical_t;

// 定义一个用于处理操作系统线程的操作句柄
typedef struct {
  // 线程创建函数指针类型
  // 该函数用于创建一个线程，并返回创建状态
  // 参数说明：
  // - task_code: 指向线程任务代码的指针
  // - task_name: 指向线程名称的指针
  // - stack_depth: 线程堆栈深度
  // - parameters: 指向线程参数的指针
  // - priority: 线程优先级
  // - task_handler: 指向线程句柄的指针，用于存储创建后的线程句柄
  led_handler_status_t (*pf_os_thread_create)(void *const task_code,
                                              const char *const task_name,
                                              const uint32_t stack_depth,
                                              void *const parameters,
                                              uint32_t const priority,
                                              void **const task_handler);

  // 线程删除函数指针类型
  // 该函数用于删除一个已创建的线程，并返回删除状态
  // 参数说明：
  // - void*: 指向要删除的线程的指针
  led_handler_status_t (*pf_os_thread_delete)(void *);
} handler_os_thread_t;

#endif /* OS_SUPPORTING */

typedef struct bsp_led_handler bsp_led_handler_t;

typedef led_handler_status_t (*pf_handler_led_constrol_t)(
    bsp_led_handler_t *const self,
    uint32_t,     // cycle time
    uint32_t,     // blink times
    proportion_t, // proportion on/off
    led_index_t const index);

typedef led_handler_status_t (*pf_handler_led_register_t)(
    bsp_led_handler_t *const self, bsp_led_driver_t *const led_driver,
    led_index_t *const index);

#endif /* BSP_LED_HANDLER_H */
