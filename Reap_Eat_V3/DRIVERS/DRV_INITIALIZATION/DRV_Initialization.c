/******************************************************************************/
/*  Filename:   DRV_Initialization.x                                          */
/*  Created on: Feb 12, 2021                                                  */
/*  Author:     Juan Leyva                                                    */
/*                                                                            */
/*                                                                            */
/*  PB2   I2C0SCL  BME280 temperature and humidity Sensor.                    */
/*  PB3   I2C0SDA  BME280 temperature and humidity Sensor.                    */
/*  PA0   U0RX     UART PC serial communication.                              */
/*  PA1   U0TX     UART PC serial communication.                              */
/*  PC4   U1RX     UART ESP32 serial communication.                           */
/*  PC5   U1TX     UART ESP32 serial communication.                           */
/*  PB0   DOUT     Peltier cooling module.                                    */
/*  PB1   DOUT     Internal ventilation fan.                                  */
/*  PB4   M0PWM2   LED lighting.                                              */
/*  PB5   DOUT     Alert Buzzer.                                              */
/*  PB6   M0PWM0   Vent servos.                                               */
/*  PB7   DOUT     PTC Heating module.                                        */
/*  PA2   DOUT     External exhaust fan.                                      */
/*  PA3   DOUT     Irrigation                                                 */
/*  PA4   DOUT     Humidifier tank filler.                                    */
/*  PE4   M0PWM4   Ultrasonic transducer humidifier.  .                       */
/*  PE1   DIN      Door switch signal.                                        */
/*  PE2   AIN1     Main water tank level analog signal.                       */
/*  PF1   DOUT     Status LED.                                                */
/*                                                                            */
/******************************************************************************/

#include "DRV_Initialization.h"
#include "utils/uartstdio.c"

void DRV_Initialize(void)
{
    /*  Enable peripheral GPIOs                                               */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    /*  UART 0 initializations.                                                */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                     UART_CONFIG_WLEN_8 |
                     UART_CONFIG_STOP_ONE |
                     UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);


    /*  UART 1 initializations.                                                */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1));

    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    UARTClockSourceSet(UART1_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
                        UART_CONFIG_WLEN_8 |
                        UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_NONE);
    UARTEnable(UART1_BASE);

    /*  I2C 0  initializations.                                                */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));

    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
    I2CMasterEnable(I2C0_BASE);

    /*  Digital output initializations.                                       */

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,
                          GPIO_PIN_2 |
                          GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,
                          GPIO_PIN_0 |
                          GPIO_PIN_1 |
                          GPIO_PIN_4 |
                          GPIO_PIN_5 |
                          GPIO_PIN_6 |
                          GPIO_PIN_7);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
                          GPIO_PIN_1 |
                          GPIO_PIN_2 |
                          GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);

    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_6,
                     GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_OD);

    /*  Digital input initializations.                                       */
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_1,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_BOTH_EDGES);
    GPIOIntRegister(GPIO_PORTE_BASE, DRV_Gpio_PortE_Handler);
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_1);

    /*  PWM initializations.                                                  */
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinConfigure(GPIO_PE4_M0PWM4);

    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_6);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0));

    SysCtlPWMClockSet(SYSCTL_PWMDIV_8);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
                    PWM_GEN_MODE_DOWN |
                    PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, PWM_SERVO_PERIOD);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (uint32_t)(PWM_SERVO_PERIOD / 20));

    PWMGenConfigure(PWM0_BASE, PWM_GEN_1,
                    PWM_GEN_MODE_DOWN |
                    PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, PWM_LED_PERIOD);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, (uint32_t)(PWM_LED_PERIOD / 2));

//    PWMGenConfigure(PWM0_BASE, PWM_GEN_2,
//                 PWM_GEN_MODE_DOWN |
//                 PWM_GEN_MODE_NO_SYNC);
//
//    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, PWM_HUMIDIFER_PERIOD);
//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, (uint32_t)(PWM_HUMIDIFER_PERIOD / 2));


    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    //PWMGenEnable(PWM0_BASE, PWM_GEN_2);
    PWMOutputState(PWM0_BASE,
                   PWM_OUT_0_BIT |
                   PWM_OUT_2_BIT , true);
}

