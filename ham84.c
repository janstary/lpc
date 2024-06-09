#include "lpc.h"

/* ***************************************************************** */

/*  Hamming 8,4 Decoder - can correct 1 out of seven bits */
/*   and can detect up to two errors. */

/* Input: */
/*  INPUT  - Seven bit data word, 4 bits parameter and */
/*           4 bits parity information */
/* Input/Output: */
/*  ERRCNT - Sums errors detected by Hamming code */
/* Output: */
/*  OUTPUT - 4 corrected parameter bits */

/* This subroutine is entered with an eight bit word in INPUT.  The 8th */
/* bit is parity and is stripped off.  The remaining 7 bits address the */
/* hamming 8,4 table and the output OUTPUT from the table gives the 4 */
/* bits of corrected data.  If bit 4 is set, no error was detected. */
/* ERRCNT is the number of errors counted. */

/* This subroutine has no local state. */

/* Subroutine */ int ham84_(int32_t *input, int32_t *output, int32_t *errcnt)
{
    /* Initialized data */

    static int32_t dactab[128] = { 16,0,0,3,0,5,14,7,0,9,14,11,14,13,30,14,0,
	    9,2,7,4,7,7,23,9,25,10,9,12,9,14,7,0,5,2,11,5,21,6,5,8,11,11,27,
	    12,5,14,11,2,1,18,2,12,5,2,7,12,9,2,11,28,12,12,15,0,3,3,19,4,13,
	    6,3,8,13,10,3,13,29,14,13,4,1,10,3,20,4,4,7,10,9,26,10,4,13,10,15,
	    8,1,6,3,6,5,22,6,24,8,8,11,8,13,6,15,1,17,2,1,4,1,6,15,8,1,10,15,
	    12,15,15,31 };

    int32_t i__, j, parity;

/*       Arguments */
/*       Parameters/constants */
/*       Local variables that need not be saved */
/*  Determine parity of input word */
    parity = *input & 255;
    parity ^= parity / 16;
    parity ^= parity / 4;
    parity ^= parity / 2;
    parity &= 1;
    i__ = dactab[*input & 127];
    *output = i__ & 15;
    j = i__ & 16;
    if (j != 0) {
/*          No errors detected in seven bits */
	if (parity != 0) {
	    ++(*errcnt);
	}
    } else {
/*          One or two errors detected */
	++(*errcnt);
	if (parity == 0) {
/*             Two errors detected */
	    ++(*errcnt);
	    *output = -1;
	}
    }
    return 0;
} /* ham84_ */

