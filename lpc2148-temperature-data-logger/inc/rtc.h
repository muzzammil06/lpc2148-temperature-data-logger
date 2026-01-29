#ifndef RTC_H
#define RTC_H        // Header guard to prevent multiple inclusion

/* ================= RTC FUNCTION PROTOTYPES ================= */

/*
 * Initializes the Real Time Clock (RTC)
 */
void RTC_Init(void);

/*
 * Reads current time from RTC
 * Parameters:
 *   hour   ? pointer to store hour value
 *   minute ? pointer to store minute value
 *   second ? pointer to store second value
 */
void GetRTCTimeInfo(long int *, long int *, long int *);

/*
 * Displays time on LCD in HH:MM:SS format
 */
void DisplayRTCTime(unsigned long int,
                    unsigned long int,
                    unsigned long int);

/*
 * Reads current date from RTC
 * Parameters:
 *   date  ? pointer to store date
 *   month ? pointer to store month
 *   year  ? pointer to store year
 */
void GetRTCDateInfo(long int *, long int *, long int *);

/*
 * Displays date on LCD in DD/MM/YYYY format
 */
void DisplayRTCDate(unsigned long int,
                    unsigned long int,
                    unsigned long int);

/*
 * Sets RTC time (hour, minute, second)
 */
void SetRTCTimeInfo(unsigned long int,
                    unsigned long int,
                    unsigned long int);

/*
 * Sets RTC date (date, month, year)
 */
void SetRTCDateInfo(unsigned long int,
                    unsigned long int,
                    unsigned long int);

/*
 * Reads day of week from RTC
 */
void GetRTCDay(long int *);

/*
 * Displays day of week on LCD
 */
void DisplayRTCDay(unsigned long int);

/*
 * Sets day of week in RTC
 */
void SetRTCDay(unsigned long int);

/*
 * Displays temperature on LCD
 */
void DisplayTemp(void);

#endif   // End of RTC_H
