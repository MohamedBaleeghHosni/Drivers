 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Baleegh
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
/* Number of Data bits in the frame*/
typedef enum{
	UART_5_BIT, UART_6_BIT, UART_7_BIT, UART_8_BIT, UART_9_BIT

} UART_BitDataType;

/* Parity Type (enable and set type of parity generation and  check )*/
typedef enum {
	UART_PARITY_DISABLED, UART_PARITY_EVEN = 2, UART_PARITY_ODD
} UART_ParityType;

/* Stop Bit's number at the end of frame */
typedef enum {
	UART_ONE_STOP_BIT, UART_TWO_STOP_BITS
} UART_StopBitType;

/* Baud Rate Value */
typedef enum {
	UART_BAUD_10 =10,
	UART_BAUD_300 =300,
	UART_BAUD_600 =600,
	UART_BAUD_1200 =1200,
	UART_BAUD_2400 = 2400,
	UART_BAUD_4800 = 4800,
	UART_BAUD_9600 = 9600,
	UART_BAUD_14400 = 14400,
	UART_BAUD_19200 = 19200,
	UART_BAUD_38400 = 38400,
	UART_BAUD_57600 = 57600,
	UART_BAUD_115200 = 115200,
	UART_BAUD_128000 =128000,
	UART_BAUD_256000 =256000,


} UART_BaudRateType;

/* UART configuration structure*/
typedef struct {
	UART_BitDataType bit_data;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRateType baud_rate;
} UART_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint32 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint32 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const char *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str);
// Receive until #

#endif /* UART_H_ */
