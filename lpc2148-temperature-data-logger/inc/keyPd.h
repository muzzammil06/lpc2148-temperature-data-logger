#ifndef __KEYPD_H__
#define __KEYPD_H__        // Header guard to prevent multiple inclusion

#include <LPC214X.H>       // LPC214x microcontroller register definitions

/* ================= ROW PIN DEFINITIONS ================= */
/*
 * Keypad row lines connected to Port 1 pins
 * P1.16 – P1.19
 */
#define R0 16
#define R1 17
#define R2 18
#define R3 19

/* ================= COLUMN PIN DEFINITIONS ================= */
/*
 * Keypad column lines connected to Port 1 pins
 * P1.20 – P1.23
 */
#define C0 20
#define C1 21
#define C2 22
#define C3 23

/* ================= KEYPAD FUNCTION PROTOTYPES ================= */
/*
 * Initializes keypad row pins as outputs
 */
void KeyPdInit(void);

/*
 * Checks keypad column status
 * Returns:
 *   1 ? No key pressed
 *   0 ? Key pressed
 */
unsigned char ColStat(void);

/*
 * Detects and returns the pressed key value
 */
unsigned char KeyVal(void);

/* ================= KEY LOOKUP TABLE ================= */
/*
 * 4×4 keypad lookup table
 * Maps row and column to key value
 */
extern unsigned char LUT[4][4];

#endif   // End of __KEYPD_H__
