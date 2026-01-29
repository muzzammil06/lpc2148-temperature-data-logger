#include <LPC214X.H>        // LPC214x microcontroller register definitions
#include "rtc_defines.h"    // RTC register macros and constants
#include "types.h"          // Custom data types (u8, s32, u32, f32)
#include "lcd.h"            // LCD display functions
#include "lm35.h"           // LM35 temperature sensor functions

// External temperature variable read from LM35
extern volatile f32 temp;

/* ================= DAY NAME LOOKUP TABLE ================= */
/*
 * Maps day number (0–6) to day names
 * 0 ? SUN, 1 ? MON, ..., 6 ? SAT
 */
u8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/* ================= RTC INITIALIZATION ================= */
/*
 * Initializes RTC with prescaler values and enables it
 */
void RTC_Init(void)
{
    CCR = RTC_RESET;        // Reset RTC
    PREINT  = PREINT_VAL;   // Set integer prescaler value
    PREFRAC = PREFRAC_VAL;  // Set fractional prescaler value
    CCR = RTC_ENABLE;       // Enable RTC
}

/* ================= READ RTC TIME ================= */
/*
 * Reads current time from RTC registers
 */
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
    *hour   = HOUR;         // Read hour register
    *minute = MIN;          // Read minute register
    *second = SEC;          // Read second register
}

/* ================= DISPLAY TIME ON LCD ================= */
/*
 * Displays time in HH:MM:SS format
 */
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
    CmdLCD(0x80);           // Move cursor to first line, first position

    CharLCD(hour/10 + 48);  // Display hour tens digit
    CharLCD(hour%10 + 48);  // Display hour units digit
    CharLCD(':');

    CharLCD(minute/10 + 48);// Display minute tens digit
    CharLCD(minute%10 + 48);// Display minute units digit
    CharLCD(':');

    CharLCD(second/10 + 48);// Display second tens digit
    CharLCD(second%10 + 48);// Display second units digit
}

/* ================= READ RTC DATE ================= */
/*
 * Reads current date from RTC registers
 */
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
    *date  = DOM;           // Read date (day of month)
    *month = MONTH;         // Read month
    *year  = YEAR;          // Read year
}

/* ================= DISPLAY DATE ON LCD ================= */
/*
 * Displays date in DD/MM/YYYY format
 */
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
    CmdLCD(0xC0);           // Move cursor to second line

    CharLCD(date/10 + 48);  // Date tens digit
    CharLCD(date%10 + 48);  // Date units digit
    CharLCD('/');

    CharLCD(month/10 + 48); // Month tens digit
    CharLCD(month%10 + 48); // Month units digit
    CharLCD('/');

    IntLCD(year);           // Display full year
}

/* ================= SET RTC TIME ================= */
/*
 * Sets RTC hour, minute and second
 */
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
    HOUR = hour;            // Set hour register
    MIN  = minute;          // Set minute register
    SEC  = second;          // Set second register
}

/* ================= SET RTC DATE ================= */
/*
 * Sets RTC date, month and year
 */
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
    DOM   = date;           // Set day of month
    MONTH = month;          // Set month
    YEAR  = year;           // Set year
}

/* ================= READ RTC DAY ================= */
/*
 * Reads day of week from RTC
 */
void GetRTCDay(s32 *day)
{
    *day = DOW;             // Read day-of-week register
}

/* ================= DISPLAY DAY ================= */
/*
 * Displays day name (SUN–SAT) on LCD
 */
void DisplayRTCDay(u32 day)
{
    CmdLCD(0xCC);           // Position cursor for day display
    StrLCD(week[day]);      // Display day string
}

/* ================= SET RTC DAY ================= */
/*
 * Sets day of week in RTC
 */
void SetRTCDay(u32 day)
{
    DOW = day;              // Set day-of-week register
}

/* ================= DISPLAY TEMPERATURE ================= */
/*
 * Displays temperature value on LCD
 */
void DisplayTemp(void)
{
    CmdLCD(0x89);           // Set cursor position for temperature
    StrLCD("T:");           // Display label

    IntLCD((int)temp);      // Display integer part of temperature
    CharLCD(223);           // Degree symbol
    CharLCD('C');           // Celsius unit
}
