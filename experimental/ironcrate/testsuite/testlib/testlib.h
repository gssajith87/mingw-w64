#ifndef IC_TESTLIB_HXX
#define IC_TESTLIB_HXX

#define IC_TEST_NO_INVALID_PARA_HANDLER 1

extern int ic_test_main (int seq, int flags);
extern void *ic_test_getsymbol (const char *name);

extern int ic_test_invalid_parameter_called;
extern int ic_test_segfault;
extern const char *ic_test_msvcrt_name;
extern const char *ic_test_testname;

extern void ic_test_reset_internal_vars (void);

#define IC_TEST_RSLT_OK 3
#define IC_TEST_RSLT_SUCCESS 0
#define IC_TEST_RSLT_FAILED  1
#define IC_TEST_RSLT_UNSUPPORTED 2

#endif

