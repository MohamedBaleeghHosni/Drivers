/*
 * TIMER.c
 *
 *  Created on: Oct 5, 2025
 *      Author: Mohamed Baleegh
 */
#include "Timer.h"
#include "avr/io.h"
#include <util/delay.h>
#include "common_macros.h"
#include <avr/interrupt.h>
#include "std_types.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application of the timer */
static void (*g_Timer0CallBackPtr)(void) = NULL_PTR;
static void (*g_Timer1CallBackPtr)(void) = NULL_PTR;
static void (*g_Timer2CallBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                          Interrupt Service Routines
 *******************************************************************************/

/*  TIMER0  */
ISR(TIMER0_OVF_vect)
{
    if(g_Timer0CallBackPtr != NULL_PTR)
    {
        (*g_Timer0CallBackPtr)();/* Call call back function */
    }
}

ISR(TIMER0_COMP_vect)
{
    if(g_Timer0CallBackPtr != NULL_PTR)
    {
    	(*g_Timer0CallBackPtr)();/* Call call back function */
    }

}

/*  TIMER1  */
ISR(TIMER1_OVF_vect)
{
    if(g_Timer1CallBackPtr != NULL_PTR)
    {
        (*g_Timer1CallBackPtr)();/* Call call back function */
    }
}

ISR(TIMER1_COMPA_vect)
{
    if(g_Timer1CallBackPtr != NULL_PTR)
    {
        (*g_Timer1CallBackPtr)();/* Call call back function */
    }
}

/*  TIMER2  */
ISR(TIMER2_OVF_vect)
{
    if(g_Timer2CallBackPtr != NULL_PTR)
    {
        (*g_Timer2CallBackPtr)();/* Call call back function */
    }
}

ISR(TIMER2_COMP_vect)
{
    if(g_Timer2CallBackPtr != NULL_PTR)
    {
        (*g_Timer2CallBackPtr)();/* Call call back function */
    }
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer_init(const Timer_ConfigType * Config_Ptr)
{

	switch (Config_Ptr->timer_ID)
	{
	case TIMER0_ID:
		TCNT0 = 0; /* Clear the counter register */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock);
		SET_BIT(TCCR0, FOC0); //for non PWM mode
		if (Config_Ptr->timer_mode == TIMER_MODE_NORMAL)
		{
			//Activate normal (overflow) mode
			CLEAR_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);
			/* Load the initial value */
			TCNT0 = (uint8) (Config_Ptr->timer_InitialValue);
			//enable interrupt for normal mode -> timer 0
			SET_BIT(TIMSK, TOIE0);
		}
		else if (Config_Ptr->timer_mode == TIMER_MODE_COMPARE)
		{
			//Activate CTC (compare) mode
			CLEAR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			//enable interrupt for CTC mode -> timer 0
			SET_BIT(TIMSK, OCIE0);

			//add the compare value
			OCR0 = (uint8)(Config_Ptr->timer_compare_MatchValue);

		}
		break;

	case TIMER1_ID:
	{
		//for non PWM mode
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);
		TCNT1 = Config_Ptr->timer_InitialValue;

		if (Config_Ptr->timer_mode == TIMER_MODE_NORMAL)
		{
			/* Normal mode */
			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1B, WGM13);

			SET_BIT(TIMSK, TOIE1); /* Timer/Counter1 Overflow Interrupt Enable */
		}


		else if (Config_Ptr->timer_mode == TIMER_MODE_COMPARE)
	{
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		OCR1A = Config_Ptr->timer_compare_MatchValue;
        SET_BIT(TIMSK,OCIE1A);/* Output Compare A Match Interrupt Enable*/



	}
		TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock);/* Clock Select Bit */

		break;
	}
	case TIMER2_ID:
	{
		SET_BIT(TCCR2,FOC2);
        TCNT2 = (uint8)(Config_Ptr->timer_InitialValue);


		if (Config_Ptr->timer_mode == TIMER_MODE_NORMAL)
		{
			CLEAR_BIT(TCCR2,WGM20);
			CLEAR_BIT(TCCR2,WGM21);
            SET_BIT(TIMSK, TOIE2); /* Timer/Counter2 Overflow Interrupt Enable */


		}
		else if (Config_Ptr->timer_mode == TIMER_MODE_COMPARE)
		{
			CLEAR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);
			OCR2 = Config_Ptr->timer_compare_MatchValue;
			SET_BIT(TIMSK, OCIE2);/*Timer/Counter2 Output Compare Match Interrupt Enable*/


		}
        TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->timer_clock);/* Clock Select Bit */

		break;
	}
	default:
		/*do nothing */
		break;
	}
}

void Timer_deInit(Timer_ID_Type timer_type)
{
	switch(timer_type)
	    {
	        case TIMER0_ID:
	            TCCR0 = 0;
	            CLEAR_BIT(TIMSK, TOIE0);
	            CLEAR_BIT(TIMSK, OCIE0);
	            break;

	        case TIMER1_ID:
	            TCCR1A = 0;
	            TCCR1B = 0;
	            CLEAR_BIT(TIMSK, TOIE1);
	            CLEAR_BIT(TIMSK, OCIE1A);
	            break;

	        case TIMER2_ID:
	            TCCR2 = 0;
	            CLEAR_BIT(TIMSK, TOIE2);
	            CLEAR_BIT(TIMSK, OCIE2);
	            break;
	    }
}

void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	switch(a_timer_ID)
	    {
	        case TIMER0_ID:
	            g_Timer0CallBackPtr = a_ptr;
	            break;

	        case TIMER1_ID:
	            g_Timer1CallBackPtr = a_ptr;
	            break;

	        case TIMER2_ID:
	            g_Timer2CallBackPtr = a_ptr;
	            break;
	    }
}
