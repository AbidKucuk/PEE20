/*
 * rgb_led.h
 *
 *  Created on: Mar 23, 2024
 *      Author: abid
 */

#ifndef INC_RGB_LED_H_
#define INC_RGB_LED_H_

#include <stdint.h>

#define RED_LED     BIT2    // P1.2
#define GREEN_LED   BIT1    // P1.1
#define BLUE_LED    BIT0    // P1.0

// For how the LED should be on for
extern const int LED_ON_TIME;

// To count for how long the LED is on
extern int ledOnCounter;

typedef enum
{
    led_on, led_off
} LED_State;

// Defining the led state
extern LED_State led_state;

// Configure rgb led
void configureLed(void);

// Light up led
void lightLed(uint8_t led);

// Turn off led
void dimLed(uint8_t led);

#endif /* INC_RGB_LED_H_ */
