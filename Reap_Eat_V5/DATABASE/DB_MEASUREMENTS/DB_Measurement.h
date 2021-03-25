/******************************************************************************/
/*  Name: DB_Measurements.h                                                    */
/*  Author: Juan Leyva                                                        */
/*  Created On: Feb 12, 2021                                                  */
/*                                                                            */
/*  Functionality: This module provides read and write operations of global   */
/*                 measurement table.                                         */
/******************************************************************************/

#ifndef DB_MEASUREMENTS_H_
#define DB_MEASUREMENTS_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
/*                             ENUM DECLARATIONS                              */
/******************************************************************************/

/*  Enumerated type for sensor measurement IDs used to index measurements.    */
typedef enum
{
    MEASURE_TEMPERATURE,        /* Enclosure temperature in deg C x 100.      */
    MEASURE_HUMIDITY,           /* Enclosure humidity in % RH x 100.          */
    MEASURE_WATERING,           /* Watering measurements (relative vol.%)     */
    MEASURE_LIGHT_INTENSITY,    /* Current light intensity as a percent.      */
    MEASURE_LIGHTING_HOURS,     /* Number of hours light has be on x 100.     */
    MEASURE_MAIN_TANK_LEVEL,    /* Main tank water level as a percentage.     */
    MEASURE_HUMD_TANK_LEVEL,    /* Humd. tank water level as a percentage.    */
    MEASURE_DOOR_SWITCH_STATE,  /* Door switch state as open/close (1/0).     */

    SIZE_OF_MEASUREMENT_TABLE  /* Size of global measurements table.          */

} DB_measurement_id_t;

/******************************************************************************/
/*                             GLOBAL VARIABLES                               */
/******************************************************************************/

/*  Global array for storing sensor measurement data as 32-bit value.         */
volatile uint32_t g_measurement[SIZE_OF_MEASUREMENT_TABLE];

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION                         */
/******************************************************************************/

/*  Write sensor measurement data in global array.                            */
void DB_Measurement_Write(DB_measurement_id_t, const uint32_t);

/* Reads measurements data.                                                   */
uint32_t DB_Measurement_Read(DB_measurement_id_t);

#endif /* DB_MEASUREMENTS_H_ */
