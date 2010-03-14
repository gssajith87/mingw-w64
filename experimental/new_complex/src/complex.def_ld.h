#ifdef __FCT_TYPE
#undef __FCT_TYPE
#endif
#ifdef __FCT_ABIEXT
#undef __FCT_ABIEXT
#endif
#ifdef __FCT_CSTEXT
#undef __FCT_CSTEXT
#endif
#ifdef __FCT_NAN
#undef __FCT_NAN
#endif

#define __FCT_TYPE long double
#define	__FCT_ABIEXT(N) N##l
#define __FCT_CSTEXT(N) N##L

#define __FCT_NAN NANL

#ifdef __FCT_M_PI
#undef __FCT_M_PI
#endif
#define __FCT_M_PI M_PIl

#ifdef __FCT_M_PI_2
#undef __FCT_M_PI_2
#endif
#define __FCT_M_PI_2 M_PI_2l

#ifdef __FCT_M_PI_4
#undef __FCT_M_PI_4
#endif
#define __FCT_M_PI_4 M_PI_4l

#ifdef __FCT_M_PI_3_4
#undef __FCT_M_PI_3_4
#endif
#define __FCT_M_PI_3_4 M_PI_3_4l

#ifdef __FCT_HUGE_VAL
#undef __FCT_HUGE_VAL
#endif
#define __FCT_HUGE_VAL HUGE_VALL
