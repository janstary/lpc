#include <math.h>
#include "lpc.h"

/* ********************************************************************* */

/* Compute RMS energy. */

/* Input: */
/*  LEN    - Length of speech buffer */
/*  SPEECH - Speech buffer */
/*           Indices 1 through LEN read. */
/* Output: */
/*  RMS    - Root Mean Square energy */

/* This subroutine has no local state. */

/* Subroutine */ int energy_(int32_t *len, float *speech, float *rms)
{
    /* System generated locals */
    int32_t i__1;

    /* Local variables */
    int32_t i__;

/*       Arguments */
/*       Local variables that need not be saved */
    /* Parameter adjustments */
    --speech;

    /* Function Body */
    *rms = 0.f;
    i__1 = *len;
    for (i__ = 1; i__ <= i__1; ++i__) {
	*rms += speech[i__] * speech[i__];
    }
    *rms = sqrt(*rms / *len);
    return 0;
} /* energy_ */

