/*
 * HW_Cooler.c
 *
 *  Created on: Feb 22, 2021
 *      Author: juanleyva
 */

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "HW_Cooler.h"

/******************************************************************************/
/*                          FUNCTION IMPLEMENTATION                           */
/******************************************************************************/

/*  Turn on the cooling peltier module.                                       */
void HW_Cooler_On(void)
{
    DRV_Gpio_Set_High(COOLER);
}

/*  Turn off the cooling peltier module.                                      */
void HW_Cooler_Off(void)
{
    DRV_Gpio_Set_Low(COOLER);
}
