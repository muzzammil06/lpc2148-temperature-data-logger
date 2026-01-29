/* ================= LCD FUNCTION PROTOTYPES ================= */

/*
 * Initializes the LCD module in 8-bit mode
 */
void InitLCD(void);

/*
 * Sends a command to the LCD
 */
void CmdLCD(unsigned char);

/*
 * Displays a single character on the LCD
 */
void CharLCD(unsigned char);

/*
 * Low-level function to write data/command to LCD
 */
void DispLCD(unsigned char);

/*
 * Displays a null-terminated string on the LCD
 */
void StrLCD(unsigned char *);

/*
 * Displays a signed integer value on the LCD
 */
void IntLCD(signed long int);

/*
 * Displays a floating-point value on the LCD
 */
void FltLCD(float);

/*
 * Stores a custom character font in LCD CGRAM
 */
void StoreCustCharFont(void);
