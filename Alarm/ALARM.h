/******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: alarm.h
 *
 * Description: Header file for the Alarm (Buzzer) driver
 *
 * Author: Mohamed Baleegh
 *
 *******************************************************************************/

#ifndef ALARM_H_
#define ALARM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ALARM_PORT_ID     PORTC_ID
#define ALARM_PIN_ID      PIN5_ID

/*******************************************************************************
 *                      Functions Protoypes                                   *
 *******************************************************************************/


void Alarm_init(void);

/*
 * Description:
 * Turn ON the alarm (activate buzzer).
 */
void Alarm_on(void);

/*
 * Description:
 * Turn OFF the alarm (deactivate buzzer).
 */
void Alarm_off(void);

/*
 * Description:
 * Toggle the state of the ALARM .
 */
void Alarm_toggle (void);


#endif
