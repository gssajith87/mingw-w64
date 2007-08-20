# INCLUDES = -I$(top_srcdir) -I$(includedir)
# Done: lib_LIBRARIES = libm.a libmingw32.a libmoldname.a libmingwex.a libcrtdll.a libmsvcrt.a libmsvcr80.a
# TODO: Turn _libm_dummy.c into a BUILT_SOURCES thing

#Use AM_MAINTAINER_MODE in configure.ac to disable autoreconf

if WITHSYSROOT
  sysincludes = -I@TARGET_SYSTEM_ROOT@/mingw/include
else
  sysincludes =
endif

AM_CPPFLAGS = $(sysincludes) -D_CRTBLD -D_SYSCRT=1 -DCRTDLL=1 -DWINHEAP=1
crtdir=$(libdir)
# These targets require special handling that automake can't
# yet support (or that I don't know how to do properly)
crt_SCRIPTS = crt1.o
BUILT_SOURCES = libcrtdll.a libmsvcrt.a libmsvcr80.a crt2.o dllcrt1.o dllcrt2.o
libcrtdll.a libmsvcrt.a libmsvcr80.a:
	base=`echo $@ | sed -e 's/\.a//' -e 's/^lib//'`; \
	$(DLLTOOL) --as=$(AS) -k --dllname $${base}.dll --output-lib $@ --def $(top_srcdir)/$${base}.def
#libcrtdll.a:
#	$(DLLTOOL) --as=$(AS) -k --dllname crtdll.dll --output-lib $@ --def $(top_srcdir)/crtdll.def
#libmsvcrt.a:
#	$(DLLTOOL) --as=$(AS) -k --dllname msvcrt.dll --output-lib $@ --def $(top_srcdir)/msvcrt.def
#libmsvcr80.a:
#	$(DLLTOOL) --as=$(AS) -k --dllname msvcr80.dll --output-lib $@ --def $(top_srcdir)/msvcr80.def
crt1.o:
#	$(COMPILE) -D__CRTDLL__ -U__MSVCRT__ -c $(top_srcdir)/crtexe.c -o $@
	echo $(libexecdir)
	echo $(libdir)
	echo $(crtdir)
crt2.o:
	$(COMPILE) -D__MSVCRT__ -U__CRTDLL__ -c $(top_srcdir)/crtexe.c -o $@
dllcrt1.o:
	$(COMPILE) -D__CRTDLL__ -U__MSVCRT__ -c $(top_srcdir)/crtdll.c -o $@
dllcrt2.o:
	$(COMPILE) -D__MSVCRT__ -U__CRTDLL__ -c $(top_srcdir)/crtdll.c -o $@


noinst_PROGRAMS = dummy
dummy_SOURCES = \
  CRT_fp8.c CRT_fp10.c txtmode.c binmode.c crtbegin.c crtend.c 
dummy_LINK = \
  @echo \!* > /dev/null

lib_LIBRARIES = libm.a libmingw32.a libmoldname.a libmingwex.a


libm_a_SOURCES = _libm_dummy.c

libmingw32_a_SOURCES = \
  crt0_c.c crt0_w.c dll_argv.c gccmain.c CRT_fp10.c pseudo-reloc.c pseudo-reloc-list.c pesect.c cinitexe.c \
  natstart.c gs_support.c atonexit.c dllmain.c wildcard.c merr.c dllargv.c charmax.c xtxtmode.c tlssup.c   \
  xncommod.c _newmode.c xthdloc.c mingw_helpers.c dllentry.c

libmoldname_a_SOURCES = \
  isascii.c iscsym.c iscsymf.c toascii.c strcasecmp.c strncasecmp.c wcscmpi.c
libmoldname_a_AR = \
  $(DLLTOOL) --as $(AS) -k -U --dllname msvcrt.dll --def $(top_srcdir)/moldname-msvcrt.def --output-lib $@ ; \
  $(AR) $(ARFLAGS)
  

libmingwex_a_SOURCES = \
  complex/cabs.c       complex/cabsf.c      complex/cabsl.c      complex/cacos.c      complex/cacosf.c     \
  complex/cacosh.c     complex/cacoshf.c    complex/cacoshl.c    complex/cacosl.c     complex/carg.c       \
  complex/cargf.c      complex/cargl.c      complex/casin.c      complex/casinf.c     complex/casinh.c     \
  complex/casinhf.c    complex/casinhl.c    complex/casinl.c     complex/catan.c      complex/catanf.c     \
  complex/catanh.c     complex/catanhf.c    complex/catanhl.c    complex/catanl.c     complex/ccos.c       \
  complex/ccosf.c      complex/ccosh.c      complex/ccoshf.c     complex/ccoshl.c     complex/ccosl.c      \
  complex/cexp.c       complex/cexpf.c      complex/cexpl.c      complex/cimag.c      complex/cimagf.c     \
  complex/cimagl.c     complex/clog.c       complex/clogf.c      complex/clogl.c      complex/cpow.c       \
  complex/cpowf.c      complex/cpowl.c      complex/cproj.c      complex/cprojf.c     complex/cprojl.c     \
  complex/creal.c      complex/crealf.c     complex/creall.c     complex/csin.c       complex/csinf.c      \
  complex/csinh.c      complex/csinhf.c     complex/csinhl.c     complex/csinl.c      complex/csqrt.c      \
  complex/csqrtf.c     complex/csqrtl.c     complex/ctan.c       complex/ctanf.c      complex/ctanh.c      \
  complex/ctanhf.c     complex/ctanhl.c     complex/ctanl.c      dirent.c             ftruncate.c          \
  getopt.c             math/acosf.c         math/acosh.c         math/acoshf.c        math/acoshl.c        \
  math/acosl.c         math/asinf.c         math/asinh.c         math/asinhf.c        math/asinhl.c        \
  math/asinl.c         math/atan2f.c        math/atan2l.c        math/atanf.c         math/atanh.c         \
  math/atanhf.c        math/atanhl.c        math/atanl.c         math/cbrt.c          math/cbrtf.c         \
  math/cbrtl.c         math/ceilf.S         math/ceill.S         math/cephes_emath.c  math/copysign.S      \
  math/copysignf.S     math/copysignl.S     math/cosf.S          math/coshf.c         math/coshl.c         \
  math/cosl.S          math/erfl.c          math/exp2.S          math/exp2f.S         math/exp2l.S         \
  math/expf.c          math/expl.c          math/expm1.c         math/expm1f.c        math/expm1l.c        \
  math/fabs.c          math/fabsf.c         math/fabsl.c         math/fdim.c          math/fdimf.c         \
  math/fdiml.c         math/floorf.S        math/floorl.S        math/fma.S           math/fmaf.S          \
  math/fmal.c          math/fmax.c          math/fmaxf.c         math/fmaxl.c         math/fmin.c          \
  math/fminf.c         math/fminl.c         math/fmodf.c         math/fmodl.c         math/fp_consts.c     \
  math/fp_constsf.c    math/fp_constsl.c    math/fpclassify.c    math/fpclassifyf.c   math/fpclassifyl.c   \
  math/frexpf.c        math/frexpl.S        math/fucom.c         math/hypotf.c        math/hypotl.c        \
  math/ilogb.S         math/ilogbf.S        math/ilogbl.S        math/isnan.c         math/isnanf.c        \
  math/isnanl.c        math/ldexpf.c        math/ldexpl.c        math/lgamma.c        math/lgammaf.c       \
  math/lgammal.c       math/llrint.c        math/llrintf.c       math/llrintl.c       math/llround.c       \
  math/llroundf.c      math/llroundl.c      math/log10f.S        math/log10l.S        math/log1p.S         \
  math/log1pf.S        math/log1pl.S        math/log2.S          math/log2f.S         math/log2l.S         \
  math/logb.c          math/logbf.c         math/logbl.c         math/logf.S          math/logl.S          \
  math/lrint.c         math/lrintf.c        math/lrintl.c        math/lround.c        math/lroundf.c       \
  math/lroundl.c       math/modff.c         math/modfl.c         math/nearbyint.S     math/nearbyintf.S    \
  math/nearbyintl.S    math/nextafterf.c    math/nextafterl.c    math/nexttoward.c    math/nexttowardf.c   \
  math/powf.c          math/powi.c          math/powif.c         math/powil.c         math/powl.c          \
  math/remainder.S     math/remainderf.S    math/remainderl.S    math/remquo.S        math/remquof.S       \
  math/remquol.S       math/rint.c          math/rintf.c         math/rintl.c         math/round.c         \
  math/roundf.c        math/roundl.c        math/s_erf.c         math/scalbn.S        math/scalbnf.S       \
  math/scalbnl.S       math/sf_erf.c        math/signbit.c       math/signbitf.c      math/signbitl.c      \
  math/sinf.S          math/sinhf.c         math/sinhl.c         math/sinl.S          math/sqrtf.c         \
  math/sqrtl.c         math/tanf.S          math/tanhf.c         math/tanhl.c         math/tanl.S          \
  math/tgamma.c        math/tgammaf.c       math/tgammal.c       math/trunc.c         math/truncf.c        \
  math/truncl.c        misc/alarm.c         misc/btowc.c         misc/feclearexcept.c misc/fegetenv.c      \
  misc/fegetexceptflag.c misc/fegetround.c    misc/feholdexcept.c  misc/feraiseexcept.c misc/fesetenv.c    \
  misc/fesetexceptflag.c misc/fesetround.c    misc/fetestexcept.c  misc/feupdateenv.c   misc/fwide.c       \
  misc/getlogin.c      misc/gettimeofday.c  misc/imaxabs.c       misc/imaxdiv.c       misc/mbrtowc.c       \
  misc/mbsinit.c       misc/mingw-aligned-malloc.c misc/mingw-fseek.c   misc/seterrno.c      misc/sleep.c  \
  misc/strtoimax.c     misc/strtold.c       misc/strtoumax.c     misc/wassert.c       misc/wcrtomb.c       \
  misc/wcstoimax.c     misc/wcstold.c       misc/wcstoumax.c     misc/wctob.c         misc/wctrans.c       \
  misc/wctype.c        misc/wmemchr.c       misc/wmemcmp.c       misc/wmemcpy.c       misc/wmemmove.c      \
  misc/wmemset.c       stdio/_Exit.c        stdio/atoll.c        stdio/fopen64.c      stdio/fseeko64.c     \
  stdio/ftello64.c     stdio/lltoa.c        stdio/lltow.c        stdio/lseek64.c      stdio/snprintf.c     \
  stdio/snwprintf.c    stdio/strtof.c       stdio/ulltoa.c       stdio/ulltow.c       stdio/vfscanf.c      \
  stdio/vfwscanf.c     stdio/vscanf.c       stdio/vsnprintf.c    stdio/vsnwprintf.c   stdio/vsscanf.c      \
  stdio/vswscanf.c     stdio/vwscanf.c      stdio/wcstof.c       stdio/wtoll.c        wdirent.c


include Makefile.mklibs.am

CLEANFILES = $(BUILT_SOURCES)
EXTRA_DIST = crtdll.def msvcrt.def msvcr80.def crtexe.c crtdll.c lib
noinst_HEADERS = \
  misc/mb_wc_common.h internal.h oscalls.h sect_attribs.h math/fp_consts.h \
  math/cephes_mconf.h math/fastmath.h math/cephes_emath.h

