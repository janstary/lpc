#include "lpc.h"

/*  Pseudo random number generator based on Knuth, Vol 2, p. 27. */

/* Function Return: */
/*  RANDOM - Integer variable, uniformly distributed over -32768 to 32767 */

/* This subroutine maintains local state from one call to the next. */
/* In the context of the LPC10 coder, there is no reason to reinitialize */
/* this local state when switching between audio streams, because its */
/* results are only used to generate noise for unvoiced frames. */

int32_t random_(struct lpc10_decoder_state *st)
{
    /* Initialized data */

    int32_t *j;
    int32_t *k;
    int16_t *y;

    /* System generated locals */
    int32_t ret_val;

/* 	Parameters/constants */
/*       Local state */
/*   The following is a 16 bit 2's complement addition, */
/*   with overflow checking disabled */

    j = &(st->j);
    k = &(st->k);
    y = &(st->y[0]);

    y[*k - 1] += y[*j - 1];
    ret_val = y[*k - 1];
    --(*k);
    if (*k <= 0) {
	*k = 5;
    }
    --(*j);
    if (*j <= 0) {
	*j = 5;
    }
    return ret_val;
} /* random_ */

