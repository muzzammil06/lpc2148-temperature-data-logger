#include <LPC214X.H>    // LPC214x microcontroller register definitions

/* ================= PIN FUNCTION CONFIGURATION ================= */
/*
 * Function: CfgPinFunc
 * Purpose : Configures the function of a specific GPIO pin
 * Args    : portNo ? Port number (only Port 0 supported here)
 *           pinNo  ? Pin number within the port
 *           Func   ? Pin function selection value
 *                     00 ? GPIO
 *                     01 ? Function 1
 *                     10 ? Function 2
 *                     11 ? Function 3
 */
void CfgPinFunc(int portNo, int pinNo, int Func)
{
    // Check if Port 0 is selected
    if(portNo == 0)
    {
        // Pins P0.0 to P0.15 use PINSEL0 register
        if(pinNo < 16)
        {
            // Clear the 2-bit function field for the pin
            // Then set the required function
            PINSEL0 = ((PINSEL0 & ~(3 << (pinNo * 2))) |
                       (Func << (pinNo * 2)));
        }
        // Pins P0.16 to P0.31 use PINSEL1 register
        else
        {
            // Clear the 2-bit function field for the pin
            // Then set the required function
            PINSEL1 = ((PINSEL1 & ~(3 << ((pinNo - 16) * 2))) |
                       (Func << ((pinNo - 16) * 2)));
        }
    }
    else
    {
        // FOR NOTHING (Only Port 0 handled in this function)
    }
}
