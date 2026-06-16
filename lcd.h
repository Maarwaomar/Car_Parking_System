/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include"std_types.h"

/*------------------------------------------------------------------------------
 *                                Definitions
 *----------------------------------------------------------------------------*/

/*
 * LCD Data bits mode configuration:
 *  - Can be either 4 or 8.
 *  - This decides whether we use 4-bit mode (DB4–DB7 only)
 *    or 8-bit mode (DB0–DB7).
 */
#define LCD_DATA_BITS_MODE 4

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be equal to 4 or 8"
#endif


/*------------------------------------------------------------------------------
 *                       LCD Control Pins (RS, E)
 *----------------------------------------------------------------------------*/

/* RS (Register Select) pin:
 *  - RS = 0 → Command mode
 *  - RS = 1 → Data mode
 */
#define LCD_RS_PORT_ID                       PORTA_ID
#define LCD_RS_PIN_ID                        PIN1_ID

/* Enable (E) pin:
 *  - High-to-Low transition on this pin tells LCD to latch data.
 */
#define LCD_E_PORT_ID                        PORTA_ID
#define LCD_E_PIN_ID                         PIN2_ID

/* Data port used by LCD (All data lines are connected to PORTA here) */
#define LCD_DATA_PORT_ID                     PORTA_ID


/*------------------------------------------------------------------------------
 *                       LCD Data Pins (for 4-bit mode)
 *----------------------------------------------------------------------------*/
#if (LCD_DATA_BITS_MODE == 4)
#define LCD_DB4_PIN_ID                       PIN3_ID
#define LCD_DB5_PIN_ID                       PIN4_ID
#define LCD_DB6_PIN_ID                       PIN5_ID
#define LCD_DB7_PIN_ID                       PIN6_ID
#endif


/*------------------------------------------------------------------------------
 *                       LCD Command Codes
 *----------------------------------------------------------------------------*/

/* Clear entire LCD */
#define LCD_CLEAR_COMMAND                    0x01

/* Return cursor to home position */
#define LCD_GO_TO_HOME                       0x02

/* 2-line display, 8-bit mode, 5x7 dots format */
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38

/* 2-line display, 4-bit mode, 5x7 dots format */
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28

/* Special initialization commands for 4-bit mode */
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32

/* Cursor control */
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E

/* Base address for setting cursor position */
#define LCD_SET_CURSOR_LOCATION              0x80


/*------------------------------------------------------------------------------
 *                       Functions Prototypes
 *----------------------------------------------------------------------------*/

/*
 * Description:
 * Initialize the LCD:
 *  - Set control/data pins direction.
 *  - Send initialization commands based on mode (4 or 8-bit).
 */
void LCD_init(void);

/*
 * Description:
 * Send a command to the LCD (RS=0).
 */
void LCD_sendCommand(uint8 command);

/*
 * Description:
 * Display a single character on the LCD (RS=1).
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description:
 * Display a string of characters on the LCD.
 */
void LCD_displayString(const char str[]);

/*
 * Description:
 * Convert integer to string and display it on LCD.
 */
void LCD_integerToString(int data);

/*
 * Description:
 * Move the cursor to a specific (row, column).
 * Rows typically: 0 → first line, 1 → second line.
 */
void LCD_moveCursor(uint8 row,uint8 col);

/*
 * Description:
 * Display a string starting at a specific row and column.
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/*
 * Description:
 * Clear the LCD screen (erase everything).
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
