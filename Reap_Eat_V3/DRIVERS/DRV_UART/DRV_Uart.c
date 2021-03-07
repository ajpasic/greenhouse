/*
 * DRV_Uart.c
 *
 *  Created on: Feb 22, 2021
 *      Author: juanleyva
 ******************************************************************************/


#include "DRV_Uart.h"

void DRV_Uart_Send_Bytes(drv_uart_port_t port, uint8_t *tx_bytes,
                         uint8_t tx_byte_count)
{
    uint16_t index;

    for (index = 0; index < tx_byte_count; index++)
    {
        if (!UARTCharPutNonBlocking(port, tx_bytes[index]))
        {
            index--;
        }
    }
}

uint8_t DRV_Uart_Receive_Byte(drv_uart_port_t port)
{
    uint8_t rx_byte;

    /*  While characters available in FIFO.                                   */
    if(UARTCharsAvail(port))
    {
        /* Read byte from UART                                                */
        rx_byte = (uint8_t) UARTCharGetNonBlocking(port);
    }

    return rx_byte;
}

void DRV_Uart_Receive_Bytes(drv_uart_port_t port, uint8_t* rx_buffer,
                            uint8_t rx_buffer_size, uint8_t end_byte)
{
    uint16_t index;
    uint8_t rx_byte = '\0';

    for (index = 0; index < rx_buffer_size; index++)
    {
        rx_byte = DRV_Uart_Receive_Byte(port);

        if (rx_byte == end_byte)
        {
            break;
        }

        rx_buffer[index] = rx_byte;
    }
}
