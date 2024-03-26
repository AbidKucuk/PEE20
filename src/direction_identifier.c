/*
 * turn_indicator.c
 *
 *  Created on: Mar 26, 2024
 *      Author: abid
 */

#include <inc/direction_identifier.h>
#include <msp430.h>

// Default is going straight
Direction_Identifier_State direction_indentifier_state = Straight;

void configureDirectionIdentifierLEDS()
{
    P1DIR |= LEFT_LED | RIGHT_LED; // Set LED's as output
    P1OUT |= (LEFT_LED | RIGHT_LED); // Light up both LED's on start because default is straight
}

void lightDirectionIndentifierLEDS(Dummy_NFC_Command direction_command)
{
    switch (direction_command)
    {
    case command_left:
        direction_indentifier_state = Left;
        P1OUT &= ~RIGHT_LED;
        P1OUT |= LEFT_LED;
        break;

    case command_right:
        direction_indentifier_state = Right;
        P1OUT &= ~LEFT_LED;
        P1OUT |= RIGHT_LED;
        break;
    case command_straight:
        direction_indentifier_state = Straight;
        P1OUT |= (LEFT_LED | RIGHT_LED);
        break;
    }
}

void dimDirectionIndentifierLEDS(void)
{
    P1OUT &= ~(LEFT_LED | RIGHT_LED);
}

