/*
 * LED.c
 *
 *  Created on: Sep 25, 2025
 *      Author: Mohamed Baleegh
 */
#include "gpio.h"
#include "LED.h"
void LEDS_init(void)
{
	GPIO_setupPinDirection(RED_LED_PORT_ID,RED_LED_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT_ID,GREEN_LED_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(BLUE_LED_PORT_ID,BLUE_LED_PIN_ID,PIN_OUTPUT);

	LED_off(RED_LED);
	LED_off(GREEN_LED);
	LED_off(BLUE_LED);

}
void LED_on(LED_ID id)
{
	switch(id)
	{
	case RED_LED:GPIO_writePin(RED_LED_PORT_ID,RED_LED_PIN_ID,LED_ON);
			break;
    case GREEN_LED: GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LED_ON);
            break;
    case BLUE_LED:  GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LED_ON);
            break;


	}
}
void LED_off(LED_ID id)
{
    switch(id)
    {
        case RED_LED:   GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LED_OFF);
            break;
        case GREEN_LED: GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LED_OFF);
            break;
        case BLUE_LED:  GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LED_OFF);
            break;
    }
}

void LED_toggle(LED_ID led)
{
    switch(led)
    {
    case RED_LED:
        GPIO_togglePin(RED_LED_PORT_ID, RED_LED_PIN_ID);
        break;
    case GREEN_LED:
        GPIO_togglePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID);
        break;
    case BLUE_LED:
        GPIO_togglePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID);
        break;
    }
}

