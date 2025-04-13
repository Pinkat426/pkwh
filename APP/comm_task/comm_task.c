#include "comm_task.h"

void CommTask_Entry(void *argument) {
  DEBUG_PRINTF("Comm Task Start real...\r\n");
  KeyMessage_t key_msg_rcv;

  for (;;) {
    if (NULL != key_to_comm_queue &&
        xQueueReceive(key_to_comm_queue, &key_msg_rcv, 0) == pdTRUE) {
      HAL_UART_Transmit(&huart7, key_msg_rcv.data, key_msg_rcv.length, 1000);
    }
    osDelay(1);
  }
}
