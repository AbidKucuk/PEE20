/*
 * report.c
 *
 *  Created on: Mar 26, 2024
 *      Author: abid
 */

#include <msp430.h>
#include "../inc/report.h"
#include <lib/oled.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lib/i2c.h"
#include <stdio.h>

// By default reporting
Report_State report_state = reporting;

char TIME_STRING[] = "Time: ";
char DISTANCE_STRING[] = "Distance: ";
char R_STRING[] = "Red: ";
char G_STRING[] = "Green: ";
char B_STRING[] = "Blue: ";

void report(int time, int distance, int r, int g, int b)
{

    // This code basically creates the string to display for the OLED
    char time_s[14];
    char distance_s[18];
    char r_s[5];
    char g_s[5];
    char b_s[5];

    sprintf(time_s, "%d", time);
    sprintf(distance_s, "%d", distance);
    sprintf(r_s, "%d", r);
    sprintf(g_s, "%d", g);
    sprintf(b_s, "%d", b);

    char result_time_s[20];
    char result_distance_s[25];
    char result_r_s[20];
    char result_g_s[20];
    char result_b_s[20];

    strcpy(result_time_s, TIME_STRING);
    strcat(result_time_s, time_s);

    strcpy(result_distance_s, DISTANCE_STRING);
    strcat(result_distance_s, distance_s);

    strcpy(result_r_s, R_STRING);
    strcat(result_r_s, r_s);

    strcpy(result_g_s, G_STRING);
    strcat(result_g_s, g_s);

    strcpy(result_b_s, B_STRING);
    strcat(result_b_s, b_s);

// Now finally they can get displayed on the OLED
    ssd1306_clearDisplay();
    ssd1306_printText(0, 1, result_time_s);
    ssd1306_printText(0, 2, result_distance_s);
    ssd1306_printText(0, 3, result_r_s);
    ssd1306_printText(0, 4, result_g_s);
    ssd1306_printText(0, 5, result_b_s);

}
