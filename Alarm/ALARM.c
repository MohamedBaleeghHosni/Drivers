/******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: alarm.c
 *
 * Description: Source file for the Alarm (Buzzer) driver
 *
 * Author: Mohamed Baleegh
 *
 *******************************************************************************/

#include "alarm.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Alarm_init(void)
{
    /* Set alarm pin as output */
    GPIO_setupPinDirection(ALARM_PORT_ID, ALARM_PIN_ID, PIN_OUTPUT);

    /* Starting with the   alarm OFF */
    GPIO_writePin(ALARM_PORT_ID, ALARM_PIN_ID, LOGIC_LOW);
}

void Alarm_on(void)
{
    GPIO_writePin(ALARM_PORT_ID, ALARM_PIN_ID, LOGIC_HIGH);
}

void Alarm_off(void)
{
    GPIO_writePin(ALARM_PORT_ID, ALARM_PIN_ID, LOGIC_LOW);
}
void Alarm_toggle (void)
{
	GPIO_togglePin(ALARM_PORT_ID,ALARM_PIN_ID);
}
