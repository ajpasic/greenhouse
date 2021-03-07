/******************************************************************************/
/*  Filename:   HW_Vent.h                                                     */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Vent hardware module used to interface with the servo motor that drives   */
/*  the vent hardware. The vent can be either opened or closed. Macros are    */
/*  provided to define the duty cycle of the servo motor signal to set the    */
/*  servo shaft in the open and close positions. Tunning of the position of   */
/*  the servo shaft can be done by changing the macros on this file.          */
/*  The LED light interfaces through the following pin and module:            */
/*                                                                            */
/*  PB6   M0PWM0   Vent servos.                                               */
/*                                                                            */
/******************************************************************************/

#ifndef HARDWARE_HW_SERVO_H_
#define HARDWARE_HW_SERVO_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Pwm.h"

/******************************************************************************/
/*                             MACRO DEFINITIONS                              */
/******************************************************************************/

#define OPEN_STATE_DUTY_CYCLE   ((uint8_t)10)   /* 10% duty cycle for PWM.    */
#define CLOSE_STATE_DUTY_CYCLE  ((uint8_t) 5)   /* 05% duty cycle for PWM.    */

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Open the vent by driving the servo motor in the open positon.             */
void HW_Vent_Open(void);

/*  Close the vent by driving the servo motor in the close positon.           */
void HW_Vent_Close(void);

#endif /* HARDWARE_HW_SERVO_H_ */
