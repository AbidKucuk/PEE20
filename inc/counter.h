/*
 * counter.h
 *
 *  Created on: Mar 26, 2024
 *      Author: abid
 */

#ifndef INC_COUNTER_H_
#define INC_COUNTER_H_


#include <stdint.h>


// Defining possible states of the counter
typedef enum
{
    counting, not_counting
} Counter_State;


// Defining counter state
extern Counter_State counter_state;


void startCounting(void);
void stopCounting(void);


#endif /* INC_COUNTER_H_ */
