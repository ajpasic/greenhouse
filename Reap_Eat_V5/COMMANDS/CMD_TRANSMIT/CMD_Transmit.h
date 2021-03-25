/******************************************************************************/
/*  Filename:   CMD_Transmit.h                                                */
/*  Created on: Mar 13, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  This module deals with the transmission of commands from  controller to   */
/*  server mcu.                                                               */
/******************************************************************************/

#ifndef CMD_TRANSMIT_H_
#define CMD_TRANSMIT_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <stdint.h>
#include "CMD_General.h"
#include "HW_Communication.h"

/******************************************************************************/
/*                             MACRO DEFINITIONS                              */
/******************************************************************************/

#define CMD_WORD_SIZE     ((uint8_t) 7)
#define CMD_TRANSMIT_OK   ((uint8_t) 0)
#define CMD_TRANSMIT_FAIL ((uint8_t) 1)

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Function responsible for formatting and sending command to server.        */
uint8_t CMD_Transmit(cmd_noun_t noun, cmd_verb_t verb, uint8_t *data);

#endif /* CMD_TRANSMIT_H_ */
