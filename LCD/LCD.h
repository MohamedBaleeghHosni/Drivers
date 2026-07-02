/*
 * LCD.h
 *
 *  Created on: Sep 17, 2025
 *      Author: TheBaleegh
 */



/*******************************************************************************
 *                     LCD BIT MODE DEFINITION                                  *
 *******************************************************************************/
#define LCD_DATA_BITS_MODE 4/* 4 or 8 */
#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#ifndef LCD_H_
#define LCD_H_
/* lCD COMMANDS*/
#define LCD_FUNCTION_SET_8BIT_2LINE_5x7   0x38
#define LCD_FUNCTION_SET_4BIT_2LINE_5x7   0x28
#define LCD_FUNCTION_SET_8BIT_1LINE_5x7   0x30
#define LCD_FUNCTION_SET_4BIT_1LINE_5x7   0x20

#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32

#define LCD_CURSOR_OFF 0x0c
#define LCD_CURSOR_ON 0x0e
#define LCD_CURSOR_ON_BLINKING 0x0f
#define LCD_CLEAR 0x01
#define LCD_SHIFT_CURSOR_TO_LEFT_ONE_CHARACTER 0x10
#define LCD_SHIFT_CURSOR_TO_RIGHT_ONE_CHARACTER 0x14
#define LCD_SET_CURSOR_LOCATION              0x80



#include "std_types.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand (uint8 command);
void LCD_dispCharacter(uint8 character);
void LCD_init(void);
void LCD_dispString(const char *Str);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_intgerToString(int data);
void LCD_clear_Display(void);
int LCD_stringToInteger(char *data);
void LCD_floatToString(float data);



/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTA_ID
#define LCD_RS_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTA_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif



#endif /* LCD_H_ */
