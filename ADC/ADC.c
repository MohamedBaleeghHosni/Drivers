/*
 * ADC.c
 *
 *  Created on: Sep 19, 2025
 *      Author: Mohamed Baleegh
 */
#include "ADC.h"
#include "common_macros.h"
#include <avr/io.h>
#include "std_types.h"



void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	ADMUX = (ADMUX & 0X3F) | ((Config_Ptr -> VREF)<<6);

	//CLEAR_BIT(ADMUX,REFS0);/* Internal 2.56 V*/
	//SET_BIT(ADMUX,REFS1);/* Internal 2.56 V*/
	CLEAR_BIT(ADMUX,MUX0);
	CLEAR_BIT(ADMUX,MUX1);
	CLEAR_BIT(ADMUX,MUX2);
	CLEAR_BIT(ADMUX,MUX3);
	CLEAR_BIT(ADMUX,MUX4);
	SET_BIT(ADCSRA,ADEN); /*ADC enable */
	CLEAR_BIT(ADCSRA,ADIE); /*ADC interrupt disable*/
	/*Prescaler Select*/
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr -> prescaler);
//	SET_BIT(ADCSRA,ADPS0);
//	SET_BIT(ADCSRA,ADPS1);
//	SET_BIT(ADCSRA,ADPS2);*/

}
uint16 ADC_readChannel(uint8 ch_num)
{
	/*data insertion */
	ADMUX =((ADMUX&0XE0)| (ch_num));
	/*Starting the conversion */
	SET_BIT(ADCSRA,ADSC);
	/*POOLING UNTIL CONVERSION IS DONE */
	while(BIT_IS_CLEAR(ADCSRA,ADIF))
	{

	}
	/*CLEAR THE FLAG */
	SET_BIT(ADCSRA,ADIF);

	return ADC;

}
