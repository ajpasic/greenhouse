/*
 * DB_Control.c
 *
 *  Created on: Mar 14, 2021
 *      Author: juanleyva
 */

#include "DB_Control.h"


void DB_Control_Setpoint_Write(DB_control_setpoint_t id, const uint32_t value)
{
    /*  If ID is valid.                                                       */
    if (id < SIZE_OF_CONTROL_SETPOINT_TABLE)
    {
        g_control_setpoint[id] = (uint32_t)value;
    }
}

void DB_Control_Subsystem_Write(DB_control_subsystem_t id, const uint8_t value)
{
    /*  If ID is valid.                                                       */
    if (id < SIZE_OF_CONTROL_SUBSYSTEM_TABLE)
    {
        g_control_subsystem[id] = (uint32_t)value;
    }
}

uint32_t DB_Control_Setpoint_Read(DB_control_setpoint_t id)
{
    /*  If ID is valid.                                                       */
    if (id < SIZE_OF_CONTROL_SETPOINT_TABLE)
    {
        return g_control_setpoint[id];
    }
    else
    {
        return 0xFF;
    }
}

uint8_t DB_Control_Subsystem_Read(DB_control_subsystem_t id)
{
    /*  If ID is valid.                                                       */
    if (id < SIZE_OF_CONTROL_SUBSYSTEM_TABLE)
    {
        return g_control_subsystem[id];
    }
    else
    {
        return 0xFF;
    }
}
