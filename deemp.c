#include "lpc.h"

/*  De-Emphasize output speech with   1 / ( 1 - .75z**-1 ) */
/*    cascaded with 200 Hz high pass filter */
/*    ( 1 - 1.9998z**-1 + z**-2 ) / ( 1 - 1.75z**-1 + .78z**-2 ) */

/*  WARNING!  The coefficients above may be out of date with the code */
/*  below.  Either that, or some kind of transformation was performed */
/*  on the coefficients above to create the code below. */

/* Input: */
/*  N  - Number of samples */
/* Input/Output: */
/*  X  - Speech */
/*       Indices 1 through N are read before being written. */

/* This subroutine maintains local state from one call to the next.  If */
/* you want to switch to using a new audio stream for this filter, or */
/* reinitialize its state for any other reason, call the ENTRY */
/* INITDEEMP. */

/* Subroutine */ int deemp_(float *x, int32_t *n, struct lpc10_decoder_state *st)
{
    /* Initialized data */

    float *dei1;
    float *dei2;
    float *deo1;
    float *deo2;
    float *deo3;

    /* System generated locals */
    int32_t i__1;
    float r__1;

    /* Local variables */
    int32_t k;
    float dei0;

/*       Arguments */
/*       Local variables that need not be saved */
/*       Local state */
/*       All of the locals saved below were not given explicit initial */
/*       values in the original code.  I think 0 is a safe choice. */
    /* Parameter adjustments */
    if (x) {
	--x;
	}

    /* Function Body */

    dei1 = &(st->dei1);
    dei2 = &(st->dei2);
    deo1 = &(st->deo1);
    deo2 = &(st->deo2);
    deo3 = &(st->deo3);

    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	dei0 = x[k];
	r__1 = x[k] - *dei1 * 1.9998f + *dei2;
	x[k] = r__1 + *deo1 * 2.5f - *deo2 * 2.0925f + *deo3 * .585f;
	*dei2 = *dei1;
	*dei1 = dei0;
	*deo3 = *deo2;
	*deo2 = *deo1;
	*deo1 = x[k];
    }
    return 0;
} /* deemp_ */
