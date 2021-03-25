/******************************************************************************/
/*  Filename:   HW_Buzzer.c                                                   */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Buzzer hardware module used to interface with buzzer hardware. The buzzer */
/*  can only be turned on or off. The buzzer interfaces with through the      */
/*  following pin and module:                                                 */
/*                                                                            */
/*  PB5   DOUT     Alert Buzzer.                                              */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Buzzer.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Turn on the buzzer.                                                       */
void HW_Buzzer_On(void)
{
    /*  Set buzzer PWM signal's to 50 percent duty cycle.                     */
    DRV_Gpio_Set_High(BUZZER);
}

/*  Turn off the buzzer.                                                      */
void HW_Buzzer_Off(void)
{
    /*  Set buzzer PWM signal's to 0 percent duty cycle, basically off.       */
    DRV_Gpio_Set_Low(BUZZER);
}
