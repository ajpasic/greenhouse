/*
 * DRV_Pwm.c
 *
 *  Created on: Feb 21, 2021
 *      Author: juanleyva
 */

#include "DRV_Pwm.h"

void DRV_Pwm_Set_Duty_Cycle(drv_pwm_io_t io, uint8_t percent)
{
    uint32_t new_width;

    if (percent > 100)
    {
        percent = (uint8_t) 100;
    }

    switch(io)
    {
        case VENT_SERVO:

            if (percent < 1)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false);
            }
            else
            {
                new_width = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0);
                new_width = (uint32_t)(new_width * percent * 0.01);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, new_width);
                PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
            }
            break;

        case LIGHT:

            if (percent < 1)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false);
            }
            else
            {
                new_width = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1);
                new_width = (uint32_t)(new_width * percent * 0.01);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, new_width);
                PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
            }

            break;

        case HUMIDIFIER:

            if (percent  < 1)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
            }
            else
            {
                new_width = (uint32_t)PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2);
                new_width = (uint32_t)(new_width * percent * 0.01);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, new_width);
                PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
            }
            break;

        default:
            break;
    }

}
