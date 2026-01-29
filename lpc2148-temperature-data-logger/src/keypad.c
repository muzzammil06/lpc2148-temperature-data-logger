#include <LPC214X.H>        // LPC214x microcontroller register definitions
#include "KeyPd.h"          // Keypad related definitions (row/column pins)

/* ================= KEYPAD LOOK-UP TABLE ================= */
/*
 * LUT maps row and column numbers to key values
 * 4x4 keypad layout:
 * Each key press returns a value from 0 to 15
 */
unsigned char LUT[4][4] =
{
    {0,  1,  2,  3},
    {4,  5,  6,  7},
    {8,  9, 10, 11},
    {12,13, 14,15}
};

/* ================= KEYPAD INITIALIZATION ================= */
/*
 * Function: KeyPdInit
 * Purpose : Configures keypad row pins as output
 *           and initializes them to logic LOW
 */
void KeyPdInit(void)
{
    // Configure row pins (R0–R3) as output pins
    IODIR1 |= ((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));

    // P1.16–P1.19 are configured for output (row lines)

    // Clear all row pins (set them LOW)
    IOCLR1 = ((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));

    // Initializing rows to 0
}

/* ================= COLUMN STATUS CHECK ================= */
/*
 * Function: ColStat
 * Purpose : Checks whether any key is pressed
 * Returns : 1 ? No key pressed
 *           0 ? Key pressed
 */
unsigned char ColStat(void)
{
    // Read column pins (P1.20–P1.23)
    // If all are HIGH (0x0F), no key is pressed
    if((((IOPIN1 >> 20) & 0x0F) == 0x0F))
        return 1;
    else
        return 0;
}

/* ================= KEY VALUE DETECTION ================= */
/*
 * Function: KeyVal
 * Purpose : Detects which key is pressed
 * Method  : Row scanning and column detection
 * Returns : Key value (0–15) using LUT
 */
unsigned char KeyVal(void)
{
    char row_val = 0, col_val = 0;   // Variables to store row & column

    /* --------- ROW 0 CHECK --------- */
    IOCLR1 = (1<<R0);                           // Activate row 0
    IOSET1 = ((1<<R1)|(1<<R2)|(1<<R3));         // Deactivate other rows

    if((((IOPIN1>>20)&0x0F) != 0x0F))            // If any column is LOW
    {
        row_val = 0;                            // Row 0 selected
        goto colcheck;
    }

    /* --------- ROW 1 CHECK --------- */
    IOCLR1 = (1<<R1);                           // Activate row 1
    IOSET1 = ((1<<R0)|(1<<R2)|(1<<R3));

    if((((IOPIN1>>20)&0x0F) != 0x0F))
    {
        row_val = 1;                            // Row 1 selected
        goto colcheck;
    }

    /* --------- ROW 2 CHECK --------- */
    IOCLR1 = (1<<R2);                           // Activate row 2
    IOSET1 = ((1<<R0)|(1<<R1)|(1<<R3));

    if((((IOPIN1>>20)&0x0F) != 0x0F))
    {
        row_val = 2;                            // Row 2 selected
        goto colcheck;
    }

    /* --------- ROW 3 CHECK --------- */
    IOCLR1 = (1<<R3);                           // Activate row 3
    IOSET1 = ((1<<R0)|(1<<R1)|(1<<R2));

    if((((IOPIN1>>20)&0x0F) != 0x0F))
        row_val = 3;                            // Row 3 selected

    /* --------- COLUMN CHECK --------- */
    colcheck:

    // Check which column is LOW
    if(((IOPIN1>>C0)&1) == 0)
        col_val = 0;
    else if(((IOPIN1>>C1)&1) == 0)
        col_val = 1;
    else if(((IOPIN1>>C2)&1) == 0)
        col_val = 2;
    else
        col_val = 3;

    // Clear all rows after key detection
    IOCLR1 = ((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));

    // Initializing rows to 0

    // Return corresponding key value from LUT
    return (LUT[row_val][col_val]);
}
