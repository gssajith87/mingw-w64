#include <math.h>
#include <complex.h>

/* Define some PI constants for long double, as they are not defined in math.h  */
#ifndef M_PI_4l
#define M_PI_4l 0.7853981633974483096156608458198757L
#define M_PI_2l 1.5707963267948966192313216916397514L
#define M_PIl   3.1415926535897932384626433832795029L
#endif

/* NAN builtins for gcc, as they are not part of math.h  */
#ifndef NANF
#define NANF __builtin_nanf ("")
#endif
#ifndef NANL
#define NANL __builtin_nanl ("")
#endif

/* Some more helpers.  */
#define M_PI_3_4  (M_PI - M_PI_4)
#define M_PI_3_4l (M_PIl - M_PI_4l)

#if defined(_NEWCOMPLEX_FLOAT)
# define __FLT_TYPE	float
# define __FLT_ABI(N)	N##f
# define __FLT_CST(N)	N##F
# define __FLT_NAN	NANF
# define __FLT_HUGE_VAL	HUGE_VALF
# define __FLT_PI	M_PI
# define __FLT_PI_2	M_PI_2
# define __FLT_PI_4	M_PI_4
# define __FLT_PI_3_4	M_PI_3_4
#elif defined(_NEWCOMPLEX_DOUBLE)
# define __FLT_TYPE	double
# define __FLT_ABI(N)	N
# define __FLT_CST(N)	N
# define __FLT_NAN	NAN
# define __FLT_HUGE_VAL	HUGE_VAL
# define __FLT_PI	M_PI
# define __FLT_PI_2	M_PI_2
# define __FLT_PI_4	M_PI_4
# define __FLT_PI_3_4	M_PI_3_4
#elif defined(_NEWCOMPLEX_LDOUBLE)
# define __FLT_TYPE	long double
# define __FLT_ABI(N)	N##l
# define __FLT_CST(N)	N##L
# define __FLT_NAN	NANL
# define __FLT_HUGE_VAL	HUGE_VALL
# define __FLT_PI	M_PIl
# define __FLT_PI_2	M_PI_2l
# define __FLT_PI_4	M_PI_4l
# define __FLT_PI_3_4	M_PI_3_4l
#else
# error "Unknown complex number type"
#endif
