AM_CPPFLAGS = -I $(srcdir)/src
LDADD = libnewcomplex.a

src_newcomplex =  \
src/cabs.c   src/cargf.c  src/ccosl.c  src/cimag.c   src/clogf.c  src/conjl.c  src/cproj.c   src/crealf.c  src/csinl.c   src/ctan.c  \
src/cabsf.c  src/cargl.c  src/cexp.c   src/cimagf.c  src/clogl.c  src/cpow.c   src/cprojf.c  src/creall.c  src/csqrt.c   src/ctanf.c \
src/cabsl.c  src/ccos.c   src/cexpf.c  src/cimagl.c  src/conj.c   src/cpowf.c  src/cprojl.c  src/csin.c    src/csqrtf.c  src/ctanl.c \
src/carg.c   src/ccosf.c  src/cexpl.c  src/clog.c    src/conjf.c  src/cpowl.c  src/creal.c   src/csinf.c   src/csqrtl.c \
\
src/cabs.def.h    src/casin.def.h   src/ccos.def.h   src/clog.def.h          src/cproj.def.h  src/csqrt.def.h \
src/cacos.def.h   src/casinh.def.h  src/ccosh.def.h  src/complex_internal.h  src/creal.def.h  src/ctan.def.h  \
src/cacosh.def.h  src/catan.def.h   src/cexp.def.h   src/conj.def.h          src/csin.def.h   src/ctanh.def.h \
src/carg.def.h    src/catanh.def.h  src/cimag.def.h  src/cpow.def.h          src/csinh.def.h

lib_LIBRARIES = libnewcomplex.a

libnewcomplex_a_SOURCES = $(src_newcomplex)

newcomplex_tests = \
  tests/cabs \
  tests/cabsf \
  tests/cabsl \
  tests/cacos \
  tests/cacosf \
  tests/cacosh \
  tests/cacoshf \
  tests/cacoshl \
  tests/cacosl \
  tests/carg \
  tests/cargf \
  tests/cargl \
  tests/casin \
  tests/casinf \
  tests/casinh \
  tests/casinhf \
  tests/casinhl \
  tests/casinl \
  tests/catan \
  tests/catanf \
  tests/catanh \
  tests/catanhf \
  tests/catanhl \
  tests/catanl \
  tests/ccos \
  tests/ccosf \
  tests/ccosh \
  tests/ccoshf \
  tests/ccoshl \
  tests/ccosl \
  tests/cexp \
  tests/cexpf \
  tests/cexpl \
  tests/cimag \
  tests/cimagf \
  tests/cimagl \
  tests/clog \
  tests/clogf \
  tests/clogl \
  tests/conj \
  tests/conjf \
  tests/conjl \
  tests/cpow \
  tests/cpowf \
  tests/cpowl \
  tests/cproj \
  tests/cprojf \
  tests/cprojl \
  tests/creal \
  tests/crealf \
  tests/creall \
  tests/csin \
  tests/csinf \
  tests/csinh \
  tests/csinhf \
  tests/csinhl \
  tests/csinl \
  tests/csqrt \
  tests/csqrtf \
  tests/csqrtl \
  tests/ctan \
  tests/ctanf \
  tests/ctanh \
  tests/ctanhf \
  tests/ctanhl \
  tests/ctanl 

TESTS = $(check_PROGRAMS)
check_PROGRAMS = $(newcomplex_tests)
