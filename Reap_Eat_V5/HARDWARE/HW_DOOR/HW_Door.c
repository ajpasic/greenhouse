/******************************************************************************/
/*  Filename:   HW_Buzzer.c                                                   */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Door switch hardware module used to interface with the door switch.       */
/*  The interrupt associated with the digital input connected to the door     */
/*  switch can be disbled and enabled here. Additionally, the status of the   */
/*  door can also be polled. The door switch interfaces through the           */
/*  following pin and module:                                                 */
/*                                                                            */
/*  PE1   DIN      Door switch signal.                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Door.h"
#include "HW_Heartbeat.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Checks if the door is currently open or not, returns true if its open.    */
bool HW_Door_Is_Open(void)
{
    return DRV_Gpio_Is_High(DOOR_SWITCH);
}

/*  Disables door switch interrupt.                                           */
void HW_Door_Interrupt_On(void)
{
    DRV_Gpio_Enable_Interrupt(DOOR_SWITCH);
}

/*  Enables door switch interrupt.                                            */
void HW_Door_Interrupt_Off(void)
{
    DRV_Gpio_Disable_Interrupt(DOOR_SWITCH);
}

