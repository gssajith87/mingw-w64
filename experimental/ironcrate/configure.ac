#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mingw-w64-runtime],[3.0b],[mingw-w64-public@lists.sourceforge.net])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CANONICAL_HOST

AC_CONFIG_SRCDIR([error/_ic_errno.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([windows.h])

# Checks for typedefs, structures, and compiler characteristics.
#AC_TYPE_SIZE_T

# Checks for library functions.
#AC_FUNC_ALLOCA
#AC_CHECK_FUNCS([fchdir strrchr])

AM_CONDITIONAL([MSVC_MODE], [ test "x$am_cv_CC_dependencies_compiler_type" = "xmsvc7" ])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
