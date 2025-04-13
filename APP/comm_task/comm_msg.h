// comm_msg.h
#ifndef __COMM_MSG_H
#define __COMM_MSG_H

#include <stdint.h>

#define COMM_MSG_MAX_LEN 64

typedef struct {
  uint8_t data[COMM_MSG_MAX_LEN];
  uint16_t length;
} CommMessage_t;

#endif
