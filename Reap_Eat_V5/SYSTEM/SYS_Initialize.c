/*
 * SYS_Init.c
 *
 *  Created on: Mar 16, 2021
 *      Author: juanleyva
 */

#include "SYS_Initialize.h"

void SYS_Init(void)
{
    DB_Init();
    DRV_Init();

    HW_Ambient_Sensor_Init();
}

