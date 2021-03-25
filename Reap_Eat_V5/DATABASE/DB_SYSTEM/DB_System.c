/*
 * DB_System.c
 *
 *  Created on: Mar 14, 2021
 *      Author: juanleyva
 */

#include "DB_System.h"

void DB_System_Write(DB_system_id_t id, DB_system_status_t status)
{
    if (id < SIZE_OF_SYSTEM_STATUS_TABLE)
    {
        g_system_status[id] = status;
    }
}

DB_system_status_t DB_System_Read(DB_system_id_t id)
{
    if (id < SIZE_OF_SYSTEM_STATUS_TABLE)
    {
        return g_system_status[id];
    }
    else
    {
        return SIZE_OF_SYSTEM_STATUS_TABLE;
    }
}
