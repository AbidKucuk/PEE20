/*
 * turn_indicator.h
 *
 *  Created on: Mar 26, 2024
 *      Author: abid
 */

#ifndef INC_DIRECTION_IDENTIFIER_H_
#define INC_DIRECTION_IDENTIFIER_H_

#include <stdint.h>

#define LEFT_LED    BIT3 // P1.3
#define RIGHT_LED   BIT4 // P1.4

void configureDirectionIdentifierLEDS(void);

// Possible states for the direction identifier
typedef enum
{
    Left, Right, Straight
} Direction_Identifier_State;

/*TODO: Should be Detected NFC Turn Command instead from the NFC unit.
 * So that depending on the turn command the corresponding led's light up
 * Should be done when integrating with NFC detection unit.
 */
typedef enum
{
    command_left, command_right, command_straight
} Dummy_NFC_Command;

// Defining direction identifier state
extern Direction_Identifier_State direction_indentifier_state;

// Light up the direction identifier led's
void lightDirectionIndentifierLEDS(Dummy_NFC_Command direction_command);

// Dim the direction identifier led's
void dimDirectionIndentifierLEDS(void);

#endif /* INC_DIRECTION_IDENTIFIER_H_ */
