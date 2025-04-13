#ifndef __KEY_TASK__
#define __KEY_TASK__

#include "Debug_printf.h"
#include "FreeRTOS.h"
#include "bsp_key_driver.h"
#include "cmsis_os.h"
#include "common_include.h"
#include "queue.h"
#include "stm32h7xx_hal_uart.h"
#include "usart.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define KEY_MSG_MAX_LEN 32

typedef struct {
  uint8_t data[KEY_MSG_MAX_LEN];
  uint16_t length;
} KeyMessage_t;

extern QueueHandle_t key_to_comm_queue;

#endif // __KEY_TASK__
