/******************************************************************************/
/*  Filename:   DRV_I2C.h                                                     */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*                                                                            */
/*  PB2   I2C0SCL  BME280 temperature and humidity Sensor.                    */
/*  PB3   I2C0SDA  BME280 temperature and humidity Sensor.                    */
/*                                                                            */

#ifndef DRIVERS_DRV_I2C_H_
#define DRIVERS_DRV_I2C_H_

#include "DRV_Initialize.h"

int8_t DRV_I2c_Read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint32_t len);

int8_t DRV_I2c_Write(uint8_t id, uint8_t reg_addr, const uint8_t *data, uint32_t len);

#endif /* DRIVERS_DRV_I2C_H_ */
