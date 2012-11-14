ACLOCAL_AMFLAGS = -I build-aux

lib_LIBRARIES = libironcrate.a

libironcrate_a_SOURCES =
noinst_DIST = update_liblist.pl

include error/list.am
include except/list.am
include locale/list.am
include memory/list.am
include misc/list.am
include sort/list.am
include threads/list.am

if MSVC_MODE
AM_CPPFLAGS = -O2 -Zi
AM_CFLAGS =
noinst_DATA = ironcrate.lib
test_linklib = ironcrate.lib
ironcrate.lib: libironcrate.a
	/bin/cp $< $@
	/bin/touch -m $< $@
else
test_linklib = -L . libironcrate.a
endif

clean-local:
	-/bin/rm -f ironcrate.lib

test_cppflags =
test_cflags =
test_ldflags =
test_ldadd = $(test_linklib)

TESTS = $(check_PROGRAMS)
check_PROGRAMS =

include testsuite/list.am
