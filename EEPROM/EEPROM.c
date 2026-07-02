 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Mohamed Baleegh
 *
 *******************************************************************************/
#include "EEPROM.h"
#include "I2C.h"
#include <util/delay.h>
#define EEPROM_TOTAL_BYTES   2048u    /* 16 Kbit = 2048 bytes */
#define EEPROM_PAGE_SIZE     16u      /* page size (bytes) */
#define EEPROM_DEV_BASE_ADDR 0xA0u    /* control byte base for 24C16 (A2..A0 = 0) */
/* Write-cycle delay after page write (ms). Typical 5-10 ms */
#define EEPROM_WRITE_CYCLE_MS 10u

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
	I2C_start();
    if (I2C_getStatus() != I2C_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (I2C_getStatus() != I2C_MT_SLA_W_ACK)
        return ERROR; 
		 
    /* Send the required memory location address */
    I2C_writeByte((uint8)(u16addr));
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return ERROR;
		
    /* write byte to eeprom */
    I2C_writeByte(u8data);
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    I2C_stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
    /* Send the Start Bit */
    I2C_start();
    if (I2C_getStatus() != I2C_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700) >> 7)));
    if (I2C_getStatus() != I2C_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    I2C_writeByte((uint8)(u16addr));
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    I2C_start();
    if (I2C_getStatus() != I2C_REP_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700) >> 7) | 1));
    if (I2C_getStatus() != I2C_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = I2C_readByteWithNACK();
    if (I2C_getStatus() != I2C_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    I2C_stop();

    return SUCCESS;
}



/* Helper: build control byte for address (A10..A8 come from address bits 10..8) */
static inline uint8 eeprom_control_byte_for_addr(uint16 addr)
{
    /* top 3 bits of address go into control byte bits A2..A0 */
    uint8 device = (uint8)((addr >> 8) & 0x07u);
    return (uint8)(EEPROM_DEV_BASE_ADDR | device);
}

/* Write a single page (addr must be page-aligned or less-than-page write is allowed).
   data[] length is 'len' (<= EEPROM_PAGE_SIZE). */
static void EEPROM_writePage(uint16 addr, const uint8 *data, uint8 len)
{
    uint8 control = eeprom_control_byte_for_addr(addr);
    uint8 lowAddr = (uint8)(addr & 0xFFu);

    I2C_start();
    I2C_writeByte(control);   // SLA+W
    I2C_writeByte(lowAddr);   // Low address
    for(uint8 i = 0; i < len; i++)
    {
        I2C_writeByte(data[i]);
    }
    I2C_stop();

    _delay_ms(EEPROM_WRITE_CYCLE_MS); // wait for write cycle
}

/* Clear whole EEPROM by writing 'pattern' to all bytes (0xFF or 0x00) */
/* Clear whole EEPROM by writing 'pattern' to all bytes (0xFF or 0x00)*/
void EEPROM_clearAll(uint8 pattern)
{
    uint8 pageBuffer[EEPROM_PAGE_SIZE];
    uint16 bytesRemaining = EEPROM_TOTAL_BYTES;
    uint16 addr = 0;

    /* prepare a page filled with the pattern */
    for(uint8 i = 0; i < EEPROM_PAGE_SIZE; i++)
        pageBuffer[i] = pattern;

    while(bytesRemaining > 0)
    {
        uint8 writeLen = (bytesRemaining >= EEPROM_PAGE_SIZE) ? EEPROM_PAGE_SIZE : (uint8)bytesRemaining;

        /* write a page */
        EEPROM_writePage(addr, pageBuffer, writeLen);

        addr += writeLen;
        bytesRemaining -= writeLen;
    }
}
