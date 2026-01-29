#include "types.h"          // Custom data types (u32, f32, etc.)
#include "delay.h"          // Delay functions
#include <LPC21XX.H>        // LPC21xx microcontroller register definitions
#include "adc_defines.h"    // ADC-related macros and bit definitions

/* ================= ADC CHANNEL PIN SELECTION ================= */
/*
 * Lookup table for ADC pin configuration
 * Each entry corresponds to ADC channel pin function
 */
u32 adcChSel[4] =
{
    AIN0_PIN_0_27,          // ADC Channel 0 ? P0.27
    AIN1_PIN_0_28,          // ADC Channel 1 ? P0.28
    AIN2_PIN_0_29,          // ADC Channel 2 ? P0.29
    AIN3_PIN_0_30           // ADC Channel 3 ? P0.30
};

/* ================= ADC INITIALIZATION ================= */
/*
 * Function: Init_ADC
 * Purpose : Initializes ADC and selects required channel pin
 * Args    : chNo ? ADC channel number (0–3)
 */
void Init_ADC(u32 chNo)
{
    // Clear pin function bits for selected ADC channel
    PINSEL1 &= ~(adcChSel[chNo]);

    // Set pin function for ADC input
    PINSEL1 |= adcChSel[chNo];

    // Enable ADC (PDN_BIT) and set ADC clock divider
    ADCR |= (1<<PDN_BIT) | (CLKDIV<<CLKDIV_BITS);
}

/* ================= ADC READ FUNCTION ================= */
/*
 * Function: Read_ADC
 * Purpose : Reads ADC value from selected channel
 * Args    : chNo     ? ADC channel number
 *           eAR      ? Pointer to store equivalent analog voltage
 *           adcDVal  ? Pointer to store digital ADC value
 */
void Read_ADC(u32 chNo, f32 *eAR, u32 *adcDVal)
{
    // Clear previous channel selection and start bits
    ADCR &= 0xFFFFFF00;

    // Select ADC channel and start conversion
    ADCR |= (1<<ADC_CONV_START_BIT) | (1<<chNo);

    delay_us(3);            // Small delay for ADC conversion start

    // Wait until conversion is complete (DONE bit = 1)
    while(((ADDR >> DONE_BIT) & 1) == 0);

    // Stop ADC conversion
    ADCR &= ~(1<<ADC_CONV_START_BIT);

    // Extract 10-bit digital ADC value
    *adcDVal = (ADDR >> DIGITAL_DATA_BITS) & 1023;

    // Convert digital value to analog voltage (0–3.3V)
    *eAR = (*adcDVal) * (3.3 / 1023);
}
