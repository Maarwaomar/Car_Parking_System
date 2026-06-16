/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Marwa Omar
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*------------------------------------------------------------------------------
 *                                Definitions
 *----------------------------------------------------------------------------*/

/* Logic state to activate the buzzer (HIGH means buzzer ON) */
#define BUZZER_STATE              LOGIC_HIGH

/* The port where the buzzer is connected (PORTC in this case) */
#define BUZZER_PORTID             PORTC_ID

/* The pin number inside the port used for the buzzer (PIN5 of PORTC) */
#define BUZZER_PINID              PIN5_ID


/*------------------------------------------------------------------------------
 *                          Functions Prototypes
 *----------------------------------------------------------------------------*/

/*
 * Description :
 * Initialize the buzzer pin:
 *  - Set the buzzer pin direction as output.
 *  - Ensure the buzzer is OFF initially.
 */
void Buzzer_init(void);

/*
 * Description :
 * Turn the buzzer ON by setting the buzzer pin to HIGH.
 */
void Buzzer_ON(void);

/*
 * Description :
 * Turn the buzzer OFF by setting the buzzer pin to LOW.
 */
void Buzzer_OFF(void);


#endif /* BUZZER_H_ */
