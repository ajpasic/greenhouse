/*
 * DB_Control.h
 *
 *  Created on: Mar 14, 2021
 *      Author: juanleyva
 */

#ifndef DB_CONTROL_H_
#define DB_CONTROL_H_

#include <stdint.h>

typedef enum
{
    SETPOINT_TEMPERATURE = 0,
    SETPOINT_HUMIDITY,
    SETPOINT_WATERING_DURATION,
    SETPOINT_WATERING_VOLUME,
    SETPOINT_LIGHTING_HOURS,

    SIZE_OF_CONTROL_SETPOINT_TABLE

} DB_control_setpoint_t;

typedef enum
{
    CONTROL_TEMPERATURE = 0,
    CONTROL_HUMIDITY,
    CONTROL_WATERING,
    CONTROL_LIGHTING,

    SIZE_OF_CONTROL_SUBSYSTEM_TABLE

} DB_control_subsystem_t;

typedef enum
{
    DISABLE = 0,
    ENABLE,

    SIZE_OF_SUBSYSTEM_STATUS_TABLE

} DB_control_subsystem_status_t;

volatile uint32_t g_control_setpoint[SIZE_OF_CONTROL_SETPOINT_TABLE];
volatile uint8_t g_control_subsystem[SIZE_OF_CONTROL_SUBSYSTEM_TABLE];

void DB_Control_Setpoint_Write(DB_control_setpoint_t id, const uint32_t value);
void DB_Control_Subsystem_Write(DB_control_subsystem_t id, const uint8_t value);

uint32_t DB_Control_Setpoint_Read(DB_control_setpoint_t id);
uint8_t DB_Control_Subsystem_Read(DB_control_subsystem_t id);

#endif /* DB_CONTROL_H_ */
