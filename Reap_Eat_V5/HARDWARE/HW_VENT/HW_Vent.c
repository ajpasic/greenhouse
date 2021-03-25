/******************************************************************************/
/*  Filename:   HW_Vent.c                                                     */
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

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <HW_Vent.h>

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Open the vent by driving the servo motor in the open positon.             */
void HW_Vent_Open(void)
{
    /* Set the duty cyle of the PWM signal that goes to the vent servo to set */
    /* the servo to the open state position.                                  */
    DRV_Pwm_Set_Duty_Cycle(VENT_SERVO, OPEN_STATE_DUTY_CYCLE);
}

/*  Close the vent by driving the servo motor in the close positon.           */
void HW_Vent_Close(void)
{
    /* Set the duty cyle of the PWM signal that goes to the vent servo to set */
    /* the servo to the close state position.                                 */
    DRV_Pwm_Set_Duty_Cycle(VENT_SERVO, CLOSE_STATE_DUTY_CYCLE);
}
