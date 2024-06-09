#include "lpc.h"

/* ********************************************************************* */

/*  Check RC's, repeat previous frame's RC's if unstable */

/* Input: */
/*  ORDER - Number of RC's */
/*  RC1F  - Previous frame's RC's */
/*          Indices 1 through ORDER may be read. */
/* Input/Output: */
/*  RC2F  - Present frame's RC's */
/*          Indices 1 through ORDER may be read, and written. */

/* This subroutine has no local state. */

/* Subroutine */ int rcchk_(int32_t *order, float *rc1f, float *rc2f)
{
    /* System generated locals */
    int32_t i__1;
    float r__1;

    /* Local variables */
    int32_t i__;

/*       Arguments */
/*       Local variables that need not be saved */
    /* Parameter adjustments */
    --rc2f;
    --rc1f;

    /* Function Body */
    i__1 = *order;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if ((r__1 = rc2f[i__], abs(r__1)) > .99f) {
	    goto L10;
	}
    }
    return 0;
/*       Note: In version embedded in other software, all calls to ERROR 
*/
/*       should probably be removed. */
L10:

/*       This call to ERROR is only needed for debugging purposes. */

/*       CALL ERROR('RCCHK',2,I) */
    i__1 = *order;
    for (i__ = 1; i__ <= i__1; ++i__) {
	rc2f[i__] = rc1f[i__];
    }
    return 0;
} /* rcchk_ */

