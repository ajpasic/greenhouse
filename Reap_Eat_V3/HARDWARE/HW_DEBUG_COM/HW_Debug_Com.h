/******************************************************************************/
/*  Filename:   HW_Debug_Com.h                                                */
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

#ifndef HARDWARE_HW_DEBUG_COM_H_
#define HARDWARE_HW_DEBUG_COM_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Uart.h"

/******************************************************************************/
/*                             MACRO DEFINITIONS                              */
/******************************************************************************/

#define MAX_DEBUG_MESSAGE_SIZE ((uint8_t) 64)

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/* Send "tx_bytes_size" number of bytes in the "tx_bytes" array to the PC.    */
void HW_Debug_Send(uint8_t tx_bytes[], uint8_t tx_bytes_size);

/* Sends a single byte to the PC uart port.                                   */
void HW_Debug_Send_Single(uint8_t tx_byte);

/* Send a string to the PC uart port.                                         */
void HW_Debug_Print(char *str);

#endif /* HARDWARE_HW_DEBUG_COM_H_ */
