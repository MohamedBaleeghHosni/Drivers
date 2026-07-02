 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mohamed Baleegh
 *
 *******************************************************************************/

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr)

{
	uint16 ubrr_value = 0;
	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);
	/* U2X = 1 for double transmission speed */
	UCSRA = (1 << U2X);
	/*must be set to one when using the UCSRC*/
	SET_BIT(UCSRC,URSEL);
	/* Set USART MODE SELECT TO ASYNCHRONOUS */
	CLEAR_BIT(UCSRC, UMSEL);


	/* Data Bits number Configuration */

	switch (Config_Ptr->bit_data)
	{
	case UART_5_BIT:
		CLEAR_BIT(UCSRC, UCSZ0);
		CLEAR_BIT(UCSRC, UCSZ1);
		CLEAR_BIT(UCSRB, UCSZ2);
		break;
	case UART_6_BIT:
		SET_BIT(UCSRC, UCSZ0);
		CLEAR_BIT(UCSRC, UCSZ1);
		CLEAR_BIT(UCSRB, UCSZ2);
		break;

	case UART_7_BIT:
		CLEAR_BIT(UCSRC, UCSZ0);
		SET_BIT(UCSRC, UCSZ1);
		CLEAR_BIT(UCSRB, UCSZ2);
		break;

	case UART_8_BIT:
		SET_BIT(UCSRC, UCSZ0);
		SET_BIT(UCSRC, UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;

	case UART_9_BIT:
		SET_BIT(UCSRC, UCSZ0);
		SET_BIT(UCSRC, UCSZ1);
		SET_BIT(UCSRB, UCSZ2);
		break;

	}

	/* Parity Configuration */

	switch (Config_Ptr->parity)
	{
	case UART_PARITY_DISABLED:
		CLEAR_BIT(UCSRC, UPM0);
		CLEAR_BIT(UCSRC, UPM1);
		break;
	case UART_PARITY_EVEN:
		CLEAR_BIT(UCSRC, UPM0);
		SET_BIT(UCSRC, UPM1);
		break;
	case UART_PARITY_ODD:
		SET_BIT(UCSRC, UPM0);
		SET_BIT(UCSRC, UPM1);
		break;

	}

	/* Stop Bit Configuration */
	
	switch (Config_Ptr ->stop_bit)
	{
	case UART_ONE_STOP_BIT:
		CLEAR_BIT(UCSRC,USBS);
		break;
	case UART_TWO_STOP_BITS:
		SET_BIT(UCSRC,USBS);
		break;


	}
	
	ubrr_value = (uint16)(((F_CPU) / ((Config_Ptr->baud_rate) * 8UL)) - 1);

		UBRRH = ubrr_value >> 8;
		UBRRL = ubrr_value;


}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint32 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint32 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;		
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const char *Str)
{
    uint8 i = 0;
    while (Str[i] != '\0')
    {
        UART_sendByte(Str[i]);
        i++;
    }
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
    uint8 i = 0;
    Str[i] = UART_recieveByte();

    while (Str[i] != '#')
    {
        i++;
        Str[i] = UART_recieveByte();
    }

    Str[i] = '\0'; // نحول الـ# إلى نهاية النص
}
