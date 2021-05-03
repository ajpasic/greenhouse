#ifndef COMMANDS_H_
#define COMMANDS_H_

// uart configuration
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"

typedef enum {
  TEMPERATURE = 0,
  HUMIDITY,
  WATERING,
  LIGHTING,
  SYSTEM,
  SIZE_OF_NOUN_TABLE
} cmd_noun_t;

typedef enum {
  SET = 0,
  GET,
  ALERT,
  SIZE_OF_VERB_TABLE
} cmd_verb_t;

typedef enum {
  CRITICAL = 0,
  WARNING,
  AMBIENT_SENSOR_FAILURE,
  TEMPERATURE_CONTROL_TIMEOUT,
  SIZE_OF_ALERT_TABLE
} cmd_alert_t;

uint8_t convertASCIItoInteger(uint8_t *data, size_t len) {
  uint8_t value = 0;
  for (int i = 0; i < len; i++) {
    uint8_t increment = (data[i] - '0') * pow(10, len-1 - i);
    value += increment;
  }
  return value;
}

void uart_init(void) {
  uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  uart_param_config(UART_NUM_1, &uart_config);
  uart_set_pin(UART_NUM_1, 14, 2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART_NUM_1, 512*2, 512*2, 0, NULL, 0);
  uart_flush(UART_NUM_1);
}

void cmd_transmit(cmd_noun_t noun, cmd_verb_t verb, uint8_t *dataArray, uint8_t setpoint = 0x00) {
  uint8_t result = 0;
  uint8_t cmd_message[7];
  if (noun < SIZE_OF_NOUN_TABLE && verb < SIZE_OF_VERB_TABLE) {
    cmd_message[0] = (uint8_t) noun;
    cmd_message[1] = (uint8_t) verb;
    cmd_message[2] = setpoint;
    cmd_message[6] = 0xFF;
  }
  
  uart_write_bytes(UART_NUM_1, (const char*) cmd_message, 7);
  uart_wait_tx_done(UART_NUM_1, 100);
  uart_read_bytes(UART_NUM_1, dataArray, 7, 100);
  uart_flush(UART_NUM_1);
}

#endif
