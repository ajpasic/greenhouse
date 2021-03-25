/******************************************************************************/
/*  Name: DB_Measurement.h                                                    */
/*  Author: Juan Leyva                                                        */
/*  Created On: Feb 12, 2021                                                  */
/*                                                                            */
/*  Functionality: This module provides read and write operations of global   */
/*                 measurement table.                                         */
/******************************************************************************/

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <DB_Measurement.h>

/******************************************************************************/
/*  Name: DB_Measurement_Write                                                */
/*  Inputs: id                                                                */
/*          value                                                             */
/*  Output: none                                                              */
/*  Funcitonality: Writes sensor measurements in global array.                */
/******************************************************************************/

void DB_Measurement_Write(DB_measurement_id_t id, const uint32_t value)
{
    /*  If ID is valid.                                                       */
    if (id < SIZE_OF_MEASUREMENT_TABLE)
    {
        g_measurement[id] = (uint32_t)value;
    }
}

/******************************************************************************/
/*  Name: DB_Measurement_Read                                                 */
/*  Inputs: id                                                                */
/*  Output: none                                                              */
/*  Funcitonality: Read sensor measurements in global array.                */
/******************************************************************************/

uint32_t DB_Measurement_Read(DB_measurement_id_t id)
{
    /*  If ID is valid.                                                       */
    if (id < SIZE_OF_MEASUREMENT_TABLE)
    {
        return g_measurement[id];
    }
    else
    {
        return 0xFF;
    }
}
