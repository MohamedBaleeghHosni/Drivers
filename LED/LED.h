/*
 * LED.h
 *
 *  Created on: Sep 25, 2025
 *      Author: VTE
 */

#ifndef LED_H_
#define LED_H_
#include "std_types.h"



/*******************************************************************************
 *                     DEFINITIONS                                 *
 *******************************************************************************/

#define CONNECTION_TYPE    POSITIVE_LOGIC

#define RED_LED_PORT_ID    PORTC_ID
#define RED_LED_PIN_ID     PIN0_ID

#define GREEN_LED_PORT_ID  PORTC_ID
#define GREEN_LED_PIN_ID   PIN1_ID

#define BLUE_LED_PORT_ID   PORTC_ID
#define BLUE_LED_PIN_ID    PIN2_ID

/*******************************************************************************
 *                                     TYPES DECLERATIONS                               *
 *******************************************************************************/

typedef enum
{
    RED_LED,
    GREEN_LED,
    BLUE_LED
} LED_ID;

#if(CONNECTION_TYPE==POSITIVE_LOGIC)
typedef enum
{
	LED_OFF,LED_ON
}LED_CONDITION;
#elif(CONNECTION_TYPE==NEGATIVE_LOGIC)
typedef enum
{
	LED_ON,LED_OFF
}LED_CONDITION;
#endif


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Initialize all LED pins as outputs and turn them off */
void LEDS_init(void);

/* Turn ON a specific LED */
void LED_on(LED_ID id);

/* Turn OFF a specific LED */
void LED_off(LED_ID id);

/* Toggle LED */
void LED_toggle(LED_ID led);


#endif
