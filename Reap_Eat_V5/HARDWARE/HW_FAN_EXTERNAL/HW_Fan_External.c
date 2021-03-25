/******************************************************************************/
/*  Filename:   HW_Fan_External.c                                             */
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

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Fan_External.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Turn on the external fan.                                                 */
void HW_Fan_External_On(void)
{
    DRV_Gpio_Set_High(FAN_EXTERNAL);
}

/*  Turn off the external fan.                                                */
void HW_Fan_External_Off(void)
{
    DRV_Gpio_Set_Low(FAN_EXTERNAL);
}
