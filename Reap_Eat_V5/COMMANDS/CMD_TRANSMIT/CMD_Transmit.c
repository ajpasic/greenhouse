/******************************************************************************/
/*  Filename:   CMD_Transmit.c                                                */
/*  Created on: Mar 13, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  This module deals with the transmission of commands from  controller to   */
/*  server mcu.                                                               */
/******************************************************************************/


/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "CMD_Transmit.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Function responsible for formatting and sending command to server.        */
uint8_t CMD_Transmit(cmd_noun_t noun, cmd_verb_t verb, uint8_t *data)
{
    uint8_t result = 0;
    uint8_t cmd_message[CMD_WORD_SIZE];

    /* If noun and verb of command is valid proceed.                          */
    if (noun < SIZE_OF_NOUN_TABLE && verb < SIZE_OF_VERB_TABLE)
    {
        /*  Format command message bytes.                                     */
        cmd_message[0] = (uint8_t)noun;
        cmd_message[1] = (uint8_t)verb;
        cmd_message[2] = (uint8_t)data[0];
        cmd_message[3] = (uint8_t)data[1];
        cmd_message[4] = (uint8_t)data[2];
        cmd_message[5] = (uint8_t)data[3];
        cmd_message[6] = (uint8_t)0xFF;

        /*  Send command message to server.                                   */
        HW_Server_Send(cmd_message, CMD_WORD_SIZE);

        /*  Transmission succesful.                                           */
        result = CMD_TRANSMIT_OK;
    }
    else
    {
        /*  Transmission failed.                                              */
        result = CMD_TRANSMIT_FAIL;
    }

    /*  Return result.                                                        */
    return result;
}
