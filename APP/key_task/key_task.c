#include "key_task.h"

QueueHandle_t key_to_comm_queue;
void KeyTask_Entry(void const *argument) {
  uint32_t count = 0;
  DEBUG_PRINTF("Key Task Start real...\r\n");
  key_to_comm_queue = xQueueCreate(10, sizeof(KeyMessage_t));
  KeyMessage_t key_msg;

  for (;;) {
    if (BSP_UserKey_Detect() == BUTTON_PRESSED) {
      count++;
      snprintf((char *)key_msg.data, KEY_MSG_MAX_LEN, "Key Pressed: %d\r\n",
               count);

      key_msg.length = strlen((char *)key_msg.data);
      HAL_UART_Transmit(&huart1, key_msg.data, key_msg.length, 1000);
      xQueueSend(key_to_comm_queue, &key_msg, portMAX_DELAY);
    }
    osDelay(10);
  }
}
