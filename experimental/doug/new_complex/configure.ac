#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/complex_internal.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([subdir-objects foreign parallel-tests color-tests silent-rules])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# fake out configure for testing
AM_CONDITIONAL([LIB32], [true])
AM_CONDITIONAL([LIB64], [true])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

