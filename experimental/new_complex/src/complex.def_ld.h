#ifdef __FLT_TYPE
#undef __FLT_TYPE
#undef __FLT_ABI
#undef __FLT_CST
#undef __FLT_NAN
#undef __FLT_PI
#undef __FLT_PI_2
#undef __FLT_PI_4
#undef __FLT_PI_3_4
#undef __FLT_HUGE_VAL
#endif

#define __FLT_TYPE long double
#define	__FLT_ABI(N) N##l
#define __FLT_CST(N) N##L

#define __FLT_NAN NANL
#define __FLT_HUGE_VAL HUGE_VALL

#define __FLT_PI M_PIl
#define __FLT_PI_2 M_PI_2l
#define __FLT_PI_4 M_PI_4l
#define __FLT_PI_3_4 M_PI_3_4l
