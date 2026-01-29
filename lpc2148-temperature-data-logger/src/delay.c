/* ================= MICROSECOND DELAY ================= */
/*
 * Function: delay_us
 * Purpose : Generates approximate delay in microseconds
 * Method  : Empty loop execution
 */
void delay_us(unsigned int tdiy)
{
    tdiy *= 12;            // Scale value for ~1 microsecond delay
    while(tdiy--);         // Busy wait loop
}

/* ================= MILLISECOND DELAY ================= */
/*
 * Function: delay_ms
 * Purpose : Generates approximate delay in milliseconds
 */
void delay_ms(unsigned int tdiy)
{
    tdiy *= 12000;         // Scale value for ~1 millisecond delay
    while(tdiy--);         // Busy wait loop
}

/* ================= SECOND DELAY ================= */
/*
 * Function: delay_s
 * Purpose : Generates approximate delay in seconds
 */
void delay_s(unsigned int tdiy)
{
    tdiy *= 12000000;      // Scale value for ~1 second delay
    while(tdiy--);         // Busy wait loop
}
