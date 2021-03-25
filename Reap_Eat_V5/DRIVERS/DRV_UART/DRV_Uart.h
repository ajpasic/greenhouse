/*
 * DRV_Uart.h
 *
 *  Created on: Feb 21, 2021
 *      Author: juanleyva
 */

#ifndef DRIVERS_DRV_UART_H_
#define DRIVERS_DRV_UART_H_


#include "DRV_Initialize.h"

typedef enum
{
    SERVER_UART = UART1_BASE,
    DEBUG_UART  = UART0_BASE

} drv_uart_port_t;

void DRV_Uart_Send_Bytes(drv_uart_port_t, uint8_t *, uint8_t);

uint8_t DRV_Uart_Receive_Byte(drv_uart_port_t);

void DRV_Uart_Receive_Bytes(drv_uart_port_t, uint8_t*, uint8_t, uint8_t);


#endif /* DRIVERS_DRV_UART_H_ */
