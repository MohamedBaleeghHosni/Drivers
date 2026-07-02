/*
 * UltraSonic_Sensor.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Mohamed Baleegh
 */
#include "icu.h"
#include "UltraSonic_Sensor.h"
#include "gpio.h"
#include <util/delay.h>
/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

static volatile uint16 g_highTime;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Ultrasonic_init(void)
{
	/* Configure ICU: F_CPU/8, detect rising edge first */

	ICU_ConfigType ICU_Config = { F_CPU_8, RAISING };
	ICU_init(&ICU_Config);
	/* Set ICU callback */
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/* Set Trigger pin as output */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);



}
void Ultrasonic_Trigger(void)
{
/*Send the trigger pulse to the ultrasonic sensor.A 10us HIGH pulse*/
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void)
{
	uint16 distance = 0;
	float32 time_us = 0;

	/* Sending Trigger pulse */
	Ultrasonic_Trigger();

	/* Convert pulse width (ticks) to time in µs */
	time_us = g_highTime * ULTRASONIC_TIMER_TICK_US;

	/*
	 * Distance in cm = (time_us * speed of sound) / 2
	 *  speed_of_sound = 0.0343 cm/us
	 *  dTotal distance is divided by 2 because signal travels from HC-SR04
	 *  to object and returns to the module HC-SR-04.
	 */
	distance = (uint16) ((time_us * ULTRASONIC_SOUND_SPEED_CM_US) / 2.0);

	return distance;
}

void Ultrasonic_edgeProcessing(void)
{
	 static uint8 EdgeCount=0;
	EdgeCount++;
	    if(EdgeCount == 1)
	    {
	        /* First edge: rising  */
			/*clear the timer register to start the timer when the rising edge is detected*/

	        ICU_clearTimerValue();
			/*change the edge select to the falling edge to know the time of the pulse*/

	        ICU_setEdgeDetectionType(FALLING);
	    }
	    else if(EdgeCount == 2)
	    {
	        /* Second edge: falling  */
			/*we will read the input capture register and save it inside the g_higtime*/

	        g_highTime = ICU_getInputCaptureValue();
			/*clear the input capture register to start detect again*/
	        ICU_setEdgeDetectionType(RAISING);

	        /* make the edge counter equals zero again to start receiving the next pulse on the
	         * high edge from the sensor
	         * */
	        EdgeCount = 0;
	    }

}
