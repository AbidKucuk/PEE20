#include <lib/oled.h>
#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lib/i2c.h"

#include "inc/ussr.h"
#include "inc/rgb_led.h"
#include "inc/counter.h"
#include "inc/direction_identifier.h"
#include "inc/report.h"

char DRIVING_TEXT[] = "Vroom vrooooooom I am driving fast";
int dummy_time = 538; // In seconds
int dummy_distance = 44; // In cm
int dummy_r_count = 2;
int dummy_g_count = 1;
int dummy_b_count = 5;

void printOLEDText(char text[])
{
    ssd1306_clearDisplay(); // Clear OLED display
    ssd1306_printText(0, 1, text); // Print text on OLED display
}

typedef enum
{
    driving, not_driving
} Robot_State; // To identify state of the robot

volatile Robot_State robot_state = not_driving;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    DCOCTL = 0;
    BCSCTL1 = CALBC1_16MHZ; // Set range
    DCOCTL = CALDCO_16MHZ;  // Set DCO step + modulation */

    configureRGBLed(); // Set up RGB LED
    configureUSSR(); // Set up USSR

    i2c_init(); // initialize I2C to use with OLED
    ssd1306_init(); // Initialize OLED
    ssd1306_clearDisplay(); // Clear OLED display

    configureDirectionIdentifierLEDS(); // Set up direction identifiers
    report(time_counter, distance_counter, r_nfc_counter, g_nfc_counter,
           b_nfc_counter);

    __enable_interrupt();
    while (1)
    {

    }

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A_ISR(void)
{
    switch (button_state)
    {
    case pressed:
        if (buttonPressCounter < BUTTON_PRESS_DELAY)
        {
            buttonPressCounter++;
        }
        else
        {
            switch (robot_state)
            {
            case not_driving:
                if ((P2IN &= BUTTON) != 0)
                {
                    buttonPressCounter++;
                }
                else
                {
                    if (buttonPressCounter >= BUTTON_HOLD_LIMIT)
                    {
                        stopButtonPressTimer();
                        button_state = un_pressed;
                        resetCounters();
                        report(time_counter, distance_counter, r_nfc_counter,
                               g_nfc_counter, b_nfc_counter);
                    }
                    else
                    {
                        lightDirectionIndentifierLEDS(command_right);
                        button_state = un_pressed;
                        stopButtonPressTimer();
                        startCounting();
                        lightUpRGBLed(GREEN_LED);
                        robot_state = driving;
                        report_state = reporting;
                        printOLEDText(DRIVING_TEXT);
                    }
                }
                break;
            case driving:
                stopButtonPressTimer();
                stopCounting();
                robot_state = not_driving;

                time_counter = dummy_time;
                distance_counter = dummy_distance;
                r_nfc_counter = dummy_r_count;
                g_nfc_counter = dummy_g_count;
                b_nfc_counter = dummy_b_count;

                report(time_counter, distance_counter, r_nfc_counter,
                       g_nfc_counter, b_nfc_counter);
                break;
            }

        }

        break;
    case un_pressed:
        if (rgb_led_state == led_on)
        {
            if (rgbLedOnCounter < RGB_LED_ON_TIME)
            {
                rgbLedOnCounter++;
            }

            else
            {
                dimRGBLed(GREEN_LED);
            }
        }
        break;
    }
}

#pragma vector = PORT2_VECTOR
__interrupt
void Port_2_ISR(void)
{

    switch (robot_state)
    {
    case not_driving:
    case driving:
        if (((P2IFG &= BUTTON) != 0) && buttonPressCounter == 0
                && rgbLedOnCounter == 0)
        {
            button_state = pressed;
            startButtonPressTimer();

        }
        break;
    }
    P2IFG &= ~BUTTON;
}

