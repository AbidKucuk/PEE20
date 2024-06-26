/*
 * rgb_led.c
 *
 *  Created on: Mar 23, 2024
 *      Author: abid
 */
#include <msp430.h>
#include "../inc/rgb_led.h"

const int RGB_LED_ON_TIME = 2000; // Led should be on for 2 seconds == 2000ms,
int rgbLedOnCounter = 0; // Set default at 0
RGB_LED_State rgb_led_state = led_off; // LED is by default off

void configureRGBLed(){
    P1DIR |= RED_LED | GREEN_LED | BLUE_LED; // Set LED's pin as output
    P1OUT &= ~(RED_LED | GREEN_LED | BLUE_LED); // Dim LED's on start
}

void lightUpRGBLed(uint8_t led)
{
    P1OUT |= led;
    rgb_led_state = led_on;
    TA0CTL = 0;
    TA0CCTL0 = CCIE; // Enable interrupt for Timer A0 CCRO
    TA0CTL = TASSEL_2 | ID_0 | MC_1; // SMCLK, /1 divider, Up mode, Enable interrupts
    TA0CCR0 = 16000; // For 1ms interrupt with 16MHz clock
}

void dimRGBLed(uint8_t led)
{
    rgbLedOnCounter = 0; // Reset timer
    P1OUT &= ~led;
    rgb_led_state = led_off;
    TA0CTL = 0;
    TA0CCTL0 &= ~CCIE; // Disable interrupt for Timer A0 CCRO
}
