/******************************************************************************/
/*  Filename:   HW_Buzzer.h                                                   */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Buzzer hardware module used to interface with buzzer hardware. The buzzer */
/*  can only be turned on or off. The buzzer interfaces with through the      */
/*  following pin and module:                                                 */
/*                                                                            */
/*  PE4   M0PWM4   Alert buzzer.                                              */
/*                                                                            */
/******************************************************************************/

#ifndef HARDWARE_HW_BUZZER_H_
#define HARDWARE_HW_BUZZER_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Gpio.h"

/******************************************************************************/
/*                           FUNCTION DECLARATION                             */
/******************************************************************************/

/*  Turn on the buzzer.                                                       */
void HW_Buzzer_On(void);

/*  Turn off the buzzer.                                                      */
void HW_Buzzer_Off(void);

#endif /* HARDWARE_HW_BUZZER_H_ */
