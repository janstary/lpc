#include "lpc.h"

/* *********************************************************************** */

/*   31 Point Equiripple FIR Low-Pass Filter */
/*     Linear phase, delay = 15 samples */

/* 	Passband:  ripple = 0.25 dB, cutoff =  800 Hz */
/* 	Stopband:  atten. =  40. dB, cutoff = 1240 Hz */

/* Inputs: */
/*  LEN    - Length of speech buffers */
/*  NSAMP  - Number of samples to filter */
/*  INBUF  - Input speech buffer */
/*           Indices len-nsamp-29 through len are read. */
/* Output: */
/*  LPBUF  - Low passed speech buffer (must be different array than INBUF) */
/*           Indices len+1-nsamp through len are written. */

/* This subroutine has no local state. */

/* Subroutine */ int lpfilt_(float *inbuf, float *lpbuf, int32_t *len, int32_t *
	nsamp)
{
    /* System generated locals */
    int32_t i__1;

    /* Local variables */
    int32_t j;
    float t;

/* 	Arguments */
/* 	Parameters/constants */
/*       Local variables that need not be saved */
/*       Local state */
/*       None */
    /* Parameter adjustments */
    --lpbuf;
    --inbuf;

    /* Function Body */
    i__1 = *len;
    for (j = *len + 1 - *nsamp; j <= i__1; ++j) {
	t = (inbuf[j] + inbuf[j - 30]) * -.0097201988f;
	t += (inbuf[j - 1] + inbuf[j - 29]) * -.0105179986f;
	t += (inbuf[j - 2] + inbuf[j - 28]) * -.0083479648f;
	t += (inbuf[j - 3] + inbuf[j - 27]) * 5.860774e-4f;
	t += (inbuf[j - 4] + inbuf[j - 26]) * .0130892089f;
	t += (inbuf[j - 5] + inbuf[j - 25]) * .0217052232f;
	t += (inbuf[j - 6] + inbuf[j - 24]) * .0184161253f;
	t += (inbuf[j - 7] + inbuf[j - 23]) * 3.39723e-4f;
	t += (inbuf[j - 8] + inbuf[j - 22]) * -.0260797087f;
	t += (inbuf[j - 9] + inbuf[j - 21]) * -.0455563702f;
	t += (inbuf[j - 10] + inbuf[j - 20]) * -.040306855f;
	t += (inbuf[j - 11] + inbuf[j - 19]) * 5.029835e-4f;
	t += (inbuf[j - 12] + inbuf[j - 18]) * .0729262903f;
	t += (inbuf[j - 13] + inbuf[j - 17]) * .1572008878f;
	t += (inbuf[j - 14] + inbuf[j - 16]) * .2247288674f;
	t += inbuf[j - 15] * .250535965f;
	lpbuf[j] = t;
    }
    return 0;
} /* lpfilt_ */

