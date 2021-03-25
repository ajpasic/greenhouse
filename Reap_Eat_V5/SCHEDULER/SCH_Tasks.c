/*
 * SCH_Tasks.c
 *
 *  Created on: Mar 16, 2021
 *      Author: juanleyva
 */

#include "SCH_Tasks.h"

void SCH_Database_Measurement_Update(void)
{
    char debug_str[32];
    uint16_t debug_values[7];

    HW_Debug_Print("\n\r\t\t  ----------------Database Dump---------------\n\r");
    HW_Debug_Print("Temp[°C]   Humd[%RH]   Temp SP[°C]   Humd SP[%RH]   Light[%]   Door[O/C]\n\r");
    DB_Control_Subsystem_Write(CONTROL_TEMPERATURE,  ENABLE);
    Task_sleep(500 * (1000 / Clock_tickPeriod));

    while(1)
    {
        HW_Ambient_Sensor_Refresh();

        if (DB_System_Read(SENSOR_AMBIENT) == ACTIVE)
        {
            DB_Measurement_Write(MEASURE_TEMPERATURE, (uint32_t)HW_Ambient_Sensor_Get_Temp());
            DB_Measurement_Write(MEASURE_HUMIDITY, (uint32_t)HW_Ambient_Sensor_Get_Humd());
        }
        else
        {
            uint8_t data[4] = {(uint8_t)CRITICAL, (uint8_t)AMBIENT_SENSOR_FAILURE, 0, 0};
            CMD_Transmit(SYSTEM, ALERT, data);
        }
        //DB_Measurement_Write(MEASURE_WATERING, (uint32_t)HW_Irrigation_Get());
        DB_Measurement_Write(MEASURE_LIGHT_INTENSITY, (uint32_t)HW_Light_Get_Intensity());
        //DB_Measurement_Write(MEASURE_MAIN_TANK_LEVEL,HW_Tank_Main_Get());
        //DB_Measurement_Write(MEASURE_HUMD_TANK_LEVEL, HW_Tank_Humd_Get());
        DB_Measurement_Write(MEASURE_DOOR_SWITCH_STATE, (uint32_t)HW_Door_Is_Open());

        debug_values[0] = (uint16_t)(DB_Measurement_Read(MEASURE_TEMPERATURE));
        debug_values[1] = (uint16_t)(DB_Measurement_Read(MEASURE_HUMIDITY));
        debug_values[2] = (uint16_t)(DB_Control_Setpoint_Read(SETPOINT_TEMPERATURE));
        debug_values[3] = (uint16_t)(DB_Control_Setpoint_Read(SETPOINT_HUMIDITY));
        debug_values[4] = (uint16_t)(DB_Measurement_Read(MEASURE_LIGHT_INTENSITY));
        debug_values[5] = (uint16_t)(DB_Measurement_Read(MEASURE_DOOR_SWITCH_STATE)? 'O' : 'C');

        sprintf(debug_str, "%d.%2d      %d.%2d\t%d.%2d\t     %d.%2d\t    %d\t\t%c   \r\0",
               (debug_values[0]/100), (debug_values[0] % 100),
               (debug_values[1]/100), (debug_values[1] % 100),
               (debug_values[2]/100), (debug_values[2] % 100),
               (debug_values[3]/100), (debug_values[3] % 100),
               debug_values[4], debug_values[5]);

        HW_Debug_Print(debug_str);

        Task_sleep(200 * (1000 / Clock_tickPeriod));
    }
}

void SCH_Control(void)
{
    int32_t temp_setpoint_lower;
    int32_t temp_setpoint_upper;
    uint32_t counter = 0;
    uint8_t temp_running_mode = 0;

    DB_Control_Setpoint_Write(SETPOINT_TEMPERATURE, 27*100);
    Task_sleep(1000 * (1000 / Clock_tickPeriod));

    while(1)
    {
        if (DB_Control_Subsystem_Read(CONTROL_TEMPERATURE) == ENABLE)
        {
            temp_setpoint_lower  = ((DB_Control_Setpoint_Read(SETPOINT_TEMPERATURE) - 150));
            temp_setpoint_upper  = ((DB_Control_Setpoint_Read(SETPOINT_TEMPERATURE) + 150));

            if (temp_running_mode == 1)
            {
                if (DB_Measurement_Read(MEASURE_TEMPERATURE) < (temp_setpoint_upper - 100)
                &&  DB_Measurement_Read(MEASURE_TEMPERATURE) > (temp_setpoint_lower + 100))
                {
                    temp_running_mode = 0;
                }

                if (counter++ > 2400)
                {
                    DB_Control_Subsystem_Write(CONTROL_TEMPERATURE, DISABLE);
                    HW_Heater_Off();
                    HW_Cooler_Off();
                    HW_Fan_Internal_Off();
                    counter = 0;
                    uint8_t data[4] = {(uint8_t)CRITICAL, (uint8_t)TEMPERATURE_CONTROL_TIMEOUT, 0, 0};
                    CMD_Transmit(SYSTEM, ALERT, data);
                }
            }
            else
            {
                if (DB_Measurement_Read(MEASURE_TEMPERATURE) < temp_setpoint_lower)
                {
                    HW_Cooler_Off();
                    HW_Heater_On();
                    HW_Fan_Internal_On();
                    temp_running_mode = 1;
                }
                else if (DB_Measurement_Read(MEASURE_TEMPERATURE) > temp_setpoint_upper)
                {
                    HW_Heater_Off();
                    HW_Cooler_On();
                    HW_Fan_Internal_On();
                    HW_Fan_External_On();
                    temp_running_mode = 1;
                }
                else
                {
                    HW_Heater_Off();
                    HW_Cooler_Off();
                    HW_Fan_Internal_Off();
                    HW_Fan_External_Off();
                    temp_running_mode = 0;
                }
            }
        }
        else
        {
            HW_Heater_Off();
            HW_Cooler_Off();
        }

        HW_Heartbeat_Toggle();

        Task_sleep(200 * (1000 / Clock_tickPeriod));
    }
}

void SCH_Receive_Server_Command(void)
{
    while(1)
    {
        Semaphore_pend(semaphore0, BIOS_WAIT_FOREVER);
        CMD_Receive();
    }
}
