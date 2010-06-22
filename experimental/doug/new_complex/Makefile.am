AM_CPPFLAGS = -I $(srcdir)/src

newcomplex_src =  \
src/cabs.c        src/catanh.def.h  src/clog.def.h          src/creal.def.h \
src/cabs.def.h    src/ccos.c        src/complex_internal.h  src/csin.c      \
src/cacos.def.h   src/ccos.def.h    src/conj.c              src/csin.def.h  \
src/cacosh.def.h  src/ccosh.def.h   src/conj.def.h          src/csinh.def.h \
src/carg.c        src/cexp.c        src/cpow.c              src/csqrt.c     \
src/carg.def.h    src/cexp.def.h    src/cpow.def.h          src/csqrt.def.h \
src/casin.def.h   src/cimag.c       src/cproj.c             src/ctan.c      \
src/casinh.def.h  src/cimag.def.h   src/cproj.def.h         src/ctan.def.h  \
src/catan.def.h   src/clog.c        src/creal.c             src/ctanh.def.h

lib_LIBRARIES = libnewcomplex.a

libnewcomplex_a_SOURCES =
# Add the objects from all the helper libraries instead of source files.
libnewcomplex_a_LIBADD = \
	$(src_libnewcomplexf_a_OBJECTS) \
	$(src_libnewcomplexd_a_OBJECTS) \
	$(src_libnewcomplexld_a_OBJECTS)
libnewcomplex_a_DEPENDENCIES = $(newcomplex_libraries)

# Helper libraries.
newcomplex_libraries = \
	src/libnewcomplexf.a \
	src/libnewcomplexd.a \
	src/libnewcomplexld.a
noinst_LIBRARIES = $(newcomplex_libraries)

src_libnewcomplexf_a_SOURCES = $(newcomplex_src) src/complex.def_f.h
src_libnewcomplexf_a_CPPFLAGS = -D_NEWCOMPLEX_FLOAT $(AM_CPPFLAGS)

src_libnewcomplexd_a_SOURCES = $(newcomplex_src) src/complex.def_d.h
src_libnewcomplexd_a_CPPFLAGS = -D_NEWCOMPLEX_DOUBLE $(AM_CPPFLAGS)

src_libnewcomplexld_a_SOURCES = $(newcomplex_src) src/complex.def_ld.h
src_libnewcomplexld_a_CPPFLAGS = -D_NEWCOMPLEX_LDOUBLE $(AM_CPPFLAGS)

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
