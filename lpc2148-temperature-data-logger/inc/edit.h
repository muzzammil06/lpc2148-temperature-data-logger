#ifndef __EDIT_H__
#define __EDIT_H__          // Header guard to prevent multiple inclusion

#include "types.h"          // Custom data types (u8, u32)

/* ================= EDIT MODE MAIN FUNCTION ================= */
/*
 * Enters and controls the overall edit mode
 * Called from main program
 */
void EditMode(void);

/* ================= INTERNAL EDIT FUNCTIONS ================= */
/*
 * Displays the main edit menu on LCD
 */
void DisplayMainEditMenu(void);

/*
 * Displays and handles RTC edit sub-menu
 * Allows editing time, date, and day
 */
void EditRTCMenu(void);

/*
 * Allows editing of temperature set-point
 */
void EditSetPoint(void);

/*
 * Checks whether a given year is a leap year
 * Returns:
 *   1 ? Leap year
 *   0 ? Not a leap year
 */
u8 IsLeapYear(u32);

/*
 * Returns maximum number of days in a given month and year
 */
u8 GetMaxDays(u32, u32);

/* ================= KEYPAD NUMBER INPUT ================= */
/*
 * Reads numeric input from keypad
 * Parameters:
 *   digits ? Maximum number of digits allowed
 *   max    ? Maximum value allowed
 * Returns:
 *   Entered number
 */
u32 GetKeyNumber(u8 digits, u32 max);

#endif   // End of __EDIT_H__
