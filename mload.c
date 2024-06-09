#include "lpc.h"

/* Load a covariance matrix. */

/* Input: */
/*  ORDER            - Analysis order */
/*  AWINS            - Analysis window start */
/*  AWINF            - Analysis window finish */
/*  SPEECH(AWINF)    - Speech buffer */
/*                     Indices MIN(AWINS, AWINF-(ORDER-1)) through */
/*                             MAX(AWINF, AWINS+(ORDER-1)) read. */
/*                     As long as (AWINF-AWINS) .GE. (ORDER-1), */
/*                     this is just indices AWINS through AWINF. */
/* Output: */
/*  PHI(ORDER,ORDER) - Covariance matrix */
/*                    Lower triangular half and diagonal written, and read.*/
/*                     Upper triangular half untouched. */
/*  PSI(ORDER)       - Prediction vector */
/*                     Indices 1 through ORDER written, */
/*                     and most are read after that. */

/* This subroutine has no local state. */

/* Subroutine */ int mload_(int32_t *order, int32_t *awins, int32_t *awinf, 
	float *speech, float *phi, float *psi)
{
    /* System generated locals */
    int32_t phi_dim1, phi_offset, i__1, i__2;

    /* Local variables */
    int32_t c__, i__, r__, start;

/*       Arguments */
/*       Local variables that need not be saved */
/*   Load first column of triangular covariance matrix PHI */
    /* Parameter adjustments */
    --psi;
    phi_dim1 = *order;
    phi_offset = phi_dim1 + 1;
    phi -= phi_offset;
    --speech;

    /* Function Body */
    start = *awins + *order;
    i__1 = *order;
    for (r__ = 1; r__ <= i__1; ++r__) {
	phi[r__ + phi_dim1] = 0.f;
	i__2 = *awinf;
	for (i__ = start; i__ <= i__2; ++i__) {
	    phi[r__ + phi_dim1] += speech[i__ - 1] * speech[i__ - r__];
	}
    }
/*   Load last element of vector PSI */
    psi[*order] = 0.f;
    i__1 = *awinf;
    for (i__ = start; i__ <= i__1; ++i__) {
	psi[*order] += speech[i__] * speech[i__ - *order];
    }
/*   End correct to get additional columns of PHI */
    i__1 = *order;
    for (r__ = 2; r__ <= i__1; ++r__) {
	i__2 = r__;
	for (c__ = 2; c__ <= i__2; ++c__) {
	    phi[r__ + c__ * phi_dim1] = phi[r__ - 1 + (c__ - 1) * phi_dim1] - 
		    speech[*awinf + 1 - r__] * speech[*awinf + 1 - c__] + 
		    speech[start - r__] * speech[start - c__];
	}
    }
/*   End correct to get additional elements of PSI */
    i__1 = *order - 1;
    for (c__ = 1; c__ <= i__1; ++c__) {
	psi[c__] = phi[c__ + 1 + phi_dim1] - speech[start - 1] * speech[start 
		- 1 - c__] + speech[*awinf] * speech[*awinf - c__];
    }
/*   Copy lower triangular section into upper (why bother?) */
/*       I'm commenting this out, since the upper triangular half of PHI 
*/
/*       is never used by later code, unless a sufficiently high level of 
*/
/*       tracing is turned on. */
/* 	DO R = 1,ORDER */
/* 	   DO C = 1,R-1 */
/* 	      PHI(C,R) = PHI(R,C) */
/* 	   END DO */
/* 	END DO */
    return 0;
} /* mload_ */

