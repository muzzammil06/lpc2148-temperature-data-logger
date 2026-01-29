#include <LPC214X.H>      // LPC214x microcontroller register definitions
#include "lcd.h"          // LCD driver functions
#include "rtc.h"          // RTC (Real Time Clock) definitions
#include "keyPd.h"        // Keypad driver
#include "uart.h"         // UART communication functions
#include "types.h"        // Custom data types (u8, u32, f32, etc.)
#include "delay.h"        // Delay routines

/* ================= EXTERNAL VARIABLES FROM main.c ================= */

// Flag to indicate edit mode status
extern volatile u8 edit_flag;

// Current temperature value
extern volatile f32 temp;

// RTC time and date variables
extern long int hour, min, sec, date, month, year, day;

// Temperature set limit (modifiable)
extern u32 TEMP_LIMIT;

/* ================= NUMBER INPUT FUNCTION ================= */
/*
 * Function: GetKeyNumber
 * Purpose : Reads numeric input from keypad
 * Args    : digits - maximum number of digits allowed
 *           max    - maximum value allowed
 * Returns : Entered number (limited to max)
 */
u32 GetKeyNumber(u8 digits, u32 max)
{
    u32 val = 0;          // Variable to store entered value
    u8 key, count = 0;   // key = keypad value, count = digit count

    while(1)
    {
        while(ColStat());        // Wait until a key is pressed
        delay_ms(10);            // Debounce delay
        key = KeyVal();          // Read pressed key
        while(!ColStat());			// Wait until key is released
				if(key == 14 && count > 0)
        {
            val /= 10;
            count--;
            CmdLCD(0x10);   // Cursor left
            CharLCD(' ');
            CmdLCD(0x10);
            continue;
        }
        if(key == 15)            // If ENTER/EXIT key pressed
        {
            break;               // Exit number entry loop
        }

        if(key <= 9)             // If numeric key pressed
        {
            if(count < digits)   // Check digit limit
            {
                val = (val * 10) + key;   // Build number
                CharLCD(key + '0');       // Display digit on LCD
                count++;
            }
        }
    }
    return val;                  // Return entered number
}

/* ================= LEAP YEAR CHECK ================= */
u8 IsLeapYear(u32 y)
{
    if((y % 400) == 0) return 1;
    if((y % 100) == 0) return 0;
    if((y % 4) == 0)   return 1;
    return 0;
}


/* ================= MONTH ? MAX DAYS ================= */
u8 GetMaxDays(u32 m, u32 y)
{
    switch(m)
    {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;

        case 4: case 6: case 9: case 11:
            return 30;

        case 2:
            return IsLeapYear(y) ? 29 : 28;

        default:
            return 31;
    }
}


/* ================= MAIN EDIT MENU DISPLAY ================= */
/*
 * Displays main edit menu on LCD
 */
void DisplayMainEditMenu(void)
{
    CmdLCD(0x01);                // Clear LCD

    CmdLCD(0x80);                // First line
    StrLCD("1)EDIT RTC INFO");   // RTC edit option

    CmdLCD(0xC0);                // Second line
    StrLCD("2)E.SET 3)EXIT");    // Set-point edit and exit options
}

/* ================= RTC EDIT SUB MENU ================= */
/*
 * Allows editing of RTC parameters like hour, minute, date, etc.
 */
void EditRTCMenu(void)
{
    u8 key,value; 	// Variable to store key press
		u8 updated = 0;

    CmdLCD(0x01);                // Clear LCD
    CmdLCD(0x80);
    StrLCD("1.H 2.M 3.S 4.D");   // Hour, Minute, Second, Date
    CmdLCD(0xC0);
    StrLCD("5.M 6.Y 7.DAY 8.E"); // Month, Year, Day, Exit

    while(1)
    {
        while(ColStat());        // Wait for key press
        delay_ms(10);            // Debounce delay
        key = KeyVal();          // Read key
        while(!ColStat());       // Wait for key release

        CmdLCD(0x01);            // Clear LCD before update
				updated = 0;
        switch(key)
        {
            case 1:              // Set Hour
                StrLCD("SET HOUR:");
                hour = GetKeyNumber(2, 23);
                HOUR = hour;
								updated = 1;
                break;

            case 2:              // Set Minute
                StrLCD("SET MIN:");
                min = GetKeyNumber(2, 59);
                MIN = min;
								updated = 1;
                break;

            case 3:              // Set Second
                StrLCD("SET SEC:");
                sec = GetKeyNumber(2, 59);
                SEC = sec;
								updated = 1;
                break;
            case 4:              // Set Date
									StrLCD("SET DATE:");
								  value = GetKeyNumber(2, 31);

								if(value >= 1 && value <= GetMaxDays(month, year))
								{
												date = value;
												DOM  = date;        // ? update only if valid
												updated = 1;
								}
								break;


            case 5:              // Set Month
								StrLCD("SET MONTH:");
								value = GetKeyNumber(2, 12);
								if(value >= 1 && value <= 12)
								{
									if(date <= GetMaxDays(value, year))
									{
										month = value;
										MONTH = month;     // ? safe update
										updated = 1;
									}
							 }
								break;


            case 6:              // Set Year
								StrLCD("SET YEAR:");
								value = GetKeyNumber(4, 2099);

								if(date <= GetMaxDays(month, value))
								{
											year = value;
											YEAR = year;      // ? safe update
											updated = 1;
								}
							  break;


            case 7:   // Set Day of Week
								StrLCD("SET DAY(1-7):");
								value = GetKeyNumber(1, 7);

								if(value >= 1 && value <= 7)
								{
										day = value - 1;   // map 1–7 to 0–6
										DOW = day;
									  updated = 1;
                } 
								break;


            case 8:              // Exit RTC edit menu
                return;
        }
				CmdLCD(0x01);
				if(updated)
						StrLCD("UPDATED");       // Confirmation message
				else
					 StrLCD("reject change");
				delay_ms(500);
        CmdLCD(0x01);            // Redisplay RTC edit menu
        CmdLCD(0x80);
        StrLCD("1.H 2.M 3.S 4.D");
        CmdLCD(0xC0);
        StrLCD("5.M 6.Y 7.DAY 8.E");
    }
}

/* ================= SET POINT EDIT ================= */
/*
 * Allows editing of temperature set-point
 */
void EditSetPoint(void)
{
    CmdLCD(0x01);                // Clear LCD
    StrLCD("SET TEMP LIM:");     // Prompt user

    TEMP_LIMIT = GetKeyNumber(2, 99); // Read temperature limit

    CmdLCD(0x01);
    StrLCD("LIMIT UPDATED");     // Confirmation message
    delay_ms(500);
}

/* ================= EDIT MODE (CALLED FROM main.c) ================= */
/*
 * Main edit mode handler
 * Controls RTC edit, set-point edit, and exit
 */
void EditMode(void)
{
    u8 key;                      // Store key input

    DisplayMainEditMenu();       // Show main menu
    UARTTxStr("\r\n*** Time Editing Mode Activated ***\r\n");

    while(1)
    {
        while(ColStat());        // Wait for key press
        delay_ms(10);
        key = KeyVal();          // Read key
        while(!ColStat());       // Wait for release

        switch(key)
        {
            case 1:              // RTC Edit Mode
                UARTTxStr("*** RTC EDIT MODE ***\r\n");
                EditRTCMenu();
                DisplayMainEditMenu();
                break;

            case 2:              // Temperature Set-Point Edit
                UARTTxStr("*** SET POINT EDIT MODE ***\r\n");
                EditSetPoint();
                DisplayMainEditMenu();
                break;

            case 3:              // Exit Edit Mode
                UARTTxStr("*** EXIT EDIT MODE ***\r\n");
                edit_flag = 0;
                CmdLCD(0x01);
                return;

            default:
                break;
        }
    }
}
