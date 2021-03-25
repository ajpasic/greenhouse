/******************************************************************************/
/*  Filename:   HW_Commmunications.h                                          */
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

#ifndef HARDWARE_HW_COMMUNICATION_H_
#define HARDWARE_HW_COMMUNICATION_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Uart.h"

/******************************************************************************/
/*                             MACRO DEFINITIONS                              */
/******************************************************************************/

#define MAX_MESSAGE_SIZE    ((uint8_t) 32)

//uint8_t g_message[MAX_MESSAGE_SIZE];

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/* Send "tx_bytes_size" number of bytes in the "tx_bytes" array to the server.*/
void HW_Server_Send(uint8_t tx_bytes[], uint8_t tx_bytes_size);

/* Sends a single byte to the server uart port.                               */
void HW_Server_Send_Single(uint8_t tx_byte);

void HW_Server_Receive(uint8_t *message, uint8_t size);

/* Send a string to the server uart port.                                     */
void HW_Server_Print(char *str);

#endif /* HARDWARE_HW_COMMUNICATION_H_ */
