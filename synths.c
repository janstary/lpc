#include "lpc.h"

/* Common Block Declarations */

extern struct {
    int32_t order, lframe;
    int32_t corrp;
} contrl_;

#define contrl_1 contrl_

/* Table of constant values */

static float c_b2 = .7f;

/* The note below is from the distributed version of the LPC10 coder. */
/* The version of the code below has been modified so that SYNTHS always */
/* has a constant frame length output of MAXFRM. */

/* Also, BSYNZ and DEEMP need not be modified to work on variable */
/* positions within an array.  It is only necessary to pass the first */
/* index desired as the array argument.  What actually gets passed is the */
/* address of that array position, which the subroutine treats as the */
/* first index of the array. */

/* This technique is used in subroutine ANALYS when calling PREEMP, so it */
/* appears that multiple people wrote different parts of this LPC10 code, */
/* and that they didn't necessarily have equivalent knowledge of Fortran */
/* (not surprising). */

/*  NOTE: There is excessive buffering here, BSYNZ and DEEMP should be */
/*        changed to operate on variable positions within SOUT.  Also, */
/*        the output length parameter is bogus, and PITSYN should be */
/*        rewritten to allow a constant frame length output. */

/* Input: */
/*  VOICE  - Half frame voicing decisions */
/*           Indices 1 through 2 read. */
/* Input/Output: */
/*  PITCH  - Pitch */
/*           PITCH is restricted to range 20 to 156, inclusive, */
/*           before calling subroutine PITSYN, and then PITSYN */
/*           can modify it further under some conditions. */
/*  RMS    - Energy */
/*           Only use is for debugging, and passed to PITSYN. */
/*           See comments there for how it can be modified. */
/*  RC     - Reflection coefficients */
/*           Indices 1 through ORDER restricted to range -.99 to .99, */
/*           before calling subroutine PITSYN, and then PITSYN */
/*           can modify it further under some conditions. */
/* Output: */
/*  SPEECH - Synthesized speech samples. */
/*           Indices 1 through the final value of K are written. */
/*  K      - Number of samples placed into array SPEECH. */
/*           This is always MAXFRM. */

/* Subroutine */ int synths_(int32_t *voice, int32_t *pitch, float *
	rms, float *rc, float *speech, int32_t *k, struct lpc10_decoder_state *st)
{
    /* Initialized data */

    float *buf;
    int32_t *buflen;

    /* System generated locals */
    int32_t i__1;
    float r__1, r__2;

    /* Local variables */
    float rmsi[16];
    int32_t nout, ivuv[16], i__, j;
    extern /* Subroutine */ int deemp_(float *, int32_t *, struct lpc10_decoder_state *);
    float ratio;
    int32_t ipiti[16];
    extern int bsynz_(float *, int32_t *, 
	    int32_t *, float *, float *, float *, float *, struct lpc10_decoder_state *), irc2pc_(float *, float *
	    , int32_t *, float *, float *);
    float g2pass;
    float pc[10];
    extern /* Subroutine */ int pitsyn_(int32_t *, int32_t *, int32_t *, float 
	    *, float *, int32_t *, int32_t *, int32_t *, float *, float *, 
	    int32_t *, float *, struct lpc10_decoder_state *);
    float rci[160]	/* was [10][16] */;

/*   LPC Configuration parameters: */
/* Frame size, Prediction order, Pitch period */
/*       Arguments */

/*   LPC Processing control variables: */

/* *** Read-only: initialized in setup */

/*  Files for Speech, Parameter, and Bitstream Input & Output, */
/*    and message and debug outputs. */

/* Here are the only files which use these variables: */

/* lpcsim.f setup.f trans.f error.f vqsetup.f */

/* Many files which use fdebug are not listed, since it is only used in */
/* those other files conditionally, to print trace statements. */
/* 	int32_t fsi, fso, fpi, fpo, fbi, fbo, pbin, fmsg, fdebug */
/*  LPC order, Frame size, Quantization rate, Bits per frame, */
/*    Error correction */
/* Subroutine SETUP is the only place where order is assigned a value, */
/* and that value is 10.  It could increase efficiency 1% or so to */
/* declare order as a constant (i.e., a Fortran PARAMETER) instead of as 
*/
/* a variable in a COMMON block, since it is used in many places in the */
/* core of the coding and decoding routines.  Actually, I take that back. 
*/
/* At least when compiling with f2c, the upper bound of DO loops is */
/* stored in a local variable before the DO loop begins, and then that is 
*/
/* compared against on each iteration. */
/* Similarly for lframe, which is given a value of MAXFRM in SETUP. */
/* Similarly for quant, which is given a value of 2400 in SETUP.  quant */
/* is used in only a few places, and never in the core coding and */
/* decoding routines, so it could be eliminated entirely. */
/* nbits is similar to quant, and is given a value of 54 in SETUP. */
/* corrp is given a value of .TRUE. in SETUP, and is only used in the */
/* subroutines ENCODE and DECODE.  It doesn't affect the speed of the */
/* coder significantly whether it is .TRUE. or .FALSE., or whether it is 
*/
/* a constant or a variable, since it is only examined once per frame. */
/* Leaving it as a variable that is set to .TRUE.  seems like a good */
/* idea, since it does enable some error-correction capability for */
/* unvoiced frames, with no change in the coding rate, and no noticeable 
*/
/* quality difference in the decoded speech. */
/* 	int32_t quant, nbits */
/* *** Read/write: variables for debugging, not needed for LPC algorithm 
*/

/*  Current frame, Unstable frames, Output clip count, Max onset buffer, 
*/
/*    Debug listing detail level, Line count on listing page */

/* nframe is not needed for an embedded LPC10 at all. */
/* nunsfm is initialized to 0 in SETUP, and incremented in subroutine */
/* ERROR, which is only called from RCCHK.  When LPC10 is embedded into */
/* an application, I would recommend removing the call to ERROR in RCCHK, 
*/
/* and remove ERROR and nunsfm completely. */
/* iclip is initialized to 0 in SETUP, and incremented in entry SWRITE in 
*/
/* sread.f.  When LPC10 is embedded into an application, one might want */
/* to cause it to be incremented in a routine that takes the output of */
/* SYNTHS and sends it to an audio device.  It could be optionally */
/* displayed, for those that might want to know what it is. */
/* maxosp is never initialized to 0 in SETUP, although it probably should 
*/
/* be, and it is updated in subroutine ANALYS.  I doubt that its value */
/* would be of much interest to an application in which LPC10 is */
/* embedded. */
/* listl and lincnt are not needed for an embedded LPC10 at all. */
/* 	int32_t nframe, nunsfm, iclip, maxosp, listl, lincnt */
/* 	common /contrl/ fsi, fso, fpi, fpo, fbi, fbo, pbin, fmsg, fdebug */
/* 	common /contrl/ quant, nbits */
/* 	common /contrl/ nframe, nunsfm, iclip, maxosp, listl, lincnt */
/*       Parameters/constants */
/*       Local variables that need not be saved */
/*       Local state */
/*       BUF is a buffer of speech samples that would have been returned 
*/
/*       by the older version of SYNTHS, but the newer version doesn't, */
/*       so that the newer version can always return MAXFRM samples on */
/*       every call.  This has the effect of delaying the return of */
/*       samples for one additional frame time. */

/*       Indices 1 through BUFLEN contain samples that are left over from 
*/
/*       the last call to SYNTHS.  Given the way that PITSYN works, */
/*       BUFLEN should always be in the range MAXFRM-MAXPIT+1 through */
/*       MAXFRM, inclusive, after a call to SYNTHS is complete. */

/*       On the first call to SYNTHS (or the first call after */
/*       reinitializing with the entry INITSYNTHS), BUFLEN is MAXFRM, and 
*/
/*       a frame of silence is always returned. */
    /* Parameter adjustments */
    if (voice) {
	--voice;
	}
    if (rc) {
	--rc;
	}
    if (speech) {
	--speech;
	}

    /* Function Body */
    buf = &(st->buf[0]);
    buflen = &(st->buflen);

/* Computing MAX */
    i__1 = min(*pitch,156);
    *pitch = max(i__1,20);
    i__1 = contrl_1.order;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
/* Computing MIN */
	r__2 = rc[i__];
	r__1 = min(r__2,.99f);
	rc[i__] = max(r__1,-.99f);
    }
    pitsyn_(&contrl_1.order, &voice[1], pitch, rms, &rc[1], &contrl_1.lframe, 
	    ivuv, ipiti, rmsi, rci, &nout, &ratio, st);
    if (nout > 0) {
	i__1 = nout;
	for (j = 1; j <= i__1; ++j) {

/*             Add synthesized speech for pitch period J to the en
d of */
/*             BUF. */

	    irc2pc_(&rci[j * 10 - 10], pc, &contrl_1.order, &c_b2, &g2pass);
	    bsynz_(pc, &ipiti[j - 1], &ivuv[j - 1], &buf[*buflen], &rmsi[j - 1]
		    , &ratio, &g2pass, st);
	    deemp_(&buf[*buflen], &ipiti[j - 1], st);
	    *buflen += ipiti[j - 1];
	}

/*          Copy first MAXFRM samples from BUF to output array SPEECH 
*/
/*          (scaling them), and then remove them from the beginning of
 */
/*          BUF. */

	for (i__ = 1; i__ <= 180; ++i__) {
	    speech[i__] = buf[i__ - 1] / 4096.f;
	}
	*k = 180;
	*buflen += -180;
	i__1 = *buflen;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    buf[i__ - 1] = buf[i__ + 179];
	}
    }
    return 0;
} /* synths_ */
