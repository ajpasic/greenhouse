/******************************************************************************/
/*  Filename:   HW_Commmunications.c                                          */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Server side UART communicaiton hardware module used to interface with the */
/*  UART port that is connected to the companion WI-FI mcu (ESP32). The module*/
/*  can send a series of bytes in an array, a single 8-bit value, or a string.*/
/*  The server side uart communication interfaces through the following pin   */
/*  and module:                                                               */
/*                                                                            */
/*  PC4   U1RX     UART ESP32 serial communication.                           */
/*  PC5   U1TX     UART ESP32 serial communication.                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Communication.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/* Send "tx_bytes_size" number of bytes in the "tx_bytes" array to the server.*/
void HW_Server_Send(uint8_t tx_bytes[], uint8_t tx_byte_size)
{
    /*  Provides message length cap defined by macro in header file.          */
    if (tx_byte_size > MAX_MESSAGE_SIZE)
    {
        tx_byte_size = MAX_MESSAGE_SIZE;
    }

    /*  Send bytes to SERVER_UART port.                                       */
    DRV_Uart_Send_Bytes(SERVER_UART, tx_bytes, tx_byte_size);
}

/* Sends a single byte to the server uart port.                               */
void HW_Server_Send_Single(uint8_t tx_byte)
{
    /* Converts single 8-bit value into an array to be able to use the        */
    /* DRV_Uart_Sent_Bytes funciton which requires an array as input.         */
    uint8_t character_arr[1] = {tx_byte};

    /*  Send bytes to SERVER_UART port.                                       */
    DRV_Uart_Send_Bytes(SERVER_UART, character_arr, 1);
}

void HW_Server_Receive(uint8_t *message, uint8_t size)
{

    DRV_Uart_Receive_Bytes(SERVER_UART, message, size, 0xFF);
}

/* Send a string to the server uart port.                                     */
void HW_Server_Print(char *str)
{
    /*  Send bytes to SERVER_UART port.                                       */
    DRV_Uart_Send_Bytes(SERVER_UART, (uint8_t*)str, strlen(str));
}


