/******************************************************************************/
/*  Filename:   CMD_Receive.h                                                 */
/*  Created on: Mar 13, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  This module deals with receiving commands from server.                    */
/******************************************************************************/


#ifndef CMD_RECEIVE_H_
#define CMD_RECEIVE_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <stdint.h>
#include "CMD_Transmit.h"
#include "CMD_General.h"
#include "DB_Measurement.h"
#include "DB_System.h"
#include "DB_Control.h"



/******************************************************************************/
/*                             MACRO DEFINITIONS                              */
/******************************************************************************/

#ifndef CMD_WORD_SIZE
#define CMD_WORD_SIZE     ((uint8_t) 7)
#endif

#define CMD_RECEIVE_OK    ((uint8_t) 0)
#define CMD_RECEIVE_FAIL  ((uint8_t) 1)

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Function responsible with formatting received messages from server.       */
void CMD_Receive(void);

/*  Function responsible for executing command from server.                   */
void CMD_Execute(cmd_noun_t noun, cmd_verb_t verb, uint8_t data[4]);

#endif /* CMD_RECEIVE_H_ */
