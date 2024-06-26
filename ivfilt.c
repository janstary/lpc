#include "lpc.h"

/*   2nd order inverse filter, speech is decimated 4:1 */

/* Input: */
/*  LEN    - Length of speech buffers */
/*  NSAMP  - Number of samples to filter */
/*  LPBUF  - Low pass filtered speech buffer */
/*           Indices LEN-NSAMP-7 through LEN read. */
/* Output: */
/*  IVBUF  - Inverse filtered speech buffer */
/*           Indices LEN-NSAMP+1 through LEN written. */
/*  IVRC   - Inverse filter reflection coefficients (for voicing) */
/*          Indices 1 and 2 both written (also read, but only after writing).
*/

/* This subroutine has no local state. */

/* Subroutine */ int ivfilt_(float *lpbuf, float *ivbuf, int32_t *len, int32_t *
	nsamp, float *ivrc)
{
    /* System generated locals */
    int32_t i__1;

    /* Local variables */
    int32_t i__, j, k;
    float r__[3], pc1, pc2;

/* 	Arguments */
/*       Local variables that need not be saved */
/*       Local state */
/*       None */
/*  Calculate Autocorrelations */
    /* Parameter adjustments */
    --ivbuf;
    --lpbuf;
    --ivrc;

    /* Function Body */
    for (i__ = 1; i__ <= 3; ++i__) {
	r__[i__ - 1] = 0.f;
	k = (i__ - 1) << 2;
	i__1 = *len;
	for (j = (i__ << 2) + *len - *nsamp; j <= i__1; j += 2) {
	    r__[i__ - 1] += lpbuf[j] * lpbuf[j - k];
	}
    }
/*  Calculate predictor coefficients */
    pc1 = 0.f;
    pc2 = 0.f;
    ivrc[1] = 0.f;
    ivrc[2] = 0.f;
    if (r__[0] > 1e-10f) {
	ivrc[1] = r__[1] / r__[0];
	ivrc[2] = (r__[2] - ivrc[1] * r__[1]) / (r__[0] - ivrc[1] * r__[1]);
	pc1 = ivrc[1] - ivrc[1] * ivrc[2];
	pc2 = ivrc[2];
    }
/*  Inverse filter LPBUF into IVBUF */
    i__1 = *len;
    for (i__ = *len + 1 - *nsamp; i__ <= i__1; ++i__) {
	ivbuf[i__] = lpbuf[i__] - pc1 * lpbuf[i__ - 4] - pc2 * lpbuf[i__ - 8];
    }
    return 0;
} /* ivfilt_ */

