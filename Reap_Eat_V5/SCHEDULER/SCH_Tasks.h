/*
 * SCH_Tasks.h
 *
 *  Created on: Mar 16, 2021
 *      Author: juanleyva
 */

#ifndef SCH_TASKS_H_
#define SCH_TASKS_H_

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include <xdc/cfg/global.h>

#include "HW_Ambient_Sensor.h"
#include "HW_Door.h"
#include "HW_Light.h"
#include "HW_Debug_Com.h"
#include "HW_Cooler.h"
#include "HW_Heater.h"
#include "HW_Fan_Internal.h"
#include "HW_Fan_External.h"
#include "HW_Buzzer.h"
#include "HW_Heartbeat.h"
#include "DB_Measurement.h"
#include "CMD_Receive.h"
#include "CMD_Transmit.h"

void SCH_Database_Measurement_Update(void);

void SCH_Receive_Server_Command(void);

#endif /* SCH_TASKS_H_ */
