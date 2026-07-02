/*
 * DC-MOTOR.h
 *
 *  Created on: Sep 25, 2025
 *      Author: Mohamed Baleegh
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"

#define DC_MOTOR_COUNT  2 /* could only be set to 1 or 2 */
/*******************************************************************************
 *                              Pin Definitions
 *******************************************************************************/

/* ---------- Motor 1 ---------- */
#define DC_MOTOR1_IN1_PORT_ID   PORTB_ID
#define DC_MOTOR1_IN1_PIN_ID    PIN0_ID

#define DC_MOTOR1_IN2_PORT_ID   PORTB_ID
#define DC_MOTOR1_IN2_PIN_ID    PIN1_ID

#if (DC_MOTOR_COUNT == 2)
/* ---------- Motor 2 ---------- */
#define DC_MOTOR2_IN1_PORT_ID   PORTB_ID
#define DC_MOTOR2_IN1_PIN_ID    PIN4_ID
#define DC_MOTOR2_IN2_PORT_ID   PORTB_ID
#define DC_MOTOR2_IN2_PIN_ID    PIN5_ID
#endif
typedef enum
{
    STOP, CW, ACW
} DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(uint8 motor_id, DcMotor_State state, uint8 speed);
void DcMotor_Control(uint8 motor_id,uint16 value);

#endif /* DC_MOTOR_H_ */
