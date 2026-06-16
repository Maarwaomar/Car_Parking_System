/*
 * main.c
 *
 *  Created on: Sep 30, 2025
 *      Author: Marwa Omar
 */

#include "buzzer.h"
#include "lcd.h"
#include "led.h"
#include "ultrasonic.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/

int main(void) {
	/* ------------------- Module Initializations ------------------- */
	Buzzer_init();        /* Initialize Buzzer pin (output, initially OFF) */
	LCD_init();           /* Initialize LCD in 4-bit/8-bit mode */
	LEDS_init();          /* Initialize LEDs (Red, Green, Blue) */
	Ultrasonic_init();    /* Initialize Ultrasonic sensor + ICU */

	SREG |= (1 << 7);     /* Enable Global Interrupt (I-bit in Status Register) */

	/* ------------------- Variables ------------------- */
	uint16 distance = Ultrasonic_readDistance(); /* First distance measurement */

	/* ------------------- Infinite Loop ------------------- */
	while (1) {
		/* Continuously measure distance from ultrasonic sensor */
		distance = Ultrasonic_readDistance();

		/* Case 1: Very close obstacle (<= 5 cm) */
		if (distance <= 5) {
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 6, "STOP");  /* Display warning */
			Buzzer_ON();                               /* Activate buzzer */
			LED_TOGGLE();                              /* Blink all LEDs */
		}
		else {
			/* Case 2: Safe distance (> 5 cm) → Display distance value */
			LCD_moveCursor(0, 0);
			LCD_displayString("Distance = ");
			LCD_integerToString(distance);
			LCD_displayString("Cm   ");  /* Spaces overwrite old chars */
			Buzzer_OFF();                 /* Ensure buzzer is off */

			/* ------------------- LED Indication Zones ------------------- */
			if (distance <= 10) {
				/* Zone 1: <= 10 cm → All LEDs ON */
				LED_on(RED_LED);
				LED_on(GREEN_LED);
				LED_on(BLUE_LED);
			}
			else if (distance <= 15) {
				/* Zone 2: <= 15 cm → Red + Green ON, Blue OFF */
				LED_on(RED_LED);
				LED_on(GREEN_LED);
				LED_off(BLUE_LED);
			}
			else if (distance <= 20) {
				/* Zone 3: <= 20 cm → Only Red ON */
				LED_on(RED_LED);
				LED_off(GREEN_LED);
				LED_off(BLUE_LED);
			}
			else {
				/* Zone 4: > 20 cm → All LEDs OFF */
				LED_off(RED_LED);
				LED_off(GREEN_LED);
				LED_off(BLUE_LED);
			}
		}
	}
}
