/* ================= BIT MANIPULATION MACROS ================= */

/*
 * READBIT
 * Reads the value of a specific bit in a word
 * Returns 0 or 1
 */
#define READBIT(WORD, BP) ((WORD >> BP) & 1)

/*
 * SETBIT
 * Sets (makes 1) the bit at bit position BP
 */
#define SETBIT(WORD, BP) WORD |= (1 << BP)

/*
 * CLRBIT
 * Clears (makes 0) the bit at bit position BP
 */
#define CLRBIT(WORD, BP) WORD &= ~(1 << BP)

/*
 * CPLBIT
 * Toggles (complements) the bit at bit position BP
 */
#define CPLBIT(WORD, BP) WORD ^= (1 << BP)

/*
 * WRITEBIT
 * Writes a specific bit value (0 or 1) at bit position BP
 * BIT should be 0 or 1
 */
#define WRITEBIT(WORD, BP, BIT) WORD = ((WORD & ~(1 < BP)) | (BIT << BP))

/*
 * WRITENIBBLE
 * Writes a 4-bit nibble at starting bit position SBP
 */
#define WRITENIBBLE(WORD, SBP, NIBBLE) \
        WORD = ((WORD & ~(0xF << SBP)) | (NIBBLE << SBP))

/*
 * WRITEBYTE
 * Writes an 8-bit byte at starting bit position SBP
 */
#define WRITEBYTE(WORD, SBP, BYTE) \
        WORD = ((WORD & ~(0xFF << SBP)) | (BYTE << SBP))

/*
 * WRITEHWORD
 * Writes a 16-bit half-word at starting bit position SBP
 */
#define WRITEHWORD(WORD, SBP, HWORD) \
        WORD = ((WORD & ~(0xFFFF << SBP)) | (HWORD << SBP))
