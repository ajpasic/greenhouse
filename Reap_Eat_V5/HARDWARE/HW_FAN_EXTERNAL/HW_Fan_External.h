/******************************************************************************/
/*  Filename:   HW_Fan_External.h                                             */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  External fan hardware module used to interface with the external fan      */
/*  hardware. The fan can be turned on or off. hardware. The pin that         */
/*  connects to the external fan mosfet driver is:                            */
/*                                                                            */
/*  PA2   DOUT     External exhaust fan.                                      */
/*                                                                            */
/******************************************************************************/

#ifndef HARDWARE_HW_FAN_EXTERNAL_H_
#define HARDWARE_HW_FAN_EXTERNAL_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Gpio.h"

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Turn on the external fan.                                                 */
void HW_Fan_External_On(void);

/*  Turn off the external fan.                                                */
void HW_Fan_External_Off(void);


#endif /* HARDWARE_HW_FAN_EXTERNAL_H_ */
