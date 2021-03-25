/*
 * CMD_Receive.c
 *
 *  Created on: Mar 14, 2021
 *      Author: juanleyva
 */

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "CMD_Receive.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

void CMD_Receive(void)
{
    uint8_t word[CMD_WORD_SIZE + 2];
    HW_Server_Receive(word, CMD_WORD_SIZE + 2);

    cmd_noun_t noun = (cmd_noun_t)word[0];
    cmd_verb_t verb = (cmd_verb_t)word[1];
    uint8_t data[4] = {word[2], word[3], word[4], word[5]};

    CMD_Execute(noun, verb, data);
}

/*  Function responsible for formatting received messages from server.        */
void CMD_Execute(cmd_noun_t noun, cmd_verb_t verb, uint8_t data[4])
{
    /*  If the noun and the verb is valid                                     */
    if (noun < SIZE_OF_NOUN_TABLE && verb < SIZE_OF_VERB_TABLE)
    {
        if (noun == TEMPERATURE)
        {
            if (verb == SET)
            {
                DB_Control_Setpoint_Write(SETPOINT_TEMPERATURE, (uint32_t) (data[0] * 100));
            }
            else if(verb == GET)
            {
                /* If the sensor is working, proceed with getting measurement */
                /* otherwise send alert message.                              */
                if (DB_System_Read(SENSOR_AMBIENT) != FAILURE)
                {
                    data[0] = (uint8_t)(DB_Measurement_Read(MEASURE_TEMPERATURE)/100);
                    data[1] = 0; data[2] = 0; data[3] = 0;
                    CMD_Transmit(noun, verb, data);
                }
                else
                {
                    data[0] = (uint8_t)CRITICAL;
                    data[1] = (uint8_t)AMBIENT_SENSOR_FAILURE;
                    data[2] = 0; data[3] = 0;
                    CMD_Transmit(noun, ALERT, data);
                }
            }
        }

        else if (noun == HUMIDITY)
        {
            if (verb == SET)
            {
                DB_Control_Setpoint_Write(SETPOINT_HUMIDITY, (uint32_t) (data[0] * 100));
            }
            else if (verb == GET)
            {
                /* If the sensor is working, proceed with getting measurement */
                /* otherwise send alert message.                              */
                if (DB_System_Read(SENSOR_AMBIENT) != FAILURE)
                {
                    data[0] = (uint8_t)(DB_Measurement_Read(MEASURE_HUMIDITY)/100);
                    data[1] = 0; data[2] = 0; data[3] = 0;
                    CMD_Transmit(noun, verb, data);
                }
                else
                {
                    data[0] = (uint8_t)CRITICAL;
                    data[1] = (uint8_t)AMBIENT_SENSOR_FAILURE;
                    data[2] = 0; data[3] = 0;
                    CMD_Transmit(noun, ALERT, data);
                }
            }
        }
        else if (noun == WATERING)
        {
            if (verb == SET)
            {
                DB_Control_Setpoint_Write(SETPOINT_WATERING_DURATION, (uint32_t) (data[0] * 100));
                DB_Control_Setpoint_Write(SETPOINT_WATERING_VOLUME, (uint32_t) (data[1] * 100));
            }
            else if (verb == GET)
            {
                if (1) //DB_System(
                {
                    data[0] = (uint8_t)DB_Measurement_Read(MEASURE_WATERING);
                    data[1] = 0; data[2] = 0;  data[3] = 0;
                    CMD_Transmit(noun, verb, data);
                }
                else
                {
                    data[0] = (uint8_t)CRITICAL;
                    data[1] = (uint8_t)TYPE_2;
                    data[2] = 0; data[3] = 0;
                    CMD_Transmit(noun, ALERT, data);
                }
            }
        }
        else if (noun == LIGHTING)
        {
            if (verb == SET)
            {
                DB_Control_Setpoint_Write(SETPOINT_LIGHTING_HOURS, (uint32_t) (data[0] * 100));
            }
            else if (verb == GET)
            {
                if (1)
                {
                    data[0] = (uint8_t)DB_Measurement_Read(MEASURE_LIGHT_INTENSITY);
                    data[1] = (uint8_t)DB_Measurement_Read(MEASURE_LIGHTING_HOURS) / 100;
                    data[2] = 0; data[3] = 0;
                    CMD_Transmit(noun, verb, data);
                }
                else
                {
                    data[0] = (uint8_t)CRITICAL;
                    data[1] = (uint8_t)TYPE_3;
                    data[2] = 0; data[3] = 0;
                    CMD_Transmit(noun, ALERT, data);
                }
            }
        }
        else if (noun == SYSTEM)
        {
            if (verb == SET)
            {
                //CTL_Process_Set();
                ///
                //DB_Control
            }
            else if (verb == GET)
            {
                if (1)
                {
                    //data[0] = (uint8_t)DB_System_Read((uint32_t)data[0]);
                }
                else
                {

                }
            }
        }
    }
}

