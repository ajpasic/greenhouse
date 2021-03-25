/******************************************************************************/
/*  Filename:   HW_Cooler.h                                                    */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Cooler hardware module used to interface with the peltier cooling module.
 *  The cooler module can be either turned on or off. The LED light interfaces through the following pin and module:*/
/*                                                                            */
/*  PB0   DOUT     Peltier cooling module.                                    */
/*                                                                            */
/******************************************************************************/

#ifndef HARDWARE_HW_COOLER_H_
#define HARDWARE_HW_COOLER_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_GPIO.h"

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Turn on the cooling peltier module.                                       */
void HW_Cooler_On(void);

/*  Turn off the cooling peltier module.                                      */
void HW_Cooler_Off(void);

#endif /* HARDWARE_HW_COOLER_H_ */
