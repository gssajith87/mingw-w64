#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# Use AM_MAINTANER_MODE somewhere in this file once reconfigurations settle down.

AC_PREREQ(2.61)
AC_INIT([x86_64-mingw-runtime],[3.9.1],[mingw-w64-public@lists.sourceforge.net])

#AC_CANONICAL_SYSTEM is apparently obsolete.. should use AC_CANONICAL_BUILD, _HOST, and _TARGET
#as needed.  Also, they seem to be hierarchical -- _TARGET includes _HOST, and _HOST includes
#_BUILD.  For the runtime, we only need a build and a host, as target has no meaning.

AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([atonexit.c])
AC_CONFIG_HEADER([config.h])

AC_ARG_WITH(sysroot,
[  --with-sysroot[=DIR] Search for usr/lib, usr/include, et al, within DIR.],
[
 case ${with_sysroot} in
 yes) TARGET_SYSTEM_ROOT='${exec_prefix}/${target_noncanonical}/sys-root' ;;
 *) TARGET_SYSTEM_ROOT=$with_sysroot
    PATH=$with_sysroot/bin:$PATH
    ;;
 esac
], [
  TARGET_SYSTEM_ROOT=
])

AM_CONDITIONAL(WITHSYSROOT, test x$TARGET_SYSTEM_ROOT != x)
AC_SUBST(TARGET_SYSTEM_ROOT)

# Checks for programs.
# Checks for headers, libs, etc need to utilize the sysroot... no idea how
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_LIBTOOL_WIN32_DLL
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AM_PROG_AS


# Checks for libraries.

# Checks for header files.
#AC_HEADER_DIRENT
#AC_HEADER_STDC
#AC_CHECK_HEADERS([fcntl.h fenv.h float.h inttypes.h limits.h locale.h malloc.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/time.h sys/timeb.h termios.h unistd.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_TYPE_UINT32_T
AC_C_VOLATILE
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
#AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
#AC_FUNC_MBRTOWC
#AC_FUNC_REALLOC
#AC_FUNC_STRTOD
#AC_FUNC_VPRINTF
#AC_CHECK_FUNCS([alarm atexit btowc fesetround floor ftruncate gettimeofday isascii localeconv mbrlen memmove memset pow rint setlocale sqrt strcasecmp strchr strncasecmp strtoull strtoumax])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
