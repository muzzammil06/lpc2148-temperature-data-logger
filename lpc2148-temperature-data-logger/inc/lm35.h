#ifndef _LM35_H_
#define _LM35_H_          // Header guard to prevent multiple inclusion

#include "types.h"        // Custom data types (u8, f32)

/* ================= LM35 FUNCTION PROTOTYPE ================= */

/*
 * Reads temperature from LM35 sensor
 * Parameter:
 *   tType ? 'C' for Celsius, 'F' for Fahrenheit
 * Returns:
 *   Temperature value as float
 */
f32 Read_LM35(u8 tType);

#endif   // End of _LM35_H_
