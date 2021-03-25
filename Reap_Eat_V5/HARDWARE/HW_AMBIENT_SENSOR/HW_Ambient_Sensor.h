/*
 * HW_Ambient.h
 *
 *  Created on: Feb 21, 2021
 *      Author: juanleyva
 */

#ifndef HARDWARE_HW_AMBIENT_H_
#define HARDWARE_HW_AMBIENT_H_

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#include "DRV_I2c.h"
#include "HW_Debug_Com.h"
#include "DB_System.h"
#include "DB_Control.h"


//#define BME280_32BIT_ENABLE
#include "bme280.h"

struct identifier
{
    /* Variable to hold device address */
    uint8_t dev_addr;

    /* Variable that contains file descriptor */
    int8_t fd;
};

struct bme280_dev dev;
struct identifier id;

struct bme280_data comp_data;

uint32_t req_delay;

//extern uint8_t ambient_sensor_initialized = 1;

void HW_Ambient_Sensor_Init(void);

int32_t HW_Ambient_Sensor_Get_Temp(void);

uint32_t HW_Ambient_Sensor_Get_Humd(void);

void HW_Ambient_Sensor_Refresh(void);

int8_t HW_Ambient_Sensor_I2C_Write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

int8_t HW_Ambient_Sensor_I2C_Read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

void HW_Ambient_Sensor_I2C_Delay(uint32_t period, void *intf_ptr);



#endif /* HARDWARE_HW_AMBIENT_H_ */
