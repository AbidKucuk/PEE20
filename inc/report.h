/*
 * report.h
 *
 *  Created on: Mar 26, 2024
 *      Author: abid
 */

#ifndef INC_REPORT_H_
#define INC_REPORT_H_

typedef enum
{
    reporting, not_reporting
} Report_State;

extern Report_State report_state;

extern char TIME_STRING[];
extern char DISTANCE_STRING[];
extern char R_STRING[];
extern char G_STRING[];
extern char B_STRING[];


void report(int time, int distance, int r, int g, int b);


#endif /* INC_REPORT_H_ */
