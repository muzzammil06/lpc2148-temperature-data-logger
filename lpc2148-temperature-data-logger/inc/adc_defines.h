// adc_defines.h

/* ================= CLOCK DEFINITIONS ================= */

// External oscillator frequency (12 MHz)
#define FOSC 12000000

// CPU clock frequency (FOSC × 5 using PLL)
#define CCLK (FOSC * 5)

// Peripheral clock frequency (CCLK / 4)
#define PCLK (CCLK / 4)

// Required ADC clock frequency (max 4.5 MHz for LPC214x)
#define ADCCLK 3000000

// ADC clock divider value
#define CLKDIV ((PCLK / ADCCLK) - 1)

/* ================= ADCR REGISTER BIT DEFINITIONS ================= */

// Clock divider bit position in ADCR (bits 8–15)
#define CLKDIV_BITS        8   //@8-15

// Power-down bit position in ADCR
#define PDN_BIT            21

// Start conversion bit position in ADCR
#define ADC_CONV_START_BIT 24

/* ================= ADDR REGISTER BIT DEFINITIONS ================= */

// Digital conversion result bits (bits 6–15)
#define DIGITAL_DATA_BITS  6   //@6-15

// Conversion complete (DONE) bit position
#define DONE_BIT           31

/* ================= ADC PIN FUNCTION DEFINITIONS ================= */

// ADC channel 0 pin select (P0.27)
#define AIN0_PIN_0_27 0x00400000

// ADC channel 1 pin select (P0.28)
#define AIN1_PIN_0_28 0x01000000

// ADC channel 2 pin select (P0.29)
#define AIN2_PIN_0_29 0x04000000

// ADC channel 3 pin select (P0.30)
#define AIN3_PIN_0_30 0x10000000

/* ================= ADC CHANNEL NUMBERS ================= */

// ADC channel numbers
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3

// Add more defines as and when required
