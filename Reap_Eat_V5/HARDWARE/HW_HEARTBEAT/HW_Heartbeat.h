/******************************************************************************/
/*  Filename:   HW_Heartbeat.c                                                */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*  Description:                                                              */
/*  Heartbeat LED hardware module used to interface with the heartbeat LED.   */
/*  The LED light can be turned off or on or be toggled. The LED light        */
/*  interfaces through the following pin and module:                          */
/*                                                                            */
/*  PF1   DOUT     Heatbeat LED.                                                */
/*                                                                            */
/******************************************************************************/

#ifndef HARDWARE_HW_HEART_BEAT_H_
#define HARDWARE_HW_HEART_BEAT_H_

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "DRV_Gpio.h"

/******************************************************************************/
/*                               STATIC VARIABLE                              */
/******************************************************************************/

static volatile bool is_led_on = false;

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */
/******************************************************************************/

/*  Toggle the heartbeat LED.                                                 */
void HW_Heartbeat_Toggle(void);

/*  Turn on the heartbeat LED.                                                */
void HW_Heartbeat_On(void);

/*  Turn off the heartbeat LED.                                               */
void HW_Heartbeat_Off(void);

#endif /* HARDWARE_HW_HEART_BEAT_H_ */
