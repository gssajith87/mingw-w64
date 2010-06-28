
AM_CPPFLAGS = -I $(srcdir)/src

# set for later use by +=
LDADD =
lib_LIBRARIES =
check_LIBRARIES =
check_PROGRAMS = 
TESTS =
# Fake out the testsuite
CPPFLAGS32 = -m32
CPPFLAGS64 = -m64
LDFLAGS32 = -m32
LDFLAGS64 = -m64

src_newcomplex =  \
src/cabs.c   src/cargf.c  src/ccosl.c  src/cimag.c   src/clogf.c  src/conjl.c  src/cproj.c   src/crealf.c  src/csinl.c   src/ctan.c  \
src/cabsf.c  src/cargl.c  src/cexp.c   src/cimagf.c  src/clogl.c  src/cpow.c   src/cprojf.c  src/creall.c  src/csqrt.c   src/ctanf.c \
src/cabsl.c  src/ccos.c   src/cexpf.c  src/cimagl.c  src/conj.c   src/cpowf.c  src/cprojl.c  src/csin.c    src/csqrtf.c  src/ctanl.c \
src/carg.c   src/ccosf.c  src/cexpl.c  src/clog.c    src/conjf.c  src/cpowl.c  src/creal.c   src/csinf.c   src/csqrtl.c \
src/cacos.c  src/cacosf.c src/cacosl.c src/casin.c   src/casinf.c src/casinl.c src/catan.c   src/catanf.c  src/catanl.c \
\
src/cabs.def.h    src/casin.def.h   src/ccos.def.h   src/clog.def.h          src/cproj.def.h  src/csqrt.def.h \
src/cacos.def.h   src/casinh.def.h  src/ccosh.def.h  src/complex_internal.h  src/creal.def.h  src/ctan.def.h  \
src/cacosh.def.h  src/catan.def.h   src/cexp.def.h   src/conj.def.h          src/csin.def.h   src/ctanh.def.h \
src/carg.def.h    src/catanh.def.h  src/cimag.def.h  src/cpow.def.h          src/csinh.def.h

# it is ok to add the lib64/libnewcomplex.a and lib32/libnewcomplex.a on the same command line.
# The linker will choose the correct one while linking.
if LIB64
LDADD += lib64/libnewcomplex.a
lib_LIBRARIES += lib64/libnewcomplex.a
lib64_libnewcomplex_a_SOURCES = $(src_newcomplex)
lib64_libnewcomplex_a_CPPFLAGS = $(CPPFLAGS64) $(AM_CPPFLAGS)
endif

if LIB32
LDADD += lib32/libnewcomplex.a
lib_LIBRARIES += lib32/libnewcomplex.a
lib32_libnewcomplex_a_SOURCES = $(src_newcomplex)
lib32_libnewcomplex_a_CPPFLAGS = $(CPPFLAGS32) $(AM_CPPFLAGS)
endif

include testcases/complex/complex_tests.am
