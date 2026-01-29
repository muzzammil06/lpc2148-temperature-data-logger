#include <LPC214X.H>     // LPC214x microcontroller register definitions
#include "delay.h"       // Delay routines
#include "lcd.h"         // LCD function prototypes
#include "types.h"       // Custom data types (u8, s32, f32, etc.)
#include "defines.h"     // Bit manipulation macros

/* ================= LCD PIN DEFINITIONS ================= */

// LCD data lines connected to P0.8–P0.15
#define LCD_DAT 0xff    

// LCD control pins
#define RS 5   // Register Select pin (P0.5)
#define RW 6   // Read/Write pin (P0.6)
#define EN 7   // Enable pin (P0.7)

/* ================= LCD INITIALIZATION ================= */
/*
 * Function: InitLCD
 * Purpose : Initializes LCD in 8-bit mode
 */
void InitLCD(void)
{
    // Configure P0.5–P0.15 as output pins
    IODIR0 |= ((LCD_DAT << 8) | (1<<RS) | (1<<RW) | (1<<EN));
    // Data lines + control lines set as output

    delay_ms(20);        // LCD power-on delay (minimum 15ms)

    CmdLCD(0x30);        // Function set: 8-bit mode
    delay_ms(10);        // Delay > 5ms

    CmdLCD(0x30);        // Repeat command for reliability
    delay_ms(1);         // Delay > 160µs

    CmdLCD(0x30);        // Repeat function set
    delay_ms(1);

    CmdLCD(0x38);        // 8-bit mode, 2 lines, 5x7 font
    CmdLCD(0x10);        // Display OFF
    CmdLCD(0x01);        // Clear display
    CmdLCD(0x06);        // Entry mode: cursor increment
    CmdLCD(0x0F);        // Display ON, cursor ON, blinking ON
}

/* ================= SEND LCD COMMAND ================= */
/*
 * Sends a command to LCD
 */
void CmdLCD(u8 cmd)
{
    IOCLR0 = 1<<RS;      // RS = 0 ? command mode
    DispLCD(cmd);        // Send command to LCD
}

/* ================= SEND CHARACTER TO LCD ================= */
/*
 * Sends a single character to LCD
 */
void CharLCD(u8 dat)
{
    IOSET0 = 1<<RS;      // RS = 1 ? data mode
    DispLCD(dat);        // Send data to LCD
}

/* ================= LOW LEVEL LCD DATA WRITE ================= */
/*
 * Writes data/command to LCD with enable pulse
 */
void DispLCD(u8 val)
{
    IOCLR0 = 1<<RW;                      // RW = 0 ? write mode
    WRITEBYTE(IOPIN0, 8, val);           // Write value to P0.8–P0.15
    IOSET0 = 1<<EN;                      // EN = 1 (enable LCD)
    delay_ms(2);                         // Enable pulse width
    IOCLR0 = 1<<EN;                      // EN = 0
    delay_ms(5);                         // Command execution delay
}

/* ================= DISPLAY STRING ================= */
/*
 * Displays a string on LCD
 */
void StrLCD(u8 *ptr)
{
    while(*ptr != '\0')                  // Loop until null character
        CharLCD(*ptr++);                 // Display each character
}

/* ================= DISPLAY INTEGER ================= */
/*
 * Displays a signed integer on LCD
 */
void IntLCD(s32 num)
{
    u8 a[10];                            // Buffer for digits
    s8 i = 0;

    if(num == 0)                         // If number is zero
        CharLCD('0');
    else
    {
        if(num < 0)                     // Handle negative numbers
        {
            num = -num;
            CharLCD('-');
        }

        // Convert integer to ASCII digits
        while(num > 0)
        {
            a[i++] = num % 10 + 48;
            num = num / 10;
        }

        // Display digits in correct order
        for(--i; i >= 0; i--)
            CharLCD(a[i]);
    }
}

/* ================= DISPLAY FLOAT ================= */
/*
 * Displays floating-point number on LCD
 */
void FltLCD(f32 fnum)
{
    u32 num, i;

    if(fnum < 0)                         // Handle negative value
    {
        CharLCD('-');
        fnum = -fnum;
    }

    num = fnum;                          // Integer part
    IntLCD(num);                         // Display integer part
    CharLCD('.');                        // Decimal point

    // Display 6 digits after decimal
    for(i = 0; i < 6; i++)
    {
        fnum = (fnum - num) * 10;
        num = fnum;
        CharLCD(num + 48);
    }
}

/* ================= STORE CUSTOM CHARACTER ================= */
/*
 * Stores a custom character pattern in CGRAM
 */
void StoreCustCharFont(void)
{
    u8 i;
    u8 LUT[] = {0x00,0x00,0x04,0x0C,0x1C,0x1C,0x1C,0x00};

    for(i = 0; i < 8; i++)               // Write pattern to CGRAM
        CharLCD(LUT[i]);
}
