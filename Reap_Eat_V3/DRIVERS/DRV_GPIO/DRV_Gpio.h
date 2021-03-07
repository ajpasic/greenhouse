/******************************************************************************/
/*  Filename:   DRV_Gpio.h                                                    */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  PB0   DOUT     Peltier cooling module.                                    */
/*  PB1   DOUT     Internal ventilation fan.                                  */
/*  PB4   DOUT     PTC Heating module.                                        */
/*  PB5   DOUT     Ultrasonic transducer humidifier.                          */
/*  PA2   DOUT     External exhaust fan.                                      */
/*  PA3   DOUT     Irrigation                                                 */
/*  PA4   DOUT     Humidifier tank filler.                                    */
/*  PE1   DIN      Door switch signal.                                        */
/*  PF1   DOUT     Status LED.                                                */
/*                                                                            */
/******************************************************************************/

#ifndef DRIVERS_DRV_GPIO_H_
#define DRIVERS_DRV_GPIO_H_

#include "DRV_Initialization.h"

typedef enum
{
    COOLER,
    HEATER,
    FAN_INTERNAL,
    FAN_EXTERNAL,
    IRRIGATION,
    HUMIDIFIER_FILLER,
    DOOR_SWITCH,
    HEARTBEAT_LED,
    BUZZER,

    SIZE_OF_DOUT_TABLE

} drv_digital_io_t;


void DRV_Gpio_Set_High(drv_digital_io_t);

void DRV_Gpio_Set_Low(drv_digital_io_t);

bool DRV_Gpio_Is_High(drv_digital_io_t);

void DRV_Gpio_Enable_Interrupt(drv_digital_io_t);

void DRV_Gpio_Disable_Interrupt(drv_digital_io_t);

//void DRV_Gpio_Clear_Interrupt(drv_digital_io_t);

#endif /* DRIVERS_DRV_GPIO_H_ */
