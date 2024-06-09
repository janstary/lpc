#include <math.h>
#include "lpc.h"

int32_t pow_ii(int32_t *ap, int32_t *bp)
{
	int32_t pow, x, n;
	unsigned long u;

	x = *ap;
	n = *bp;

	if (n <= 0) {
		if (n == 0 || x == 1)
			return 1;
		if (x != -1)
			return x == 0 ? 1/x : 0;
		n = -n;
		}
	u = n;
	for(pow = 1; ; )
		{
		if(u & 01)
			pow *= x;
		if(u >>= 1)
			x *= x;
		else
			break;
		}
	return(pow);
	}



double
r_sign(float *a, float *b)
{
	double x;
	x = (*a >= 0 ? *a : - *a);
	return ( *b >= 0 ? x : -x);
}

int32_t
i_nint(float *x)
{
	return (*x) >= 0 ? floor(*x + .5) : -floor(.5 - *x);
}
