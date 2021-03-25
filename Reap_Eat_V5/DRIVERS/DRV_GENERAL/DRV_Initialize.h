/******************************************************************************/
/*  Filename:   DRV_Initialization.h                                          */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*                                                                            */
/*  PB2   I2C0SCL  BME280 temperature and humidity Sensor.                    */
/*  PB3   I2C0SDA  BME280 temperature and humidity Sensor.                    */
/*  PA0   U0RX     UART PC serial communication.                              */
/*  PA1   U0TX     UART PC serial communication.                              */
/*  PC4   U1RX     UART ESP32 serial communication.                           */
/*  PC5   U1TX     UART ESP32 serial communication.                           */
/*  PB0   DOUT     Peltier cooling module.                                    */
/*  PB1   DOUT     Internal ventilation fan.                                  */
/*  PB4   M0PWM2   LED lighting.                                              */
/*  PB5   DOUT     Alert Buzzer.                                              */
/*  PB6   M0PWM0   Vent servos.                                               */
/*  PB7   DOUT     PTC Heating module.                                        */
/*  PA2   DOUT     External exhaust fan.                                      */
/*  PA3   DOUT     Irrigation                                                 */
/*  PA4   DOUT     Humidifier tank filler.                                    */
/*  PE4   M0PWM4   Ultrasonic transducer humidifier.  .                       */
/*  PE1   DIN      Door switch signal.                                        */
/*  PE2   AIN1     Main water tank level analog signal.                       */
/*  PF1   DOUT     Status LED.                                                */
/*                                                                            */
/******************************************************************************/

#ifndef DRIVERS_DRV_INITIALIZATION_H_
#define DRIVERS_DRV_INITIALIZATION_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <inc/hw_sysctl.h>
#include <inc/hw_gpio.h>
#include <inc/hw_i2c.h>
#include <inc/hw_uart.h>
#include <inc/hw_pwm.h>

#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/i2c.h>
#include <driverlib/uart.h>
#include <driverlib/pwm.h>

#include "utils/uartstdio.h"


/******************************************************************************/
/*                                  DEFINES                                   */
/******************************************************************************/

/*  Macros for PWM periods for various periodic reqirements signals.          */
#define PWM_SERVO_PERIOD     ((uint32_t) 39700)   /* Period for 50 Hz PWM.    */
#define PWM_LED_PERIOD       ((uint32_t) 16500)   /* Period for 120 Hz PWM.   */
//#define PWM_HUMIDIFER_PERIOD ((uint32_t)    17)


/******************************************************************************/
/*                          FUNCTION DECLARATION                              */
/******************************************************************************/

extern void DRV_Init(void);

extern void DRV_Gpio_PortE_Handler(void);

#endif /* DRIVERS_DRV_INITIALIZATION_H_ */
