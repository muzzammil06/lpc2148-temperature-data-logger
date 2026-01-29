#ifndef RTC_DEFINES_H
#define RTC_DEFINES_H        // Header guard to prevent multiple inclusion

/* ================= SYSTEM CLOCK DEFINITIONS ================= */

// External oscillator frequency (12 MHz)
#define FOSC 12000000

// CPU clock frequency (FOSC × 5 using PLL)
#define CCLK (5 * FOSC)

// Peripheral clock frequency (CCLK / 4)
#define PCLK (CCLK / 4)

/* ================= RTC PRESCALER DEFINITIONS ================= */
/*
 * RTC runs using a 32.768 kHz clock
 * PREINT and PREFRAC values are calculated from PCLK
 */
#define PREINT_VAL  ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK - (PREINT_VAL + 1) * 32768)

/* ================= CCR REGISTER BIT DEFINITIONS ================= */

// RTC Enable bit (starts RTC)
#define RTC_ENABLE  (1 << 0)

// RTC Reset bit (resets RTC counters)
#define RTC_RESET   (1 << 1)

// RTC Clock Source select bit
#define RTC_CLKSRC  (1 << 4)

//#define _LPC2148    // Reserved for LPC2148 specific configuration

#endif   // End of RTC_DEFINES_H
