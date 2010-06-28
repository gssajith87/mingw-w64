/* grab defines of __FLT_ABI */
#if defined(_NEW_COMPLEX_FLOAT)
# define __FLT_ABI(N)	N##f
#elif defined(_NEW_COMPLEX_DOUBLE)
# define __FLT_ABI(N)	N
#elif defined(_NEW_COMPLEX_LDOUBLE)
# define __FLT_ABI(N)	N##l
#else
# error "Unknown complex number type"
#endif

#define _abifunc(first, second) __FLT_ABI(first##second)
#define _funcname(f)            _abifunc(test_function_, f)

extern int _funcname(TESTFUNC)();

int main()
{
  return _funcname(TESTFUNC)();
}
