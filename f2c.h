#ifndef F2C_INCLUDE
#define F2C_INCLUDE

#include "lpc10.h"

#define TRUE_ (1)
#define FALSE_ (0)

/* I/O stuff */

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (double)abs(x)
#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) ((a) >= (b) ? (a) : (b))
#endif
#define dmin(a,b) (double)min(a,b)
#define dmax(a,b) (double)max(a,b)

#endif
