#include <math.h>
#include "lpc.h"

/*   Convert Reflection Coefficients to Predictor Coeficients */

/* Inputs: */
/*  RC     - Reflection coefficients */
/*           Indices 1 through ORDER read. */
/*  ORDER  - Number of RC's */
/*  GPRIME - Excitation modification gain */
/* Outputs: */
/*  PC     - Predictor coefficients */
/*           Indices 1 through ORDER written. */
/*           Indices 1 through ORDER-1 are read after being written. */
/*  G2PASS - Excitation modification sharpening factor */

/* This subroutine has no local state. */

/* Subroutine */ int irc2pc_(float *rc, float *pc, int32_t *order, float *gprime,
	 float *g2pass)
{
    /* System generated locals */
    int32_t i__1, i__2;

    /* Local variables */
    float temp[10];
    int32_t i__, j;

/* 	Arguments */
/*   LPC Configuration parameters: */
/* Frame size, Prediction order, Pitch period */
/*       Local variables that need not be saved */
    /* Parameter adjustments */
    --pc;
    --rc;

    /* Function Body */
    *g2pass = 1.f;
    i__1 = *order;
    for (i__ = 1; i__ <= i__1; ++i__) {
	*g2pass *= 1.f - rc[i__] * rc[i__];
    }
    *g2pass = *gprime * sqrt(*g2pass);
    pc[1] = rc[1];
    i__1 = *order;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = i__ - 1;
	for (j = 1; j <= i__2; ++j) {
	    temp[j - 1] = pc[j] - rc[i__] * pc[i__ - j];
	}
	i__2 = i__ - 1;
	for (j = 1; j <= i__2; ++j) {
	    pc[j] = temp[j - 1];
	}
	pc[i__] = rc[i__];
    }
    return 0;
} /* irc2pc_ */

