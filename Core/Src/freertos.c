/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Debug_printf.h"
#include "bsp_led_driver.h"
#include "ws2812.h"
#include <stdint.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[128];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .cb_mem = &defaultTaskControlBlock,
    .cb_size = sizeof(defaultTaskControlBlock),
    .stack_mem = &defaultTaskBuffer[0],
    .stack_size = sizeof(defaultTaskBuffer),
    .priority = (osPriority_t)osPriorityNormal,
};
/* Definitions for key_task */
osThreadId_t key_taskHandle;
uint32_t key_taskBuffer[512];
osStaticThreadDef_t key_taskControlBlock;
const osThreadAttr_t key_task_attributes = {
    .name = "key_task",
    .cb_mem = &key_taskControlBlock,
    .cb_size = sizeof(key_taskControlBlock),
    .stack_mem = &key_taskBuffer[0],
    .stack_size = sizeof(key_taskBuffer),
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for comm_task */
osThreadId_t comm_taskHandle;
uint32_t comm_taskBuffer[512];
osStaticThreadDef_t comm_taskControlBlock;
const osThreadAttr_t comm_task_attributes = {
    .name = "comm_task",
    .cb_mem = &comm_taskControlBlock,
    .cb_size = sizeof(comm_taskControlBlock),
    .stack_mem = &comm_taskBuffer[0],
    .stack_size = sizeof(comm_taskBuffer),
    .priority = (osPriority_t)osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void KeyTask_Entry(void *argument);
void CommTask_Entry(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle =
      osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of key_task */
  key_taskHandle = osThreadNew(KeyTask_Entry, NULL, &key_task_attributes);

  /* creation of comm_task */
  comm_taskHandle = osThreadNew(CommTask_Entry, NULL, &comm_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;

void led_rgb_cycle_blink(void) {
  static uint32_t blink = 0;
  static uint8_t color_index = 0;
  static const rgb_t colors[3] = {
      {2, 0, 0}, // 红
      {0, 2, 0}, // 绿
      {0, 0, 2}  // 蓝
  };

  blink++;

  if (blink > 333) {
    rgb_t current = colors[color_index];
    WS2812_Ctrl(current.r, current.g, current.b);

    color_index = (color_index + 1) % 3; // 循环切换颜色
    blink = 0;
  }
}
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument) {
  /* USER CODE BEGIN StartDefaultTask */

  test_led_driver();
  bsp_led_driver_t led_driver_inst;
  /* Infinite loop */
  for (;;) {
    led_rgb_cycle_blink();
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_KeyTask_Entry */
/**
 * @brief Function implementing the key_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_KeyTask_Entry */
__weak void KeyTask_Entry(void *argument) {
  /* USER CODE BEGIN KeyTask_Entry */
  DEBUG_PRINTF("Key Task Start week...\r\n");
  /* Infinite loop */
  for (;;) {
    osDelay(1);
  }
  /* USER CODE END KeyTask_Entry */
}

/* USER CODE BEGIN Header_CommTask_Entry */
/**
 * @brief Function implementing the comm_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_CommTask_Entry */
__weak void CommTask_Entry(void *argument) {
  /* USER CODE BEGIN CommTask_Entry */
  DEBUG_PRINTF("Comm Task Start week...\r\n");
  /* Infinite loop */
  for (;;) {
    osDelay(1);
  }
  /* USER CODE END CommTask_Entry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
