/*
 * HW_Heater.h
 *
 *  Created on: Feb 21, 2021
 *      Author: juanleyva
 */

#ifndef HARDWARE_HW_HEATER_H_
#define HARDWARE_HW_HEATER_H_

#include "DRV_Gpio.h"

/*  Turn on the ptc heater module.                                       */
void HW_Heater_On(void);


/*  Turn off the ptc heater module.                                      */
void HW_Heater_Off(void);

#endif /* HARDWARE_HW_HEATER_H_ */
