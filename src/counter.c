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

int time_counter = 0;
int distance_counter = 0;
int r_nfc_counter = 0;
int g_nfc_counter = 0;
int b_nfc_counter = 0;

// TODO: Implement when integrating with other units
void startCounting()
{
    counter_state = counting;
}

// TODO: Implement when integrating with other units
void stopCounting()
{
    counter_state = not_counting;
}

void resetCounters()
{
    time_counter = 0;
    distance_counter = 0;
    r_nfc_counter = 0;
    g_nfc_counter = 0;
    b_nfc_counter = 0;
}

