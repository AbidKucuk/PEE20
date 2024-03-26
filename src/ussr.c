/*
 * rgb_led.h
 *
 *  Created on: Mar 23, 2024
 *      Author: abid
 */

#include <msp430.h>
#include "../inc/ussr.h"


const int BUTTON_PRESS_DELAY = 1000; // Press delay in ms
const int BUTTON_HOLD_LIMIT = 2000; // If holding button down for x ms reset report counters

int buttonPressCounter = 0; // Set default at 0
Button_State button_state = un_pressed; // Set default value as un_pressed


void configureUSSR(){
    P2DIR &= ~BUTTON; // Set button as input
    P2REN |= BUTTON; // Enable pulldown resistor for button
    P2OUT &= ~BUTTON; // Set button as pulldown
    P2IE |= BUTTON; // Set interrupt for button
    P2IES &= ~BUTTON; // Set interrupt for low -> high
    P2IFG &= ~BUTTON; // Clear interrupt flag for button
}


void startButtonPressTimer()
{
    TA0CTL = 0;
    TA0CCTL0 = CCIE; // Enable interrupt for Timer A0 CCRO
    TA0CTL = TASSEL_2 | ID_0 | MC_1; // SMCLK, /1 divider, Up mode, Enable interrupts
    TA0CCR0 = 16000; // For 1ms interrupt with 16MHz clock
}


void stopButtonPressTimer()
{
    buttonPressCounter = 0; // Reset timer
    TA0CTL = 0;
    TA0CCTL0 &= ~CCIE; // Disable interrupt for Timer A0 CCRO
    P2IE |= BUTTON; // Set interrupt for button
}
