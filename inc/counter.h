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

extern int time_counter;
extern int distance_counter;
extern int r_nfc_counter;
extern int g_nfc_counter;
extern int b_nfc_counter;


void startCounting(void);
void stopCounting(void);
void resetCounters(void);


#endif /* INC_COUNTER_H_ */
