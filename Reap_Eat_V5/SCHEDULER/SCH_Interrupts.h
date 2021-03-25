/*
 * SCH_Interrupts.h
 *
 *  Created on: Mar 16, 2021
 *      Author: juanleyva
 */

#ifndef SCHEDULER_SCH_INTERRUPTS_H_
#define SCHEDULER_SCH_INTERRUPTS_H_

#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/cfg/global.h>
#include <ti/sysbios/hal/Hwi.h>
#include "DRV_Uart.h"

void SCH_Interrupt_Uart0(void);

void SCH_Interrupt_Uart1(void);

#endif /* SCHEDULER_SCH_INTERRUPTS_H_ */
