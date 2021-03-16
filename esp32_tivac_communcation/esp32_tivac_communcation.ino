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

char str [30];
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
#define MESSAGE_LEN (64)

/************************************************************************
 *                          TYPES DEFINTION                             
 ************************************************************************/

typedef union data_t
{
    char msg[MESSAGE_LEN];
    float value;
} data_t;

typedef struct status_t
{
    uint8_t id;
    uint8_t operation;
    data_t  data;

} status_t;

typedef struct cmd_t
{
    uint8_t code;
    uint8_t data[64];

} cmd_t;

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
static uint8_t status_set(const uint8_t id, const uint8_t operation, const data_t data);

// executes command received from Tiva C
static void comm_exec_cmd(const uint8_t code, const uint8_t *data_arr);

// executes command received from PC
static void comm_exec_cmd_debug(const char *msg);

// pushes command to Tiva C
static uint8_t comm_send_cmd(const cmd_t cmd);

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

    char str[16];
    uint8_t dat[2] = {0x01};
  
    while(true) 
    {
        gpio_set_level(GPIO_NUM_33, 1);

        sprintf(str, "%c%c%c", 'G', 0x1, 0xFF);

        uart_write_bytes(TIVA_UART, str, strlen(str));

        vTaskDelay(50 / portTICK_PERIOD_MS);

        if (status_report[1].operation == 0x02)
        {
            sprintf(str, "%2hX %2hX %s\n\r", status_report[1].id,
                                         ((int)(status_report[1].operation)),
                                         status_report[1].data.msg);
            comm_push_debug(str);
        }
        else
        {
            sprintf(str, "%2hX %2hX %f ˚C\n\r", status_report[1].id,
                                            ((int)(status_report[1].operation)),
                                            status_report[1].data.value);
            comm_push_debug(str);
        }
     
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
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE * 2, NULL, 5, NULL);
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
    volatile uint8_t id;

    /* Initializing status for status id's 0x00 - 0x10.                */

    for (id = 0x00; id < NUM_CODES; id++)
    {
        status_report[id].id = (uint8_t)id;
        status_report[id].operation = (uint8_t)0x02;
        strcpy(status_report[id].data.msg, "Not initialized.");
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
static uint8_t status_set(const uint8_t id, const uint8_t operation, const data_t data)
{
    uint8_t result = 0x01;

    status_report[id].id = id;
    status_report[id].operation = operation;

    uart_disable_rx_intr(PC_UART);
    uart_disable_rx_intr(TIVA_UART);

    if (operation == 0x02)
    {
        strcpy(status_report[id].data.msg, data.msg);
        result = 0x00;
    }
    else
    {
        status_report[id].data.value = data.value;
        result = 0x00;
    }

    uart_enable_rx_intr(PC_UART);
    uart_enable_rx_intr(TIVA_UART);

    return result;
}

// executes command received from Tiva C
static void comm_exec_cmd(const uint8_t code, const uint8_t *data_arr)
{
    uint8_t id = 0x00;
    uint8_t operation = 0x02;
    float value = 0.0;
    char msg[MESSAGE_LEN];
    
    switch(code)
    {
        case 'S':
            sscanf((char*)data_arr, "%c%c", (char*) &id, (char*) &operation);

            if (operation == 0x02)
            {
                sscanf((char*)data_arr, "%c%c%s", (char*)&id, (char*)&operation, msg);
                data_t dat;
                strcpy(dat.msg, msg);
               
                status_set(id, operation, dat);
            }
            else
            {
                sscanf((char*)data_arr, "%c%c%f", (char*)&id, (char*)&operation, (float*)&value);
                data_t dat;
                dat.value = value;
           
                status_set(id, operation, dat);
            }
                    
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
}

// pushes command to Tiva C
static uint8_t comm_send_cmd(const cmd_t cmd)
{
    char str[64];
    sprintf(str, "%c%s%c", cmd.code, (const unsigned char *) cmd.data, 0xFF);
    
    
    uart_wait_tx_done(TIVA_UART, 100);
    uart_write_bytes(TIVA_UART, str, strlen(str));

    return 0;
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
    
   // comm_exec_cmd_debug((const char*) rxbuf0);
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
    
    sscanf((const char *)rxbuf1, "%c%c%c", &str[0], &str[1], &str[2]);
    uart_write_bytes(PC_UART, str, 4);
    
    
   // comm_exec_cmd((*rxbuf1), rxbuf1+1);
}
