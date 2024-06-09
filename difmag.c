#include "lpc.h"

/*  Compute Average Magnitude Difference Function */

/* Inputs: */
/*  SPEECH - Low pass filtered speech */
/*           Indices MIN_N1 through MAX_N1+LPITA-1 are read, where */
/*      MIN_N1 = (MAXLAG - MAX_TAU)/2+1  MAX_TAU = max of TAU(I) for I=1,LTAU
*/
/*      MAX_N1 = (MAXLAG - MIN_TAU)/2+1  MIN_TAU = min of TAU(I) for I=1,LTAU
*/
/*  LPITA  - Length of speech buffer */
/*  TAU    - Table of lags */
/*           Indices 1 through LTAU read. */
/*  LTAU   - Number of lag values to compute */
/*  MAXLAG - Maximum possible lag value */
/* Outputs: */
/*  (All of these outputs are also read, but only after being written.) */
/*  AMDF   - Average Magnitude Difference for each lag in TAU */
/*           Indices 1 through LTAU written */
/*  MINPTR - Index of minimum AMDF value */
/*  MAXPTR - Index of maximum AMDF value */

/* This subroutine has no local state. */

/* Subroutine */ int difmag_(float *speech, int32_t *lpita, int32_t *tau, 
	int32_t *ltau, int32_t *maxlag, float *amdf, int32_t *minptr, int32_t *
	maxptr)
{
    /* System generated locals */
    int32_t i__1, i__2;
    float r__1;

    /* Local variables */
    int32_t i__, j, n1, n2;
    float sum;

/*       Arguments */
/*       Local variables that need not be saved */
/*       Local state */
/*       None */
    /* Parameter adjustments */
    --amdf;
    --tau;
    --speech;

    /* Function Body */
    *minptr = 1;
    *maxptr = 1;
    i__1 = *ltau;
    for (i__ = 1; i__ <= i__1; ++i__) {
	n1 = (*maxlag - tau[i__]) / 2 + 1;
	n2 = n1 + *lpita - 1;
	sum = 0.f;
	i__2 = n2;
	for (j = n1; j <= i__2; j += 4) {
	    sum += (r__1 = speech[j] - speech[j + tau[i__]], abs(r__1));
	}
	amdf[i__] = sum;
	if (amdf[i__] < amdf[*minptr]) {
	    *minptr = i__;
	}
	if (amdf[i__] > amdf[*maxptr]) {
	    *maxptr = i__;
	}
    }
    return 0;
} /* difmag_ */

