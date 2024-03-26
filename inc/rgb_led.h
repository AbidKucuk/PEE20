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
extern const int RGB_LED_ON_TIME;

// To count for how long the LED is on
extern int rgbLedOnCounter;

typedef enum
{
    led_on, led_off
} RGB_LED_State;

// Defining the led state
extern RGB_LED_State rgb_led_state;

// Configure rgb led
void configureRGBLed(void);

// Light up led
void lightUpRGBLed(uint8_t led);

// Turn off led
void dimRGBLed(uint8_t led);

#endif /* INC_RGB_LED_H_ */
