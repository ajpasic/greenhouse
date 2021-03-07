/*
 * DRV_Gpio.c
 *
 *  Created on: Feb 21, 2021
 *      Author: juanleyva
 */

#include "DRV_Gpio.h"

void DRV_Gpio_Set_High(drv_digital_io_t io)
{
    switch(io)
    {
        case COOLER:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PIN_0);
            break;

        case HEATER:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_7);
            break;

        case FAN_INTERNAL:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
            break;

        case FAN_EXTERNAL:
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
            break;

        case IRRIGATION:
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
            break;

        case HUMIDIFIER_FILLER:
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
            break;

        case HEARTBEAT_LED:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            break;
        case BUZZER:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
            break;
        default:
            break;
    }
}

void DRV_Gpio_Set_Low(drv_digital_io_t io)
{
    switch(io)
    {
        case COOLER:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);
            break;

        case HEATER:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);
            break;

        case FAN_INTERNAL:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);
            break;

        case FAN_EXTERNAL:
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
            break;

        case IRRIGATION:
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
            break;

        case HUMIDIFIER_FILLER:
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
            break;

        case HEARTBEAT_LED:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            break;
        case BUZZER:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
            break;
        default:
            break;
    }
}

bool DRV_Gpio_Is_High(drv_digital_io_t io)
{
    uint32_t result = 0;
    bool ret = false;

    switch(io)
    {
        case COOLER:
            result = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0);
            break;

        case HEATER:
            result = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_7);
            break;

        case FAN_INTERNAL:
            result = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_1);
            break;

        case FAN_EXTERNAL:
            result = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
            break;

        case IRRIGATION:
            result = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3);
            break;

        case HUMIDIFIER_FILLER:
            result = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
            break;

        case HEARTBEAT_LED:
            result = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);
            break;
        case BUZZER:
            result = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_5);
            break;
        default:
            break;
    }

    if (result == (uint32_t) 0)
    {
        ret = false;
    }
    else
    {
        ret = true;
    }

    return ret;
}

void DRV_Gpio_Enable_Interrupt(drv_digital_io_t io)
{
    switch(io)
    {
        case DOOR_SWITCH:
            GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_1);
            break;

        default:
            break;
    }
}

void DRV_Gpio_Disable_Interrupt(drv_digital_io_t io)
{
    switch(io)
    {
        case DOOR_SWITCH:
            GPIOIntDisable(GPIO_PORTE_BASE, GPIO_INT_PIN_1);
            break;

        default:
            break;
    }
}

void DRV_Gpio_PortE_Handler(void)
{
    volatile uint32_t status = 0;
    volatile static bool is_first_edge = false;

    status = GPIOIntStatus(GPIO_PORTE_BASE, true);
    GPIOIntClear(GPIO_PORTE_BASE, status);

    if(status == GPIO_INT_PIN_1)
    {
        if (is_first_edge)
        {
            GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_LOW_LEVEL);
        }
        else
        {
            GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_HIGH_LEVEL);
        }

        is_first_edge != is_first_edge;

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,
        ~GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_2));
    }
}
