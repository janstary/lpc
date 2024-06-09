#include "lpc.h"

/* Calculate and remove DC bias from buffer. */

/* Input: */
/*  LEN    - Length of speech buffers */
/*  SPEECH - Input speech buffer */
/*           Indices 1 through LEN read. */
/* Output: */
/*  SIGOUT - Output speech buffer */
/*           Indices 1 through LEN written */

/* This subroutine has no local state. */

/* Subroutine */ int dcbias_(int32_t *len, float *speech, float *sigout)
{
    /* System generated locals */
    int32_t i__1;

    /* Local variables */
    float bias;
    int32_t i__;

/* 	Arguments */
/*       Local variables that need not be saved */
    /* Parameter adjustments */
    --sigout;
    --speech;

    /* Function Body */
    bias = 0.f;
    i__1 = *len;
    for (i__ = 1; i__ <= i__1; ++i__) {
	bias += speech[i__];
    }
    bias /= *len;
    i__1 = *len;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sigout[i__] = speech[i__] - bias;
    }
    return 0;
} /* dcbias_ */

