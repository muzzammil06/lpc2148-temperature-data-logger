// adc.h
#include "types.h"     // Custom data types (u32, f32)

/* ================= ADC FUNCTION PROTOTYPES ================= */

/*
 * Initializes the ADC module and selects the given channel
 * chNo ? ADC channel number (0–3)
 */
void Init_ADC(u32 chNo);

/*
 * Reads ADC value from the selected channel
 * chNo     ? ADC channel number
 * eAR      ? Pointer to store equivalent analog voltage
 * adcDVal  ? Pointer to store digital ADC value
 */
void Read_ADC(u32 chNo, f32 *eAR, u32 *adcDVal);
