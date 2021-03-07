/******************************************************************************/
/*  Filename:   HW_Fan_Internal.h                                             */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Internal fan hardware module used to interface with the internal fan      */
/*  hardware. The fan can be turned on or off. hardware. The pin that         */
/*  connects to the internal fan mosfet driver is:                            */
/*                                                                            */
/*  PB1   DOUT     Internal ventilation fan.                                  */
/*                                                                            */
/******************************************************************************/

#ifndef HARDWARE_HW_FAN_INTERNAL_H_
#define HARDWARE_HW_FAN_INTERNAL_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Gpio.h"

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Turn on the internal fan.                                                 */
void HW_Fan_Internal_On(void);

/*  Turn off the internal fan.                                                */
void HW_Fan_Internal_Off(void);

#endif /* HARDWARE_HW_FAN_INTERNAL_H_ */
