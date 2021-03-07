/*
 * TST_Testing.h
 *
 *  Created on: Feb 22, 2021
 *      Author: juanleyva
 */

#ifndef TESTING_TST_TESTING_H_
#define TESTING_TST_TESTING_H_

void TST_Run(void)
{

#ifdef DEBUG_COM_TEST

    while(1)
    {
       // HW_Heartbeat_Toggle();
        SysCtlDelay(1000000);
        HW_Server_Send((uint8_t*)"TESTING UART.", (uint8_t)strlen("TESTING UART."));
        SysCtlDelay(1000000);
        HW_Server_Send((uint8_t*)"TESTING UART.", (uint8_t)strlen("TESTING UART."));
    }


#endif

#ifdef SERVER_COM_TEST

    while(1)
    {
        HW_Heartbeat_Toggle();
        SysCtlDelay(1000000);
        HW_Debug_Send
        HW_Debug_Send((uint8_t*)"TESTING UART.", (uint8_t)strlen("TESTING UART."));
        SysCtlDelay(1000000);
        HW_Debug_Send((uint8_t*)"TESTING UART.", (uint8_t)strlen("TESTING UART."));
    }


#endif

}

#endif /* TESTING_TST_TESTING_H_ */
