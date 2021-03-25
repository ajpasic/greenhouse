/*
 * HW_Ambient_Sensor.c
 *
 *  Created on: Mar 8, 2021
 *      Author: juanleyva
 */

#include "HW_Ambient_Sensor.h"

void HW_Ambient_Sensor_Init(void)
{
    /* Variable to define the result */
    int8_t rslt = BME280_OK;

    /* Make sure to select BME280_I2C_ADDR_PRIM or BME280_I2C_ADDR_SEC as needed */
    id.dev_addr = BME280_I2C_ADDR_PRIM;

    dev.intf = BME280_I2C_INTF;
    dev.read = (bme280_read_fptr_t) HW_Ambient_Sensor_I2C_Read;
    dev.write = (bme280_write_fptr_t) HW_Ambient_Sensor_I2C_Write;
    dev.delay_us = (bme280_delay_us_fptr_t) HW_Ambient_Sensor_I2C_Delay;

    /* Update interface pointer with the structure that contains both device address and file descriptor */
    dev.intf_ptr = &id;

    /* Initialize the bme280 */
    rslt = bme280_init(&dev);

    if (rslt != BME280_OK)
    {
        HW_Debug_Print("Failed to initialize BME280.\n\r");
        DB_System_Write(SENSOR_AMBIENT, FAILURE);
        DB_Control_Subsystem_Write(CONTROL_TEMPERATURE, DISABLE);
        DB_Control_Subsystem_Write(CONTROL_HUMIDITY, DISABLE);
    }
    else
    {
        uint8_t settings_sel;

        /* Recommended mode of operation: Indoor navigation */
        dev.settings.osr_h = BME280_OVERSAMPLING_1X;
        dev.settings.osr_p = BME280_OVERSAMPLING_16X;
        dev.settings.osr_t = BME280_OVERSAMPLING_2X;
        dev.settings.filter = BME280_FILTER_COEFF_16;

        settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

        rslt = bme280_set_sensor_settings(settings_sel, &dev);

        if (rslt != BME280_OK)
        {
            HW_Debug_Print("Failed to set BME280 sensor settings.\n\r");
            DB_System_Write(SENSOR_AMBIENT, FAILURE);
            DB_Control_Subsystem_Write(CONTROL_TEMPERATURE, DISABLE);
            DB_Control_Subsystem_Write(CONTROL_HUMIDITY, DISABLE);
        }
        else
        {
            DB_System_Write(SENSOR_AMBIENT, ACTIVE);
        }
    }
}

int32_t HW_Ambient_Sensor_Get_Temp(void)
{
 //   HW_Ambient_Sensor_Refresh();
    return (comp_data.temperature * 100);
}

uint32_t HW_Ambient_Sensor_Get_Humd(void)
{
   // HW_Ambient_Sensor_Refresh();
    return (comp_data.humidity * 100);
}

void HW_Ambient_Sensor_Refresh(void)
{
    int8_t rslt;

    if (DB_System_Read(SENSOR_AMBIENT) != FAILURE)
    {
        rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);

        if (rslt != BME280_OK)
        {
            HW_Debug_Print("Failed to set BME280 sensor mode.\n\r");
            DB_System_Write(SENSOR_AMBIENT, FAILURE);
            DB_Control_Subsystem_Write(CONTROL_TEMPERATURE, DISABLE);
            DB_Control_Subsystem_Write(CONTROL_HUMIDITY, DISABLE);
        }
        else
        {
            DB_System_Write(SENSOR_AMBIENT, ACTIVE);
        }

        Task_sleep(70 * (1000 / Clock_tickPeriod));

        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);

        if (rslt != BME280_OK)
        {
            HW_Debug_Print("Failed to get BME280 sensor data.\n\r");
            DB_System_Write(SENSOR_AMBIENT, FAILURE);
            DB_Control_Subsystem_Write(CONTROL_TEMPERATURE, DISABLE);
            DB_Control_Subsystem_Write(CONTROL_HUMIDITY, DISABLE);
        }
        else
        {
            DB_System_Write(SENSOR_AMBIENT, ACTIVE);
        }
    }
}

int8_t HW_Ambient_Sensor_I2C_Read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    return DRV_I2c_Read(id.dev_addr, reg_addr, reg_data, len);
}

int8_t HW_Ambient_Sensor_I2C_Write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    return DRV_I2c_Write(id.dev_addr, reg_addr, reg_data, len);
}

void HW_Ambient_Sensor_I2C_Delay(uint32_t period, void *intf_ptr)
{
    SysCtlDelay((uint32_t)(period / 1.0 * 1000.0 * 0.023854962));
}
