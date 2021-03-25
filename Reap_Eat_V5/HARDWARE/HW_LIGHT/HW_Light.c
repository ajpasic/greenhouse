/******************************************************************************/
/*  Filename:   HW_Light.c                                                    */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Light hardware module used to interface with the LED light hardware. The  */
/*  LED light can be turned on or off or be set to certain intensity as a     */
/*  percentage. The LED light interfaces through the following pin and module:*/
/*                                                                            */
/*  PB4   M0PWM2   LED lighting.                                              */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Light.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Set light intensity as a percentage (0 to 100).                           */
void HW_Light_Set_Intensity(uint8_t intensity)
{
    /*  Set the duty cyle of the PWM signal that goes to the led light.       */
    DRV_Pwm_Set_Duty_Cycle(LIGHT, intensity);
    current_intensity = intensity;

}

uint8_t HW_Light_Get_Intensity()
{
    return current_intensity;
}

/*  Turn LED light on, in other words, 100 percent duty cycle.                */
void HW_Light_On(void)
{
    /*  Set the duty cyle of the PWM signal that goes to the led light.       */
    HW_Light_Set_Intensity(100);
}

/*  Turn LED light off, in other words, 0 percent duty cycle.                 */
void HW_Light_Off(void)
{
    /*  Set the duty cyle of the PWM signal that goes to the led light.       */
    HW_Light_Set_Intensity(0);
}
