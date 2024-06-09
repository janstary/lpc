#include "lpc.h"

/* Table of constant values */

static int32_t c__1 = 1;

/*    Pre-process input speech: */

/* Inputs: */
/*  LENGTH - Number of SPEECH samples */
/* Input/Output: */
/*  SPEECH(LENGTH) - Speech data. */
/*                   Indices 1 through LENGTH are read and modified. */

/* This subroutine has no local state maintained from one call to the */
/* next, but HP100 does.  If you want to switch to using a new audio */
/* stream for this filter, or reinitialize its state for any other */
/* reason, call the ENTRY INITPREPRO. */

/* Subroutine */ int prepro_(float *speech, int32_t *length,
			     struct lpc10_encoder_state *st)
{
    extern /* Subroutine */ int hp100_(float *, int32_t *, int32_t *, struct lpc10_encoder_state *);

/*       Arguments */
/*   High Pass Filter at 100 Hz */
    /* Parameter adjustments */
    if (speech) {
	--speech;
	}

    /* Function Body */
    hp100_(&speech[1], &c__1, length, st);
    return 0;
} /* prepro_ */
