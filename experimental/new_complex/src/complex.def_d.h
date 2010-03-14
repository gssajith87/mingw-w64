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

#define __FLT_TYPE double
#define	__FLT_ABI(N) N
#define __FLT_CST(N) N

#define __FLT_NAN NAN
#define __FLT_HUGE_VAL HUGE_VAL

#define __FLT_PI M_PI
#define __FLT_PI_2 M_PI_2
#define __FLT_PI_4 M_PI_4
#define __FLT_PI_3_4 M_PI_3_4
