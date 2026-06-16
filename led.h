/******************************************************************************
 *
 * Module: LEDS
 *
 * File Name: led.h
 *
 * Description: Header file for the leds driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/
#ifndef LED_H_
#define LED_H_

#include "std_types.h"

/*------------------------------------------------------------------------------
 *                                Data Types
 *----------------------------------------------------------------------------*/

/*
 * Enumeration for LED identifiers:
 *  - RED_LED   → Selects Red LED
 *  - BLUE_LED  → Selects Blue LED
 *  - GREEN_LED → Selects Green LED
 */
typedef enum{
	RED_LED,
	BLUE_LED,
	GREEN_LED
}LED_ID;


/*------------------------------------------------------------------------------
 *                                Definitions
 *----------------------------------------------------------------------------*/

/* Logic state to turn LED ON */
#define LED_STATE      LOGIC_HIGH

/* Red LED hardware connection */
#define RED_LED_PORT   PORTC_ID
#define RED_LED_PIN    PIN0_ID

/* Green LED hardware connection */
#define GREEN_LED_PORT PORTC_ID
#define GREEN_LED_PIN  PIN1_ID

/* Blue LED hardware connection */
#define BLUE_LED_PORT  PORTC_ID
#define BLUE_LED_PIN   PIN2_ID


/*------------------------------------------------------------------------------
 *                            Functions Prototypes
 *----------------------------------------------------------------------------*/

/*
 * Description :
 * Initialize all LEDs:
 *  - Configure LED pins as output.
 *  - Set initial state to OFF.
 */
void LEDS_init(void);

/*
 * Description :
 * Turn ON the LED corresponding to the given ID.
 */
void LED_on(LED_ID id);

/*
 * Description :
 * Turn OFF the LED corresponding to the given ID.
 */
void LED_off(LED_ID id);

/*
 * Description :
 * Toggle the state of all LEDs (ON → OFF, OFF → ON).
 */
void LED_TOGGLE(void);

#endif /* LED_H_ */
