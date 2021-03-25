/******************************************************************************/
/*  Filename:   HW_Fan_Internal.c                                             */
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

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Fan_Internal.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Turn on the internal fan.                                                 */
void HW_Fan_Internal_On(void)
{
    DRV_Gpio_Set_High(FAN_INTERNAL);
}

/*  Turn off the internal fan.                                                */
void HW_Fan_Internal_Off(void)
{
    DRV_Gpio_Set_Low(FAN_INTERNAL);
}
