/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ultrasonic sensor driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 counter = 0;        /* Used to count edges (rising/falling) of echo signal */
uint16 ride_time = 0;     /* Stores the high pulse duration of echo signal (in timer ticks) */

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/*
 * Function : Ultrasonic_init
 * --------------------------
 * Initialize the ultrasonic driver:
 *   - Configure ICU with F_CPU/8 clock and detect rising edge initially.
 *   - Register Ultrasonic_edgeProcessing() as the callback function for ICU ISR.
 *   - Configure the Trigger pin as output (used to send pulses to ultrasonic).
 */
void Ultrasonic_init(void) {
	ICU_ConfigType data;
	data.clock = F_CPU_8;      /* Timer1 runs at F_CPU/8 for better resolution */
	data.edge = RAISING;       /* Start by detecting rising edge of echo signal */

	ICU_init(&data);           /* Initialize ICU driver */
	ICU_setCallBack(Ultrasonic_edgeProcessing); /* Set callback function */

	/* Set Trigger pin direction as output */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_HIGH);
}

/*
 * Function : Ultrasonic_Trigger
 * -----------------------------
 * Sends a 10–20 µs HIGH pulse on the Trigger pin to initiate
 * a measurement cycle in the ultrasonic sensor.
 */
void Ultrasonic_Trigger(void) {
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(20); /* Minimum pulse width is 10 µs, here we use 20 µs */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_LOW);
}

/*
 * Function : Ultrasonic_readDistance
 * ----------------------------------
 * Triggers the ultrasonic sensor and waits for the echo signal
 * to complete its high pulse duration. The ICU measures that ON-time.
 *
 * Returns:
 *   - Distance in centimeters (uint16).
 *
 * Note:
 *   - The conversion factor (0.0085) is derived from the speed of sound:
 *     Distance (cm) = (Time (µs) * 0.034) / 2 ≈ Time * 0.017
 *     Since timer scaling with F_CPU/8 changes the units,
 *     here the factor is adjusted to 0.0085.
 */
uint16 Ultrasonic_readDistance(void) {
	Ultrasonic_Trigger();      /* Send trigger pulse */
	ICU_clearTimerValue();     /* Reset timer to start measuring echo pulse */

	while (counter != 0);      /* Wait until echo signal (2 edges) is captured */

	uint16 distance = (ride_time * 0.0085);  /* Convert ticks to distance */
	return (distance + 1);     /* +1 for small rounding adjustment */
}

/*
 * Function : Ultrasonic_edgeProcessing
 * ------------------------------------
 * ICU callback function, executed on each detected edge:
 *   - On 1st edge (RISING): Reset timer and switch to FALLING edge detection.
 *   - On 2nd edge (FALLING): Store pulse width (high time of echo),
 *                            reset counter, and switch back to RAISING edge.
 */
void Ultrasonic_edgeProcessing(void) {
	counter++;

	if (counter == 1) {
		/* Rising edge detected: reset timer and wait for falling edge */
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if (counter == 2) {
		/* Falling edge detected: read ON-time (high pulse) */
		ride_time = ICU_getInputCaptureValue();

		/* Reset back to rising edge for next measurement */
		ICU_setEdgeDetectionType(RAISING);
		counter = 0;
		ICU_clearTimerValue();
	}
}
