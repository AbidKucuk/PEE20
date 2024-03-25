/*
 * rgb_led.h
 *
 *  Created on: Mar 23, 2024
 *      Author: abid
 */

#ifndef INC_USSR_H
#define INC_USSR_H

#include <stdint.h>

// The ussr button is set for P2.3
#define BUTTON      BIT3

// For how long to wait in ms until the button press is registered as valid.
extern const int BUTTON_PRESS_DELAY;

// When to register button as hold to reset
extern const int BUTTON_HOLD_LIMIT;

// To count for how long the button is pressed
extern int buttonPressCounter;

// Defining the possible states of the button
typedef enum
{
    pressed, un_pressed
} Button_State;

// Defining the button_state
extern Button_State button_state;

// Configure USSR button
void configureUSSR(void);

/*
 * This function de-bounces the button by starting a timer when the button is pressed
 * by enabling an interrupt every 0.1ms.
 */
void startButtonPressTimer(void);

// This function stops the timer and disables the interrupt.
void stopButtonPressTimer(void);

#endif /* INC_USSR_H */
