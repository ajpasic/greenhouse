/******************************************************************************/
/*  Filename:   HW_Light.h                                                    */
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

#ifndef HARDWARE_HW_LIGHT_H_
#define HARDWARE_HW_LIGHT_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Pwm.h"

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Set light intensity as a percentage (0 to 100).                           */
void HW_Light_Set_Intensity(uint8_t intensity);

/*  Turn LED light on, in other words, 100 percent duty cycle.                */
void HW_Light_On(void);

/*  Turn LED light off, in other words, 0 percent duty cycle.                 */
void HW_Light_Off(void);

#endif /* HARDWARE_HW_LIGHT_H_ */
