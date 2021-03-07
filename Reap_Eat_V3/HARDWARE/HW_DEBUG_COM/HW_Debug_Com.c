/******************************************************************************/
/*  Filename:   HW_Debug_Com.c                                                */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  PC side UART communicaiton hardware module used to interface with the     */
/*  UART port that is connected to the PC and terminal. The module can send a */
/*  series of bytes in an array, a single 8-bit value, or a string. The PC    */
/*  side uart communication interfaces through the following pin and module:  */
/*                                                                            */
/*  PA0   U0RX     UART PC serial communication.                              */
/*  PA1   U0TX     UART PC serial communication.                              */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Debug_Com.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/* Send "tx_bytes_size" number of bytes in the "tx_bytes" array to the PC.    */
void HW_Debug_Send(uint8_t tx_bytes[], uint8_t tx_byte_size)
{
    /*  Provides message length cap defined by macro in header file.          */
    if (tx_byte_size > MAX_DEBUG_MESSAGE_SIZE)
    {
        tx_byte_size = MAX_DEBUG_MESSAGE_SIZE;
    }

    /*  Send bytes to DEBU_UART port.                                         */
    DRV_Uart_Send_Bytes(DEBUG_UART, tx_bytes, tx_byte_size);
}

/* Sends a single byte to the PC uart port.                                   */
void HW_Debug_Send_Single(uint8_t tx_byte)
{
    /* Converts single 8-bit value into an array to be able to use the        */
    /* DRV_Uart_Sent_Bytes funciton which requires an array as input.         */
    uint8_t character_arr[1] = {tx_byte};

    /*  Send bytes to DEBU_UART port.                                         */
    DRV_Uart_Send_Bytes(DEBUG_UART, character_arr, 1);
}

/* Send a string to the PC uart port.                                         */
void HW_Debug_Print(char *str)
{
    /*  Send bytes to DEBU_UART port.                                         */
    DRV_Uart_Send_Bytes(DEBUG_UART, (uint8_t*)str, strlen(str));
}
