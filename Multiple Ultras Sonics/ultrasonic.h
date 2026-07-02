/*
 * ultrasonic.h
 *
 *  Created on: Mar 8, 2026
 *      Author: MoTheBaleegh
 *      NEW
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                         Definitions
 *******************************************************************************/

#define ULTRASONIC_SENSORS_NUM 3

/* Trigger pins */
/*RIGHT*/
#define ULTRASONIC_TRIGGER1_PORT_ID PORTD_ID
#define ULTRASONIC_TRIGGER1_PIN_ID  PIN3_ID
/*FRONT*/

#define ULTRASONIC_TRIGGER2_PORT_ID PORTD_ID
#define ULTRASONIC_TRIGGER2_PIN_ID  PIN4_ID
/*LEFT*/

#define ULTRASONIC_TRIGGER3_PORT_ID PORTD_ID
#define ULTRASONIC_TRIGGER3_PIN_ID  PIN5_ID

/* Common Echo (ICU pin) */

#define ULTRASONIC_ECHO_PORT_ID PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID  PIN6_ID

/* Speed of sound */

#define ULTRASONIC_SOUND_SPEED_CM_US 0.0343

/* Timer tick */

#define ULTRASONIC_TIMER_TICK_US 0.5


/*******************************************************************************
 *                      Functions Prototypes
 *******************************************************************************/

void Ultrasonic_init(void);

uint16 Ultrasonic_readDistance(uint8 sensor_id);

void Ultrasonic_edgeProcessing(void);

#endif
