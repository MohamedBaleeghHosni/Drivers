 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Mohamed Baleegh
 *
 *******************************************************************************/ 

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */
#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef uint8 TWI_AddressType;
/* Twi Prescaler bits*/
typedef enum
{
	TWI_PRESCALER_1,
	TWI_PRESCALER_4,
	TWI_PRESCALER_16,
	TWI_PRESCALER_64
}TWI_BaudRateType;

typedef struct {
 TWI_AddressType address;
 TWI_BaudRateType bit_rate;
}TWI_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void I2C_init(const TWI_ConfigType * Config_Ptr);
void I2C_start(void);
void I2C_stop(void);
void I2C_writeByte(uint8 data);
uint8 I2C_readByteWithACK(void);
uint8 I2C_readByteWithNACK(void);
uint8 I2C_getStatus(void);


#endif /* I2C_H_ */
