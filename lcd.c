/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/


#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>
#include "common_macros.h" /* For GET_BIT Macro */
#include <stdlib.h>        /* For itoa() function */


/*------------------------------------------------------------------------------
 * Function : LCD_init
 * Description :
 *   - Initialize the LCD:
 *       1. Configure RS and E pins as output.
 *       2. Depending on LCD_DATA_BITS_MODE:
 *            -> Configure data pins (4-bit or full port for 8-bit).
 *            -> Send proper initialization commands.
 *       3. Turn cursor off.
 *       4. Clear the LCD screen.
 *----------------------------------------------------------------------------*/
void LCD_init(){
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT); /* RS as output */
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);   /* E as output */
	_delay_ms(20); /* Wait for LCD power on */

#if(LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins (DB4–DB7) as output */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* 4-bit mode initialization sequence */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* Set LCD to 2 lines, 4-bit mode, 5x7 font */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)
	/* Configure all 8 pins as output */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	/* Set LCD to 2 lines, 8-bit mode, 5x7 font */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);     /* Disable cursor */
	LCD_sendCommand(LCD_CLEAR_COMMAND);  /* Clear screen */
}


/*------------------------------------------------------------------------------
 * Function : LCD_sendCommand
 * Description :
 *   - Send an instruction/command to the LCD (RS = 0).
 *   - Works for both 4-bit and 8-bit modes.
 *----------------------------------------------------------------------------*/
void LCD_sendCommand(uint8 command){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* RS=0 → command */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);  /* Enable pulse */
	_delay_ms(2);

#if(LCD_DATA_BITS_MODE == 4)
	/* Send higher nibble (bits 4–7) */
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable E */
	_delay_ms(1);

	/* Pulse again to send lower nibble (bits 0–3) */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Finish cycle */
	_delay_ms(1);

#elif(LCD_DATA_BITS_MODE == 8)
	/* Write full 8-bit command */
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#endif
}


/*------------------------------------------------------------------------------
 * Function : LCD_displayCharacter
 * Description :
 *   - Display a single character (RS = 1).
 *   - Works in both 4-bit and 8-bit modes.
 *----------------------------------------------------------------------------*/
void LCD_displayCharacter(uint8 data){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* RS=1 → data */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);   /* Enable */
	_delay_ms(2);

#if(LCD_DATA_BITS_MODE == 4)
	/* Send higher nibble */
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

	/* Send lower nibble */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#elif(LCD_DATA_BITS_MODE == 8)
	/* Write full 8-bit data */
	GPIO_writePort(LCD_DATA_PORT_ID,data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#endif
}


/*------------------------------------------------------------------------------
 * Function : LCD_displayString
 * Description :
 *   - Display a null-terminated string on the LCD.
 *   - Loops through each character and prints it.
 *----------------------------------------------------------------------------*/
void LCD_displayString(const char str[]){
	uint8 i;
	for(i=0 ; str[i]!='\0' ; i++){
		LCD_displayCharacter(str[i]);
	}
}


/*------------------------------------------------------------------------------
 * Function : LCD_integerToString
 * Description :
 *   - Convert integer value into a string using itoa().
 *   - Display it on the LCD.
 *----------------------------------------------------------------------------*/
void LCD_integerToString(int data){
	char buff[16];          /* Buffer to hold string representation */
	itoa(data,buff,10);     /* Convert integer to ASCII string (decimal base) */
	LCD_displayString(buff);
}


/*------------------------------------------------------------------------------
 * Function : LCD_clearScreen
 * Description :
 *   - Clear all characters from LCD and reset cursor to home.
 *----------------------------------------------------------------------------*/
void LCD_clearScreen(){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}


/*------------------------------------------------------------------------------
 * Function : LCD_moveCursor
 * Description :
 *   - Move LCD cursor to specific (row, col).
 *   - LCD internal DDRAM addresses depend on row number.
 *----------------------------------------------------------------------------*/
void LCD_moveCursor(uint8 row,uint8 col){
	uint8 LCD_memoryAddress;

	switch(row){
	case 0 :
		LCD_memoryAddress = col;        /* First row starts at 0x00 */
		break;
	case 1 :
		LCD_memoryAddress = col + 0x40; /* Second row starts at 0x40 */
		break;
	case 2 :
		LCD_memoryAddress = col + 0x10; /* Third row starts at 0x10 */
		break;
	case 3 :
		LCD_memoryAddress = col + 0x50; /* Fourth row starts at 0x50 */
		break;
	}

	/* Combine address with command base to move cursor */
	LCD_sendCommand(LCD_memoryAddress | LCD_SET_CURSOR_LOCATION);
}


/*------------------------------------------------------------------------------
 * Function : LCD_displayStringRowColumn
 * Description :
 *   - Move cursor to given row/col.
 *   - Print the provided string starting from that position.
 *----------------------------------------------------------------------------*/
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str){
	LCD_moveCursor(row,col);
	LCD_displayString(Str);
}
