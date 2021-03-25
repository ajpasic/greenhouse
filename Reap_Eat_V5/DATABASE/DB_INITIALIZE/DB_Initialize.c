/*
 * DB_Initialize.c
 *
 *  Created on: Mar 15, 2021
 *      Author: juanleyva
 */

#include "DB_Initialize.h"

void DB_Init(void)
{
    uint8_t index;

    for(index = 0; index < SIZE_OF_MEASUREMENT_TABLE; index++)
    {
        DB_Measurement_Write((DB_measurement_id_t)index, 0);
    }

    for(index = 0; index < SIZE_OF_CONTROL_SETPOINT_TABLE; index++)
    {
        DB_Control_Setpoint_Write((DB_control_setpoint_t)index, 0);
    }

    for(index = 0; index < SIZE_OF_CONTROL_SUBSYSTEM_TABLE; index++)
   {
        DB_Control_Subsystem_Write((DB_control_subsystem_t)index, DISABLE);
   }

    for(index = 0; index < SIZE_OF_SYSTEM_TABLE; index++)
    {
        DB_System_Write((DB_system_id_t)index, FAILURE);
    }
}
