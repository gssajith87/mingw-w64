AM_CFLAGS = -Wall -DWIN32_LEAN_AND_MEAN
ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libwinpthread.la

include_HEADERS = include/pthread.h include/sched.h include/semaphore.h include/pthread_unistd.h include/pthread_time.h include/pthread_compat.h
libwinpthread_la_CPPFLAGS = -I$(srcdir)/include -DIN_WINPTHREAD
libwinpthread_la_LDFLAGS = -no-undefined -version-info 1:0:0 -L$(builddir)
EXTRA_libwinpthread_la_DEPENDENCIES = libgcc.a
libwinpthread_la_SOURCES = \
  src/barrier.h  src/cond.h  src/misc.h  src/mutex.h  src/rwlock.h  src/spinlock.h  src/thread.h  src/ref.h  src/sem.h \
  src/barrier.c  src/cond.c  src/misc.c  src/mutex.c  src/rwlock.c  src/spinlock.c  src/thread.c  src/ref.c  src/sem.c  src/sched.c \
  src/winpthread_internal.h  src/clock.c src/nanosleep.c src/version.rc

noinst_LIBRARIES = libgcc.a  #libgcc.dll.a  libgcc_eh.a  libgcc_s.a  libgcc_s.dll.a libpthread.a
libgccsrc = src/libgcc/dll_dependency.S src/libgcc/dll_math.c
libgcc_a_SOURCES = $(libgccsrc)
libgcc_dll_a_SOURCES = $(libgccsrc)
libgcc_s_a_SOURCES =
libgcc_s_dll_a_SOURCES =
libgcc_eh_a_SOURCES =
libpthread_a_SOURCES =

lib_LIBRARIES =

# Tell libtool how to use the resource compiler
.rc.lo:
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --tag=RC --mode=compile $(RC) $(RCFLAGS) -i $< -o $@

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

DISTCHECK_CONFIGURE_FLAGS = --host=$(host_triplet)

