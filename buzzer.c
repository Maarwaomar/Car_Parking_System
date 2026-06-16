/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/


#include "buzzer.h"
#include "gpio.h"

/*
 * Description :
 * Initialize the buzzer:
 *  - Configure the buzzer pin as OUTPUT.
 *  - Start with buzzer OFF (pin LOW).
 */
void Buzzer_init(void)
{
	/* Set buzzer pin as output */
	GPIO_setupPinDirection(BUZZER_PORTID, BUZZER_PINID, PIN_OUTPUT);

	/* Initialize buzzer state to OFF (LOW) */
	GPIO_writePin(BUZZER_PORTID, BUZZER_PINID, LOGIC_LOW);
}

/*
 * Description :
 * Turn ON the buzzer.
 * The buzzer is activated by writing BUZZER_STATE (usually HIGH) to the pin.
 */
void Buzzer_ON(void)
{
	GPIO_writePin(BUZZER_PORTID, BUZZER_PINID, BUZZER_STATE);
}

/*
 * Description :
 * Turn OFF the buzzer.
 * The buzzer is deactivated by writing the opposite of BUZZER_STATE (LOW).
 */
void Buzzer_OFF(void)
{
	GPIO_writePin(BUZZER_PORTID, BUZZER_PINID, !BUZZER_STATE);
}
