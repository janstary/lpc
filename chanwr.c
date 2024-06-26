#include "lpc.h"

/* CHANWR: */
/*   Place quantized parameters into bitstream */

/* Input: */
/*  ORDER  - Number of reflection coefficients (not really variable) */
/*  IPITV  - Quantized pitch/voicing parameter */
/*  IRMS   - Quantized energy parameter */
/*  IRC    - Quantized reflection coefficients */
/*           Indices 1 through ORDER read. */
/* Output: */
/*  IBITS  - Serial bitstream */
/*           Indices 1 through 54 written. */
/*           Bit 54, the SYNC bit, alternates from one call to the next. */

/* Subroutine CHANWR maintains one bit of local state from one call to */
/* the next, in the variable ISYNC.  I believe that this one bit is only */
/* intended to allow a receiver to resynchronize its interpretation of */
/* the bit stream, by looking for which of the 54 bits alternates every */
/* frame time.  This is just a simple framing mechanism that is not */
/* useful when other, higher overhead framing mechanisms are used to */
/* transmit the coded frames. */

/* I'm not going to make an entry to reinitialize this bit, since it */
/* doesn't help a receiver much to know whether the first sync bit is a 0 */
/* or a 1.  It needs to examine several frames in sequence to have */
/* reasonably good assurance that its framing is correct. */


/* CHANRD: */
/*   Reconstruct parameters from bitstream */

/* Input: */
/*  ORDER  - Number of reflection coefficients (not really variable) */
/*  IBITS  - Serial bitstream */
/*           Indices 1 through 53 read (SYNC bit is ignored). */
/* Output: */
/*  IPITV  - Quantized pitch/voicing parameter */
/*  IRMS   - Quantized energy parameter */
/*  IRC    - Quantized reflection coefficients */
/*           Indices 1 through ORDER written */

/* Entry CHANRD has no local state. */



/*   IBITS is 54 bits of LPC data ordered as follows: */
/* 	R1-0, R2-0, R3-0,  P-0,  A-0, */
/* 	R1-1, R2-1, R3-1,  P-1,  A-1, */
/* 	R1-2, R4-0, R3-2,  A-2,  P-2, R4-1, */
/* 	R1-3, R2-2, R3-3, R4-2,  A-3, */
/* 	R1-4, R2-3, R3-4, R4-3,  A-4, */
/* 	 P-3, R2-4, R7-0, R8-0,  P-4, R4-4, */
/* 	R5-0, R6-0, R7-1,R10-0, R8-1, */
/* 	R5-1, R6-1, R7-2, R9-0,  P-5, */
/* 	R5-2, R6-2,R10-1, R8-2,  P-6, R9-1, */
/* 	R5-3, R6-3, R7-3, R9-2, R8-3, SYNC */
static int chanwr_0_(int n__, int32_t *order, int32_t *ipitv, 
	int32_t *irms, int32_t *irc, int32_t *ibits,
			       struct lpc10_encoder_state *st)
{
    /* Initialized data */

    int32_t *isync;
    static int32_t bit[10] = { 2,4,8,8,8,8,16,16,16,16 };
    static int32_t iblist[53] = { 13,12,11,1,2,13,12,11,1,2,13,10,11,2,1,10,
	    13,12,11,10,2,13,12,11,10,2,1,12,7,6,1,10,9,8,7,4,6,9,8,7,5,1,9,8,
	    4,6,1,5,9,8,7,5,6 };

    /* System generated locals */
    int32_t i__1;

    /* Local variables */
    int32_t itab[13], i__;

/*       Arguments */
/*       Parameters/constants */
/*       These arrays are not Fortran PARAMETER's, but they are defined */
/*       by DATA statements below, and their contents are never altered. 
*/
/*       Local variables that need not be saved */
/*       Local state */
/*       ISYNC is only used by CHANWR, not by ENTRY CHANRD. */

    /* Parameter adjustments */
    --irc;
    --ibits;

    /* Function Body */
    switch(n__) {
	case 1: goto L_chanrd;
	}

    isync = &(st->isync);

/* ***********************************************************************
 */
/* 	Place quantized parameters into bitstream */
/* ***********************************************************************
 */
/*   Place parameters into ITAB */
    itab[0] = *ipitv;
    itab[1] = *irms;
    itab[2] = 0;
    i__1 = *order;
    for (i__ = 1; i__ <= i__1; ++i__) {
	itab[i__ + 2] = irc[*order + 1 - i__] & 32767;
    }
/*   Put 54 bits into IBITS array */
    for (i__ = 1; i__ <= 53; ++i__) {
	ibits[i__] = itab[iblist[i__ - 1] - 1] & 1;
	itab[iblist[i__ - 1] - 1] /= 2;
    }
    ibits[54] = *isync & 1;
    *isync = 1 - *isync;
    return 0;
/* ***********************************************************************
 */
/* 	Reconstruct parameters from bitstream */
/* ***********************************************************************
 */

L_chanrd:
/*   Reconstruct ITAB */
    for (i__ = 1; i__ <= 13; ++i__) {
	itab[i__ - 1] = 0;
    }
    for (i__ = 1; i__ <= 53; ++i__) {
	itab[iblist[54 - i__ - 1] - 1] = (itab[iblist[54 - i__ - 1] - 1] << 1)
		 + ibits[54 - i__];
    }
/*   Sign extend RC's */
    i__1 = *order;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if ((itab[i__ + 2] & bit[i__ - 1]) != 0) {
	    itab[i__ + 2] -= bit[i__ - 1] << 1;
	}
    }
/*   Restore variables */
    *ipitv = itab[0];
    *irms = itab[1];
    i__1 = *order;
    for (i__ = 1; i__ <= i__1; ++i__) {
	irc[i__] = itab[*order + 4 - i__ - 1];
    }
    return 0;
} /* chanwr_ */

/* Subroutine */ int chanwr_(int32_t *order, int32_t *ipitv, int32_t *irms, 
	int32_t *irc, int32_t *ibits, struct lpc10_encoder_state *st)
{
    return chanwr_0_(0, order, ipitv, irms, irc, ibits, st);
    }

/* Subroutine */ int chanrd_(int32_t *order, int32_t *ipitv, int32_t *irms, 
	int32_t *irc, int32_t *ibits)
{
    return chanwr_0_(1, order, ipitv, irms, irc, ibits, 0);
    }
