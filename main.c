#include <lib/oled.h>
#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lib/i2c.h"

#include "inc/ussr.h"
#include "inc/rgb_led.h"

const int BUTTON_HOLD_LIMIT = 3; // If holding button down for 3 seconds reset report counters

char DRIVING_TEXT[] = "Vroom vrooooooom I am driving fast";
char REPORT_TEXT[] = "Reporting since not driving";
char RESET_TEXT[] = "I just reset the report";

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

    configureLed(); // Set up RGB LED
    configureUSSR(); // Set up USSR

    i2c_init(); // initialize I2C to use with OLED
    ssd1306_init(); // Initialize OLED
    ssd1306_clearDisplay(); // Clear OLED display
    printOLEDText(REPORT_TEXT);

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
                    printOLEDText(RESET_TEXT);
                    startButtonPressTimer();
                }
                else
                {
                    button_state = un_pressed;
                    stopButtonPressTimer();
                    lightLed(GREEN_LED);
                    robot_state = driving;
                    printOLEDText(DRIVING_TEXT);

                }
                break;
            case driving:
                stopButtonPressTimer();
                robot_state = not_driving;
                printOLEDText(REPORT_TEXT);
                break;
            }

        }

        break;
    case un_pressed:
        if (led_state == led_on)
        {
            if (ledOnCounter < LED_ON_TIME)
            {
                ledOnCounter++;
            }

            else
            {
                dimLed(GREEN_LED);
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
                && ledOnCounter == 0)
        {
            button_state = pressed;
            startButtonPressTimer();

        }
        break;
    }
    P2IFG &= ~BUTTON;
}

