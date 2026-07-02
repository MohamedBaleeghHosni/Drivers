/*
 * ADC.h
 *
 *  Created on: Sep 19, 2025
 *      Author: Mohamed Baleegh
 */

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	DIVISION_FACTOR_2=1,DIVISION_FACTOR_4,DIVISION_FACTOR_8,
	DIVISION_FACTOR_16,DIVISION_FACTOR_32,
	DIVISION_FACTOR_64,DIVISION_FACTOR_128
}ADC_PrescalerValu;

typedef enum
{
	 AREF_InternalVrefTurnedOff, AVCC_WithExternalCapacitorAt_AREF_Pin,
	 Reserved, Internal_VRef

}ADC_VoltageRefernceSelect;

typedef struct
{
	ADC_PrescalerValu prescaler;
	ADC_VoltageRefernceSelect VREF;
}ADC_ConfigType;

void ADC_init(const ADC_ConfigType * Config_Ptr);
uint16 ADC_readChannel(uint8 ch_num);


#endif /* ADC_H_ */
