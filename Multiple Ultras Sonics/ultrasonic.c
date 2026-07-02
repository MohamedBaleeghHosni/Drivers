/*
 * ultrasonic.c
 *
 *  Created on: Mar 8, 2026
 *      Author: MoTheBaleegh
 */
#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Global Variables
 *******************************************************************************/

  uint16 g_highTime;
  uint8 g_edgeCount = 0;


/*******************************************************************************
 *                      Local Arrays for Triggers
 *******************************************************************************/

uint8 triggerPorts[ULTRASONIC_SENSORS_NUM] =
{
 ULTRASONIC_TRIGGER1_PORT_ID,
 ULTRASONIC_TRIGGER2_PORT_ID,
 ULTRASONIC_TRIGGER3_PORT_ID
};

uint8 triggerPins[ULTRASONIC_SENSORS_NUM] =
{
 ULTRASONIC_TRIGGER1_PIN_ID,
 ULTRASONIC_TRIGGER2_PIN_ID,
 ULTRASONIC_TRIGGER3_PIN_ID
};


/*******************************************************************************
 *                      Functions
 *******************************************************************************/

void Ultrasonic_init(void)
{
    ICU_ConfigType ICU_Config = {F_CPU_8, RAISING};
    ICU_init(&ICU_Config);

    ICU_setCallBack(Ultrasonic_edgeProcessing);

    /* Configure trigger pins as output */

    for(uint8 i = 0; i < ULTRASONIC_SENSORS_NUM; i++)
    {
        GPIO_setupPinDirection(triggerPorts[i], triggerPins[i], PIN_OUTPUT);
        GPIO_writePin(triggerPorts[i], triggerPins[i], LOGIC_LOW);
    }

    /* Configure echo pins as input */

    GPIO_setupPinDirection(ULTRASONIC_ECHO_PORT_ID, ULTRASONIC_ECHO_PIN_ID, PIN_INPUT);
}


/*******************************************************************************
 * Trigger selected sensor
 *******************************************************************************/

 void Ultrasonic_triggerSensor(uint8 sensor_id)
{
    GPIO_writePin(triggerPorts[sensor_id], triggerPins[sensor_id], LOGIC_HIGH);
    _delay_us(10);
    GPIO_writePin(triggerPorts[sensor_id], triggerPins[sensor_id], LOGIC_LOW);
}


/*******************************************************************************
 * Read distance from selected sensor
 *******************************************************************************/

uint16 Ultrasonic_readDistance(uint8 sensor_id)
{
    uint16 distance = 0;
    float32 time_us = 0;

    g_highTime = 0;
    g_edgeCount = 0;

    Ultrasonic_triggerSensor(sensor_id);

    /* Wait until echo captured */

    uint32 timeout = 60000;

    while((g_highTime == 0) && timeout)
    {
        timeout--;
    }
    time_us = g_highTime * ULTRASONIC_TIMER_TICK_US;

    distance = (uint16)((time_us * ULTRASONIC_SOUND_SPEED_CM_US) / 2.0);

    return distance;
}


/*******************************************************************************
 * ICU Callback
 *******************************************************************************/

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

