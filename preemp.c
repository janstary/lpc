#include "lpc.h"

/*   Preemphasize speech with a single-zero filter. */
/*  (When coef = .9375, preemphasis is as in LPC43.) */

/* Inputs: */
/*  NSAMP  - Number of samples to filter */
/*  INBUF  - Input speech buffer */
/*           Indices 1 through NSAMP are read. */
/*  COEF   - Preemphasis coefficient */
/* Input/Output: */
/*  Z      - Filter state */
/* Output: */
/*  PEBUF  - Preemphasized speech buffer (can be equal to INBUF) */
/*           Indices 1 through NSAMP are modified. */

/* This subroutine has no local state. */

/* Subroutine */ int preemp_(float *inbuf, float *pebuf, int32_t *nsamp, float *
	coef, float *z__)
{
    /* System generated locals */
    int32_t i__1;

    /* Local variables */
    float temp;
    int32_t i__;

/*       Arguments */
/*       Local variables */

/*       None of these need to have their values saved from one */
/*       invocation to the next. */

/*       Logically, this subroutine computes the output sequence */
/*       pebuf(1:nsamp) defined by: */

/*       pebuf(i) = inbuf(i) - coef * inbuf(i-1) */

/*       where inbuf(0) is defined by the value of z given as input to */
/*       this subroutine. */

/*       What is this filter's frequency response and phase response? */

/*       Why is this filter applied to the speech? */

/*       Could it be more efficient to apply multiple filters */
/*       simultaneously, by combining them into one equivalent filter? */

/*       Are there ever cases when "factoring" one high-order filter into 
*/
/*       multiple smaller-order filter actually reduces the number of */
/*       arithmetic operations needed to perform them? */
/*       When I first read this subroutine, I didn't understand why the */
/*       variable temp was used.  It seemed that the statements in the do 
*/
/*       loop could be replaced with the following: */

/*           pebuf(i) = inbuf(i) - coef * z */
/*           z = inbuf(i) */

/*       The reason for temp is so that even if pebuf and inbuf are the */
/*       same arrays in memory (i.e., they are aliased), then this */
/*       subroutine will still work correctly.  I didn't realize this */
/*       until seeing the comment after PEBUF above that says "(can be */
/*       equal to INBUF)". */
    /* Parameter adjustments */
    --pebuf;
    --inbuf;

    /* Function Body */
    i__1 = *nsamp;
    for (i__ = 1; i__ <= i__1; ++i__) {
	temp = inbuf[i__] - *coef * *z__;
	*z__ = inbuf[i__];
	pebuf[i__] = temp;
/* L10: */
    }
    return 0;
} /* preemp_ */

