/*
 * DB_System.h
 *
 *  Created on: Mar 14, 2021
 *      Author: juanleyva
 */

#ifndef DATABASE_DB_SYSTEM_DB_SYSTEM_H_
#define DATABASE_DB_SYSTEM_DB_SYSTEM_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <stdint.h>

/******************************************************************************/
/*                             ENUM DECLARATIONS                              */
/******************************************************************************/

typedef enum
{
    FAILURE = 0,
    ACTIVE,
    INACTIVE,

    SIZE_OF_SYSTEM_STATUS_TABLE

} DB_system_status_t;

typedef enum
{
    SYSTEM_OVERALL = 0,
    SENSOR_AMBIENT,
    SENSOR_MAIN_TANK,
    SENSOR_HUMD_TANK,
    SENSOR_DOOR_SWITCH,
    ACTUATOR_COOLER,
    ACTUATOR_HEATER,
    ACTUATOR_EXT_FAN,
    ACTUATOR_INT_FAN,
    ACTUATOR_HUMIDIFIER,
    ACTUATOR_VENT,

    SIZE_OF_SYSTEM_TABLE

} DB_system_id_t;

/******************************************************************************/
/*                             GLOBAL VARIABLES                               */
/******************************************************************************/

/*  Global array for storing system statuses as 8-bit value.                  */
volatile DB_system_status_t g_system_status[SIZE_OF_SYSTEM_TABLE];

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION                         */
/******************************************************************************/

void DB_System_Write(DB_system_id_t id, DB_system_status_t status);

DB_system_status_t DB_System_Read(DB_system_id_t id);

#endif /* DATABASE_DB_SYSTEM_DB_SYSTEM_H_ */
