AM_CFLAGS = -Wall -DWIN32_LEAN_AND_MEAN
ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libwinpthread.la
lib_LIBRARIES =
fakelib_LIBRARIES = libgcc.a  libgcc.dll.a  libgcc_eh.a  libgcc_s.a  libgcc_s.dll.a libpthread.a
fakelibdir = fakelibs

libwinpthread_la_CPPFLAGS = -I$(srcdir)/include -DIN_WINPTHREAD
libwinpthread_la_LDFLAGS = -no-undefined -version-info 1:0:0

libwinpthread_la_SOURCES = \
  src/barrier.h  src/cond.h  src/misc.h  src/mutex.h  src/rwlock.h  src/spinlock.h  src/thread.h  src/ref.h  src/sem.h \
  src/barrier.c  src/cond.c  src/misc.c  src/mutex.c  src/rwlock.c  src/spinlock.c  src/thread.c  src/ref.c  src/sem.c  src/sched.c \
  src/winpthread_internal.h  src/clock.c src/nanosleep.c src/version.rc

include_HEADERS = include/pthread.h include/sched.h include/semaphore.h include/pthread_unistd.h include/pthread_time.h include/pthread_compat.h

DISTCHECK_CONFIGURE_FLAGS = --host=$(host_triplet)

.rc.lo:
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --tag=CC --mode=compile $(RC) @RCFLAGS@ $(RCFLAGS) -i $< -o $@

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

noinst_LTLIBRARIES = libdummy.la

libwinpthread_la_LIBADD = libdummy.la

libgcc_a_SOURCES = src/dll_dependency.S src/dll_math.c
libgcc_dll_a_SOURCES = src/dll_dependency.S src/dll_math.c
libgcc_s_a_SOURCES =
libgcc_s_dll_a_SOURCES =
libgcc_eh_a_SOURCES =
libpthread_a_SOURCES =

BUILT_SOURCES = dummy.c

libdummy_la_SOURCES = dummy.c

# Force libgcc dummy build
dummy.c: $(fakelib)
	echo "static int __attribute__((unused)) dummy;" > $@

if COPY_SHARED
lib_LIBRARIES += libpthread.dll.a
libpthread.dll.a: libwinpthread.la
	cp -p $(LT_OBJDIR)/libwinpthread.dll.a $@
	touch $@
endif

if COPY_STATIC
lib_LIBRARIES += libpthread.a
libpthread.a: libwinpthread.la
	cp -p $(LT_OBJDIR)/libwinpthread.a $@
	touch $@
endif
