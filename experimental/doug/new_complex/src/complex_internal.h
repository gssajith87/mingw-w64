#include <math.h>
#include <complex.h>

/* Define some PI constants for long double, as they are not defined in math.h  */
#ifndef M_PI_4l
#define M_PI_4l 0.7853981633974483096156608458198757L
#define M_PI_2l 1.5707963267948966192313216916397514L
#define M_PIl 3.1415926535897932384626433832795029L
#endif

/* NAN builtins for gcc, as they are not part of math.h  */
#ifndef NANF
#define NANF __builtin_nanf ("")
#endif
#ifndef NANL
#define NANL __builtin_nanl ("")
#endif

/* Some more helpers.  */
#define M_PI_3_4 (M_PI - M_PI_4)
#define M_PI_3_4l (M_PIl - M_PI_4l)

#if defined(_NEWCOMPLEX_FLOAT)
#include "complex.def_f.h"
#elif defined(_NEWCOMPLEX_DOUBLE)
#include "complex.def_d.h"
#elif defined(_NEWCOMPLEX_LDOUBLE)
#include "complex.def_ld.h"
#else
#error "Unknown complex number type"
#endif
