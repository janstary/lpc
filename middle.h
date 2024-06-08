#define middle(x,y,z) ((x) < (y))			\
	? ((y) < (z) ? (y) : ((x) < (z) ? (z) : (x)))	\
	: ((x) < (z) ? (x) : ((y) < (z) ? (z) : (y)))
