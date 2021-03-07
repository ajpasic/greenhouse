/******************************************************************************/
/*  Filename:   HW_Buzzer.h                                                   */
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

#ifndef HARDWARE_HW_DOOR_H_
#define HARDWARE_HW_DOOR_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Gpio.h"

/******************************************************************************/
/*                           FUNCTION DECLARATION                             */
/******************************************************************************/

/*  Checks if the door is currently open or not, returns true if its open.    */
bool HW_Door_Is_Open(void);

/*  Disables door switch interrupt.                                           */
void HW_Door_Interrupt_On(void);

/*  Enables door switch interrupt.                                            */
void HW_Door_Interrupt_Off(void);

#endif /* HARDWARE_HW_DOOR_H_ */
