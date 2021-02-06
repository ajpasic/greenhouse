/*************************************************************************
 *
 *  Filename:   esp32_tivac_communication
 *  Author:     Juan Leyva
 *  Created on: Feb 2, 2021
 *
 *  Descriptions: Program that sets up communication through UART between
 *                ESP32 microcontroller and TM4C123G microcontroller.
 *
 ************************************************************************/

/************************************************************************
 *                           INCLUDE FILES                              
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_intr_alloc.h"


/************************************************************************
 *                          MACRO DEFINITION                             
 ************************************************************************/

#define PC_UART     (UART_NUM_0) // UART0 connects to PC
#define TIVA_UART   (UART_NUM_1) // UART1 connects to TIVA

#define RX1         (2)          // Pin 2 is the RX pin of UART1
#define TX1         (14)          // Pin 4 is the TX pin of UART1

#define BUF_SIZE    (1024)
#define RD_BUF_SIZE (BUF_SIZE)

#define NUM_CODES   (32)
#define DATA_LEN    (32)
#define MESSAGE_LEN (32)

/************************************************************************
 *                          TYPES DEFINTION                             
 ************************************************************************/
typedef struct status_t
{
    uint8_t status_code;
    bool    working;
    char    message[MESSAGE_LEN];

} status_t;

/************************************************************************
 *                          GLOBAL VARIABLES                             
 ************************************************************************/

static intr_handle_t handle_console0;
static intr_handle_t handle_console1;

uint8_t rxbuf0[256];  // UART0 buffer
uint8_t rxbuf1[256];  // UART1 buffer

status_t status_report[NUM_CODES];

/************************************************************************
 *                          FUNCTION PROTOTYPES                             
 ************************************************************************/

// initializes status report array
static void status_init(void);

// initialize uart peripheral and interrupts
static void uart_init(void);

// updates status report array
static void status_update(const uint8_t code, const bool working, const char *msg);

// executes command received from Tiva C
static void comm_exec_cmd(const uint8_t code, const uint8_t *data_arr);

// executes command received from PC
static void comm_exec_cmd_debug(const char *msg);

// pushes command to Tiva C
static void comm_push(const uint8_t code, const uint8_t *data_arr);

// pushes message to PC
static void comm_push_debug(const char *msg);

// handles alert
static void comm_alert(const char *msg);

// uart0 interrupt handler
static void IRAM_ATTR uart_intr_handle0(void *arg);

// uart1 interrupt handler
static void IRAM_ATTR uart_intr_handle1(void *arg);

/************************************************************************
 *                          TASK IMPLEMENTATION                             
 ************************************************************************/
void blink_task(void *pvParameter)
{
    gpio_pad_select_gpio(GPIO_NUM_33);
    gpio_set_direction(GPIO_NUM_33, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_33, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  
    while(true) 
    {
        gpio_set_level(GPIO_NUM_33, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/************************************************************************
 *                      ARDUINO IDE SPECIFIC                          
 ************************************************************************/
 
void setup(void)
{
    status_init();
    uart_init();
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}

void loop(void)
{
  
}

/************************************************************************
 *                         FUNCTION IMPLEMENTATION                       
 ************************************************************************/

// initializes status report array
static void status_init(void)
{
    volatile uint8_t code_i;

    for (code_i = 0x00; code_i <= 0x1F; code_i++);
    {
        status_report[code_i].status_code = code_i;
        status_report[code_i].working     = false;
        strcpy(status_report[code_i].message, "Not initialized.");
    }
}

// initialize uart peripheral and interrupts
static void uart_init(void)
{
    // uart configuarion 
    uart_config_t uart_config = 
    {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
     };
    
    uart_param_config(PC_UART, &uart_config);
    uart_param_config(TIVA_UART, &uart_config);

    // set pins for uart communication
    uart_set_pin(PC_UART, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_set_pin(TIVA_UART, TX1, RX1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // install uart drivers
    uart_driver_install(PC_UART, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_driver_install(TIVA_UART, BUF_SIZE * 2, 0, 0, NULL, 0);
    
    // free isr from uarts
    uart_isr_free(PC_UART);
    uart_isr_free(TIVA_UART);

    // register isr function for uart interrupts
    uart_isr_register(PC_UART, uart_intr_handle0, NULL, ESP_INTR_FLAG_IRAM, &handle_console0);
    uart_isr_register(TIVA_UART, uart_intr_handle1, NULL, ESP_INTR_FLAG_IRAM, &handle_console1);

    // enable receive interrupts
    uart_enable_rx_intr(PC_UART);
    uart_enable_rx_intr(TIVA_UART);

    // push an initialization message to verify setup
    uart_flush(PC_UART);
    uart_flush(TIVA_UART);
    comm_push_debug("Initialized...\n\r\0");  
}

// updates status report array
static void status_update(const uint8_t code, const bool working, const char *msg)
{
    uart_disable_rx_intr(PC_UART);
    uart_disable_rx_intr(TIVA_UART);
    
    if (code >= 0x01 && code <= 0x1F)
    {
      status_report[code].working = working;
      strcpy(status_report[code].message, msg);
    }

    uart_enable_rx_intr(PC_UART);
    uart_enable_rx_intr(TIVA_UART);
}

// executes command received from Tiva C
static void comm_exec_cmd(const uint8_t code, const uint8_t *data_arr)
{
    switch(code)
    {
        case 'R':
            status_update(data_arr[0], data_arr[1], (const char*) &data_arr[2]);
            break;
        case 'A':
            comm_alert((const char*) data_arr);
            break;
        default:
            comm_push_debug((const char*) data_arr);
            break;
    }   
}

// executes command received from PC
static void comm_exec_cmd_debug(const char *msg)
{
    uint8_t code;
    uint8_t data_arr[4] = {0, 0, 0, 0};
    const char *format = "%c %2hX %2hX %2hX %2hX";

    sscanf(msg, format, &code, &data_arr[0], &data_arr[1], &data_arr[2], &data_arr[3]);
    
    comm_push(code, data_arr);
    comm_push_debug(msg);
}

// pushes command to Tiva C
static void comm_push(const uint8_t code, const uint8_t *data_arr)
{
    char str[4];
    sprintf(str, "%c", (char) code);

    uart_wait_tx_done(TIVA_UART, 100);
    uart_write_bytes(TIVA_UART, str, strlen(str));
    uart_write_bytes(TIVA_UART, (const char*) data_arr, sizeof(data_arr) / sizeof(data_arr[0]));
    uart_write_bytes(TIVA_UART, str, strlen(str));
}

// pushes message to PC
static void comm_push_debug(const char *msg)
{
    uart_wait_tx_done(PC_UART, 100);
    uart_write_bytes(PC_UART, msg, strlen(msg));
}

// handles alert from Tiva C
static void comm_alert(const char *msg)
{
    comm_push_debug(msg);
}

// uart0 interrupt handler
static void IRAM_ATTR uart_intr_handle0(void *arg)
{
    uart_clear_intr_status(PC_UART, UART_RXFIFO_FULL_INT_CLR | UART_RXFIFO_TOUT_INT_CLR);
    
    uint16_t rx_fifo_len;
    uint16_t i = 0;
  
    rx_fifo_len = UART0.status.rxfifo_cnt; // read number of bytes in UART buffer
    
    while(rx_fifo_len)
    {
        rxbuf0[i++] = UART0.fifo.rw_byte; // read all bytes
        rx_fifo_len--;
    }
    
    uart_flush(PC_UART);
    
    comm_exec_cmd_debug((const char*) rxbuf0);
}

// uart1 interrupt handler
static void IRAM_ATTR uart_intr_handle1(void *arg)
{
    uart_clear_intr_status(TIVA_UART, UART_RXFIFO_FULL_INT_CLR | UART_RXFIFO_TOUT_INT_CLR);
    
    uint16_t rx_fifo_len;
    uint16_t i = 0;
  
    rx_fifo_len = UART1.status.rxfifo_cnt; // read number of bytes in UART buffer
    
    while(rx_fifo_len)
    {
        rxbuf1[i++] = UART1.fifo.rw_byte; // read all bytes
        rx_fifo_len--;
    }
    
    uart_flush(TIVA_UART);
    
    comm_exec_cmd((*rxbuf1), rxbuf1+1);
}
