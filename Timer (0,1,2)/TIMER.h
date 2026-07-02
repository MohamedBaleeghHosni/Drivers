/*
 * TIMER.h
 *
 *  Created on: Oct 5, 2025
 *      Author: Mohamed Baleegh
 */
#include "std_types.h"

#ifndef TIMER_H_
#define TIMER_H_


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum {
    TIMER0_ID,          /*Timer 0*/
    TIMER1_ID,          /*Timer 1*/
    TIMER2_ID           /*Timer 2*/
} Timer_ID_Type;

typedef enum {
    TIMER_NO_CLOCK,          /* No clock source (Timer/Counter stopped)*/
    TIMER_FCPU_CLOCK,        /* No prescaling*/
    TIMER_FCPU_8,            /* FCPU_8*/
    TIMER_FCPU_64,           /* FCPU_64*/
    TIMER_FCPU_256,          /* FCPU_256*/
    TIMER_FCPU_1024          /* FCPU_1024*/
} Timer_ClockType;

typedef enum {
    TIMER_MODE_NORMAL, /* An interrupt occurs each over flow */
    TIMER_MODE_COMPARE /* An interrupt occurs each time timer reaches the compare match value*/
} Timer_ModeType;

typedef struct {
    uint16 timer_InitialValue;
    uint16 timer_compare_MatchValue;
    Timer_ID_Type timer_ID;
    Timer_ClockType timer_clock;
    Timer_ModeType timer_mode;
} Timer_ConfigType;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description: Function to initialize the Timer driver
 * Inputs: pointer to the configuration structure with type Timer_ConfigType.
 *  Return: None
 */
void Timer_init(const Timer_ConfigType * Config_Ptr);


/*
 * Description: Function to disable the Timer via Timer_ID.
 * Inputs: Timer_ID
 * Return: None
 */
 void Timer_deInit(Timer_ID_Type timer_type);


 /*
  *  Description: Function to set the Call Back function address to the required Timer.
  * Inputs: pointer to Call Back function and Timer Id you want to set The Callback to it.
  * Return: None
  */
 void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );



#endif /* TIMER_H_ */
