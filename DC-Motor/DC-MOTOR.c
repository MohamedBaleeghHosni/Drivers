/*
 * DC-MOTOR.c
 *
 *  Created on: Sep 25, 2025
 *      Author: Mohamed Baleegh
 */
#include "DC-MOTOR.h"
#include "gpio.h"
#include "PWM.h"

void DcMotor_Init(void)
{
    /* Setup motor1 pins as output */
    GPIO_setupPinDirection(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID, PIN_OUTPUT);

    /* Stop motor1 initially at the beginning*/
    GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_LOW);
    GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_LOW);
#if DC_MOTOR_COUNT == 2
    /* Setup motor2 pins as output */
        GPIO_setupPinDirection(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID, PIN_OUTPUT);
        GPIO_setupPinDirection(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID, PIN_OUTPUT);

        /* Stop motor2 initially at the beginning*/
        GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID, LOGIC_LOW);
        GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID, LOGIC_LOW);
#endif
}

/* Rotate  the motors (motor_id = 1 or 2) */
void DcMotor_Rotate(uint8 motor_id, DcMotor_State state, uint8 speed)
{
	switch(motor_id)
	{
	case 1:
		switch(state)
		{
		case STOP:
			GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_LOW);
			break;

		case CW:
			GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_LOW);
			break;

		case ACW:
			GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_HIGH);
			break;
		}
		break;

#if (DC_MOTOR_COUNT == 2)
	case 2:
		switch(state)
		{
		case STOP:
			GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID, LOGIC_LOW);
			break;

		case CW:
			GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID, LOGIC_LOW);
			break;

		case ACW:
			GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID, LOGIC_HIGH);
			break;
		}
		break;
#endif
	}


	PWM_Timer0_Start(speed);
}

/* Control the motors based on a specific value condition */
void DcMotor_Control(uint8 motor_id,uint16 value)
{
	switch (motor_id) {
	case 1:

		if (value >= 40)
			DcMotor_Rotate(1, CW, 100);
		else if (value >= 35)
			DcMotor_Rotate(1, CW, 75);
		else if (value >= 30)
			DcMotor_Rotate(1, CW, 50);
		else if (value >= 25)
			DcMotor_Rotate(1, CW, 25);
		else
			DcMotor_Rotate(1, STOP, 0);
		break;
#if (DC_MOTOR_COUNT == 2)
	case 2:
		if (value >= 40)
			DcMotor_Rotate(2, CW, 100);
		else if (value >= 35)
			DcMotor_Rotate(2, CW, 75);
		else if (value >= 30)
			DcMotor_Rotate(2, CW, 50);
		else if (value >= 25)
			DcMotor_Rotate(2, CW, 25);
		else
			DcMotor_Rotate(2, STOP, 0);
		break;
#endif
	}

}
