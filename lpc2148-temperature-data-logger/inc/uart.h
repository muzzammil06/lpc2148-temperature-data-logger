#include "types.h"     // Custom data types (u32, f32, s8)

/* ================= UART FUNCTION PROTOTYPES ================= */

/*
 * Initializes UART module for serial communication
 */
void InitUART(void);

/*
 * Transmits a single character via UART
 */
void UARTTxChar(s8);

/*
 * Transmits a null-terminated string via UART
 */
void UARTTxStr(s8 *);

/*
 * Transmits an unsigned 32-bit integer via UART
 */
void UARTTxU32(u32);

/*
 * Transmits a floating-point number via UART
 */
void UARTTxF32(f32);

/*
 * Transmits complete system data (temperature, time, date)
 */
void UARTTX_Data(u32, u32, u32, u32, u32, u32);
