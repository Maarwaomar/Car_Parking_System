/******************************************************************************
 *
 * Module: LEDS
 *
 * File Name: led.c
 *
 * Description: Source file for the leds driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/

#include "led.h"
#include "gpio.h"
#include <util/delay.h>

/*------------------------------------------------------------------------------
 * Function : LEDS_init
 * Description :
 *   - Configure RED, GREEN, and BLUE LED pins as output.
 *   - Turn all LEDs OFF at startup.
 *----------------------------------------------------------------------------*/
void LEDS_init(void){
	/* Set pins as output */
	GPIO_setupPinDirection(RED_LED_PORT, RED_LED_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(BLUE_LED_PORT, BLUE_LED_PIN, PIN_OUTPUT);

	/* Ensure LEDs are OFF initially */
	LED_off(RED_LED);
	LED_off(GREEN_LED);
	LED_off(BLUE_LED);
}


/*------------------------------------------------------------------------------
 * Function : LED_on
 * Description :
 *   - Turn ON a specific LED based on its ID.
 *----------------------------------------------------------------------------*/
void LED_on(LED_ID id){
	switch(id)
	{
	case RED_LED:
		GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LED_STATE);   /* Red LED ON */
		break;
	case GREEN_LED:
		GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LED_STATE); /* Green LED ON */
		break;
	case BLUE_LED:
		GPIO_writePin(BLUE_LED_PORT, BLUE_LED_PIN, LED_STATE); /* Blue LED ON */
		break;
	}
}


/*------------------------------------------------------------------------------
 * Function : LED_off
 * Description :
 *   - Turn OFF a specific LED based on its ID.
 *----------------------------------------------------------------------------*/
void LED_off(LED_ID id){
	switch(id)
	{
	case RED_LED:
		GPIO_writePin(RED_LED_PORT, RED_LED_PIN, !LED_STATE);   /* Red LED OFF */
		break;
	case GREEN_LED:
		GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, !LED_STATE); /* Green LED OFF */
		break;
	case BLUE_LED:
		GPIO_writePin(BLUE_LED_PORT, BLUE_LED_PIN, !LED_STATE); /* Blue LED OFF */
		break;
	}
}


/*------------------------------------------------------------------------------
 * Function : LED_TOGGLE
 * Description :
 *   - Blink all LEDs together:
 *       -> Turn ON all LEDs for 500ms.
 *       -> Turn OFF all LEDs for 500ms.
 *----------------------------------------------------------------------------*/
void LED_TOGGLE(void){
	LED_on(RED_LED);
	LED_on(GREEN_LED);
	LED_on(BLUE_LED);
	_delay_ms(500);

	LED_off(RED_LED);
	LED_off(GREEN_LED);
	LED_off(BLUE_LED);
	_delay_ms(500);
}
