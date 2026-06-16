/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultasonic.h
 *
 * Description: Header file for the ultrasonic sensor driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

/* The ultrasonic sensor uses a "trigger" pin to start sending the sound pulse */
#define ULTRASONIC_TRIGGER_PORT      PORTD_ID   /* Port where trigger pin is connected */
#define ULTRASONIC_TRIGGER_PIN       PIN7_ID    /* Trigger pin number */

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Function : Ultrasonic_init
 * --------------------------
 * Initialize the ultrasonic driver:
 *   - Configure trigger pin as output.
 *   - Initialize ICU (Input Capture Unit) to measure echo pulse width.
 */
void Ultrasonic_init(void);

/*
 * Function : Ultrasonic_Trigger
 * -----------------------------
 * Send a short trigger pulse (10 µs HIGH) to the ultrasonic sensor
 * to initiate distance measurement.
 */
void Ultrasonic_Trigger(void);

/*
 * Function : Ultrasonic_readDistance
 * ----------------------------------
 * Trigger the ultrasonic sensor and calculate the measured distance
 * based on the echo pulse duration.
 *
 * Returns:
 *   - Distance in centimeters (uint16).
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Function : Ultrasonic_edgeProcessing
 * ------------------------------------
 * Callback function for ICU interrupt.
 *   - Used to process the rising and falling edges of the echo signal.
 *   - Calculates the ON-time of the echo pulse (used to determine distance).
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
