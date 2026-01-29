#include <LPC214X.H>      // LPC214x microcontroller register definitions
#include "rtc.h"          // RTC initialization and access functions
#include "lcd.h"          // LCD display functions
#include "adc.h"          // ADC initialization and control
#include "types.h"        // Custom data types (u8, u32, f32, etc.)
#include "adc_defines.h"  // ADC channel definitions
#include "uart.h"         // UART communication functions
#include "delay.h"        // Delay routines
#include "lm35.h"         // LM35 temperature sensor functions
#include "keyPd.h"        // Keypad functions
#include "edit.h"         // Edit mode functions

/* ================= MACRO DEFINITIONS ================= */

// LED connected to P0.16
#define LED_PIN (1<<16)

// Edit switch connected to P0.4
#define EDIT_SW (1<<4)

/* ================= GLOBAL VARIABLES ================= */

// RTC time and date variables
long int hour, min, sec, date, month, year, day;

// Current temperature value
volatile f32 temp;

// Flag to indicate edit mode
volatile u8 edit_flag = 0;

// Stores last minute value for UART logging
static u8 last_min = 60;

// Temperature limit for LED control
u32 TEMP_LIMIT = 45;

/* ================= MAIN FUNCTION ================= */
int main()
{
    /* --------- INITIALIZATION SECTION --------- */

    RTC_Init();            // Initialize RTC
    InitLCD();             // Initialize LCD
    Init_ADC(CH1);         // Initialize ADC on channel 1
    InitUART();            // Initialize UART communication
    KeyPdInit();           // Initialize keypad

    // Configure LED as output
    IODIR0 |= LED_PIN;

    // Turn OFF LED initially
    IOSET0 = LED_PIN;

    // Set initial RTC time (HH, MM, SS)
    SetRTCTimeInfo(23, 00, 0);

    // Set initial RTC date (DD, MM, YYYY)
    SetRTCDateInfo(02, 01, 2026);

    // Set day of week
    SetRTCDay(5);

    /* ================= SUPER LOOP ================= */
    while(1)
    {
        /* --------- CHECK EDIT SWITCH --------- */
        if((IOPIN0 & EDIT_SW) == 0)   // If edit switch is pressed
        {
            delay_ms(50);             // Debounce delay
            edit_flag = 1;            // Enter edit mode
        }

        /* --------- NORMAL MODE --------- */
        if(edit_flag == 0)
        {
            // Read current time from RTC
            GetRTCTimeInfo(&hour, &min, &sec);

            // Read current date from RTC
            GetRTCDateInfo(&date, &month, &year);

            // Read day of week
            GetRTCDay(&day);

            // Display time on LCD
            DisplayRTCTime(hour, min, sec);

            // Display date on LCD
            DisplayRTCDate(date, month, year);

            // Display day on LCD
            DisplayRTCDay(day);

            // Read temperature from LM35 sensor in Celsius
            temp = Read_LM35('C');

            // Display temperature on LCD
            DisplayTemp();

            /* --------- TEMPERATURE CONTROL --------- */
            if(temp > TEMP_LIMIT)     // If temperature exceeds limit
                IOCLR0 = LED_PIN;     // Turn OFF LED
            else
                IOSET0 = LED_PIN;     // Turn ON LED

            /* --------- UART LOGGING --------- */
            // Send data once every minute
            if(min != last_min)
            {
                last_min = min;
                UARTTX_Data(hour, min, sec, date, month, year);
            }
            // Send UART data if temperature exceeds limit
            else if(temp > TEMP_LIMIT)
            {
                UARTTX_Data(hour, min, sec, date, month, year);
            }
        }
        /* --------- EDIT MODE --------- */
        else
        {
            EditMode();   // Call edit mode function from edit.c
        }

        delay_ms(200);    // Small delay for stability
    }
}
