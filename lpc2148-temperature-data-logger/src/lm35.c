// lm35.c
#include "types.h"          // Custom data types (u8, u32, f32)
#include "adc.h"            // ADC read functions
#include "adc_defines.h"    // ADC channel definitions

/* ================= LM35 TEMPERATURE READ FUNCTION ================= */
/*
 * Function: Read_LM35
 * Purpose : Reads temperature from LM35 sensor
 * Args    : tType
 *           'C' ? Celsius
 *           'F' ? Fahrenheit
 * Returns : Temperature value as float
 */
f32 Read_LM35(u8 tType)
{
    u32 adcDVal;           // Stores raw ADC digital value
    f32 eAR, temp;         // eAR = equivalent analog voltage

    // Read ADC value from channel CH1
    // eAR  ? analog voltage
    // adcDVal ? digital ADC value
    Read_ADC(CH1, &eAR, &adcDVal);

    // LM35 gives 10mV per degree Celsius
    // Multiply voltage by 100 to get temperature in Celsius
    temp = eAR * 100;

    // Convert Celsius to Fahrenheit if requested
    if(tType == 'F')
        temp = ((temp * (9/5.0)) + 32);

    return temp;           // Return temperature value
}
