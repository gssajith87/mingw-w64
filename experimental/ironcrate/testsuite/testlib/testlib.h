#ifndef IC_TESTLIB_HXX
#define IC_TESTLIB_HXX

#define IC_TEST_NO_INVALID_PARA_HANDLER 1

extern int ic_test_main (int seq, int flags);
extern void *ic_test_getsymbol (const char *name);

extern int ic_test_invalid_parameter_called;
extern int ic_test_segfault;
extern const char *ic_test_msvcrt_name;

#endif

