/*                                                                            */
/* DRV_Pwm.h                                                                  */
/*                                                                            */
/*  Created on: Feb 21, 2021                                                  */
/*      Author: juanleyva                                                     */
/*  PB4   M0PWM2   LED lighting.                                              */
/*  PB6   M0PWM0   Vent servos.                                               */
/*  PE4   M0PWM4   Alert buzzer.                                              */
/*                                                                            */
/******************************************************************************/

#ifndef DRIVERS_DRV_PWM_H_
#define DRIVERS_DRV_PWM_H_

#include "DRV_Initialization.h"

typedef enum
{
    VENT_SERVO,
    LIGHT,
    HUMIDIFIER

} drv_pwm_io_t;

void DRV_Pwm_Set_Duty_Cycle(drv_pwm_io_t, uint8_t);


#endif /* DRIVERS_DRV_PWM_H_ */
