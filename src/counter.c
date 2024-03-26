/*
 * counter.c
 *
 *  Created on: Mar 26, 2024
 *      Author: abid
 */


#include <msp430.h>
#include "../inc/counter.h"

// Set default not counting
Counter_State counter_state = not_counting;

void startCounting(){
    counter_state = counting;
}

void stopCounting(){
    counter_state = not_counting;
}

