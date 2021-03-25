/*
 * HW_Heater.c
 *
 *  Created on: Mar 23, 2021
 *      Author: JuanLeyva
 */

#include "HW_Heater.h"


/*  Turn on the cooling peltier module.                                       */
void HW_Heater_On(void)
{
    DRV_Gpio_Set_High(HEATER);
}

/*  Turn off the cooling peltier module.                                      */
void HW_Heater_Off(void)
{
    DRV_Gpio_Set_Low(HEATER);
}

