/*
 * HW_Humidifier.c
 *
 *  Created on: Mar 1, 2021
 *      Author: juanleyva
 */


#include "HW_Humidifier.h"

void HW_Humidifier_On(void)
{
    DRV_Pwm_Set_Duty_Cycle(HUMIDIFIER, 50);
}

void HW_Humidifier_Off(void)
{
    DRV_Pwm_Set_Duty_Cycle(HUMIDIFIER, 0);
}
