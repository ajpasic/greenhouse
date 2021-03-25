/*
 * SCH_Interrupts.c
 *
 *  Created on: Mar 16, 2021
 *      Author: juanleyva
 */

#include "SCH_Interrupts.h"

void SCH_Interrupt_Uart0(void)
{
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);
    Semaphore_post(semaphore0);
}

void SCH_Interrupt_Uart1(void)
{
    UARTIntClear(UART1_BASE, UART_INT_RX | UART_INT_RT);
}
