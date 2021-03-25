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
/*  PF1   DOUT     Heatbeat LED.                                              */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <HW_Heartbeat.h>

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Toggle the heartbeat LED.                                                 */
void HW_Heartbeat_Toggle(void)
{
    /*  If the Heartbeat led is currently on.                                 */
    if(is_led_on)
    {
        /*  Turn off the heartbeat LED.                                       */
        HW_Heartbeat_Off();
    }
    else
    {
        /*  Turn on the heartbeat LED.                                        */
        HW_Heartbeat_On();
    }
}

/*  Turn on the heartbeat LED.                                                */
void HW_Heartbeat_On(void)
{
    /*  Set the led gpio pin off.                                             */
    DRV_Gpio_Set_Low(HEARTBEAT_LED);
    is_led_on = true;
}

/*  Turn off the heartbeat LED.                                               */
void HW_Heartbeat_Off(void)
{
    /*  Set the led gpio pin on.                                              */
    DRV_Gpio_Set_High(HEARTBEAT_LED);
    is_led_on = false;
}
