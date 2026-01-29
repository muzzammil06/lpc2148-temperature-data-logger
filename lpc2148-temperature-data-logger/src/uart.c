#include <LPC214X.H>      // LPC214x microcontroller register definitions
#include "UART.h"         // UART function prototypes
#include "types.h"        // Custom data types (u32, f32, s8, etc.)
#include "pinconnect.h"   // Pin function configuration function

// External temperature value
extern volatile f32 temp;

// External temperature limit
extern u32 TEMP_LIMIT;

/* ================= UART INITIALIZATION ================= */
/*
 * Function: InitUART
 * Purpose : Initializes UART0 for serial communication
 *           with 9600 baud rate (assuming PCLK)
 */
void InitUART()
{
    // Configure P0.0 as TXD0 and P0.1 as RXD0
    CfgPinFunc(0, 0, 1);
    CfgPinFunc(0, 1, 1);

    // Enable access to Divisor Latch Registers
    U0LCR = 0x83;

    // Set baud rate divisor (9600 baud)
    U0DLL = 97;
    U0DLM = 0;

    // 8-bit data, 1 stop bit, no parity
    U0LCR = 0x03;
}

/* ================= TRANSMIT SINGLE CHARACTER ================= */
/*
 * Function: UARTTxChar
 * Purpose : Transmits a single character via UART
 */
void UARTTxChar(s8 ch)
{
    // Wait until Transmit Holding Register is empty
    while(!(U0LSR & (1<<5)));   // THRE bit

    // Load character into transmit register
    U0THR = ch;
}

/* ================= TRANSMIT STRING ================= */
/*
 * Function: UARTTxStr
 * Purpose : Transmits a null-terminated string via UART
 */
void UARTTxStr(s8 *ptr)
{
    while(*ptr)                // Loop until null character
        UARTTxChar(*ptr++);
}

/* ================= TRANSMIT UNSIGNED INTEGER ================= */
/*
 * Function: UARTTxU32
 * Purpose : Transmits unsigned 32-bit integer via UART
 */
void UARTTxU32(u32 num)
{
    char buf[10];              // Buffer to store digits
    int i = 0;

    if(num == 0)               // Handle zero explicitly
    {
        UARTTxChar('0');
        return;
    }

    // Convert number to ASCII digits (reverse order)
    while(num)
    {
        buf[i++] = num % 10 + '0';
        num /= 10;
    }

    // Transmit digits in correct order
    while(i--)
        UARTTxChar(buf[i]);
}

/* ================= TRANSMIT FLOAT ================= */
/*
 * Function: UARTTxF32
 * Purpose : Transmits floating-point number (2 decimal places)
 */
void UARTTxF32(f32 fnum)
{
    u32 ipart;
    u8 i;

    // Handle negative number
    if(fnum < 0)
    {
        UARTTxChar('-');
        fnum = -fnum;
    }

    // Extract integer part
    ipart = (u32)fnum;
    UARTTxU32(ipart);
    UARTTxChar('.');

    // Extract and transmit fractional part (2 digits)
    fnum = fnum - ipart;
    for(i = 0; i < 2; i++)
    {
        fnum *= 10;
        UARTTxChar((u8)fnum + '0');
        fnum -= (u8)fnum;
    }
}

/* ================= TRANSMIT FULL SYSTEM DATA ================= */
/*
 * Function: UARTTX_Data
 * Purpose : Transmits temperature, time, and date information
 *           with alert/status indication
 */
void UARTTX_Data(u32 hour, u32 min, u32 sec,
                 u32 date, u32 month, u32 year)
{
    // Display ALERT or INFO based on temperature limit
    if(temp > TEMP_LIMIT)
        UARTTxStr("[ALERT] ");
    else
        UARTTxStr("[INFO] ");

    // Transmit temperature
    UARTTxStr("Temp: ");
    UARTTxF32(temp);
    UARTTxStr(" C | ");

    // Transmit time in HH:MM:SS format
    UARTTxChar(hour/10 + '0');
    UARTTxChar(hour%10 + '0');
    UARTTxChar(':');
    UARTTxChar(min/10 + '0');
    UARTTxChar(min%10 + '0');
    UARTTxChar(':');
    UARTTxChar(sec/10 + '0');
    UARTTxChar(sec%10 + '0');
    UARTTxStr(" ");

    // Transmit date in DD/MM/YYYY format
    UARTTxChar(date/10 + '0');
    UARTTxChar(date%10 + '0');
    UARTTxChar('/');
    UARTTxChar(month/10 + '0');
    UARTTxChar(month%10 + '0');
    UARTTxChar('/');
    UARTTxU32(year);

    // Over-temperature warning
    if(temp > TEMP_LIMIT)
        UARTTxStr(" **OVER TEMP**");

    // New line
    UARTTxStr("\r\n");
}
