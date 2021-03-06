#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mingw-w64-headers],[3.0b],[mingw-w64-public@lists.sourceforge.net])
AC_CONFIG_SRCDIR([crt/_mingw.h.in])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign])
AM_MAINTAINER_MODE

AC_CANONICAL_HOST

# Checks for programs.
# AC_PROG_SED
AC_PROG_AWK

# Search for a usable widl.  If PATH is given, search there.  Otherwise, search
# in $PATH.  In all cases, search for a canonicalized name first ($host-widl),
# followed by a non-canonicalized name (widl).  If these fail, error out.
# NB: $host from this perspective is the same as $target while building widl.
AC_MSG_CHECKING([whether to rebuild headers with widl])
AC_ARG_WITH([widl],
  AS_HELP_STRING([--with-widl=PATH],
    [use widl to update idl-based headers.  Optionally search for a compatible widl in PATH]),
  [],
  [AS_VAR_SET([with_widl],[no])])
AC_MSG_RESULT([$with_widl])

AS_VAR_IF([with_widl],[yes],[AS_VAR_SET([with_widl],["$PATH"])])
AS_VAR_IF([with_widl],[no],[],[
  AC_PATH_PROGS([WIDL], [$host-widl widl], [], [$with_widl])
  AS_VAR_IF([WIDL],[],[AC_MSG_ERROR([--with-widl is specified, but widl installation could not be found.])])])

AM_CONDITIONAL([HAVE_WIDL],[AS_VAR_TEST_SET([WIDL])])

# Checks for libraries.

# Checks for header files.

BASEHEAD_LIST="crt/_bsd_types.h crt/_cygwin.h crt/_mingw.h crt/_mingw_mac.h crt/_mingw_print_push.h crt/_mingw_print_pop.h crt/_mingw_secapi.h crt/_mingw_unicode.h crt/_timeval.h crt/crtdefs.h crt/excpt.h crt/vadefs.h "$srcdir/include/*.h
SECHEAD_LIST="$srcdir/crt/sec_api/stralign_s.h"
for i in dlg h16 hxx rh ver; do
  BASEHEAD_LIST="$BASEHEAD_LIST "$srcdir/include/*.$i
done
#FIXME: Add in base directx

AC_MSG_CHECKING([whether to build a w32api package for Cygwin])
AC_ARG_ENABLE([w32api],
  [AS_HELP_STRING([--enable-w32api],
    [Enable building a w32api package for Cygwin (shorthand for --includedir=PREFIX/include/w32api --disable-crt)])],
  [],
  [AS_VAR_SET([enable_w32api],[no])])
AC_MSG_RESULT([$enable_w32api])
AS_CASE([$enable_w32api],
  [no],[],
  [yes],[AS_VAR_SET([W32API])
  	 AS_VAR_SET([enable_crt],[no])
	 AS_VAR_SET([includedir],[${prefix}/include/w32api])],
  [AC_MSG_ERROR([invalid argument.  Must be either yes or no.])])
AM_CONDITIONAL([W32API], [AS_VAR_TEST_SET([W32API])])

AC_MSG_CHECKING([for c-runtime headers])
AC_ARG_ENABLE([crt],
  [AS_HELP_STRING([--disable-crt],
    [Do not use the default crt headers])],
  [],
  [enable_crt=yes])
AM_CONDITIONAL([ENABLE_CRT],[test x$enable_crt = xyes])
AC_MSG_RESULT([$enable_crt])
AS_VAR_IF([enable_crt],[yes],[
  BASEHEAD_LIST="$BASEHEAD_LIST "$srcdir/crt/*.h
  SYSHEAD_LIST=$srcdir/crt/sys/*.h
  SECHEAD_LIST=$srcdir/crt/sec_api/*.h
  SECSYSHEAD_LIST=$srcdir/crt/sec_api/sys/*.h
])
GDIPLUSHEAD_LIST=$srcdir/include/gdiplus/*.h
GLHEAD_LIST=$srcdir/include/GL/*.h
MINGWHELPERHEAD_LIST=$srcdir/include/psdk_inc/*.h
AC_SUBST([BASEHEAD_LIST])
AC_SUBST([GDIPLUSHEAD_LIST])
AC_SUBST([GLHEAD_LIST])
AC_SUBST([MINGWHELPERHEAD_LIST])
AC_SUBST([SYSHEAD_LIST])
AC_SUBST([SECHEAD_LIST])
AC_SUBST([SECSYSHEAD_LIST])

AC_MSG_CHECKING([for optional sdk headers])
AC_ARG_ENABLE([sdk],
  [AS_HELP_STRING([--enable-sdk=ARG],
    [Add the comma seperated desired SDKs, where ARG can be any combination of ddk, directx, ndk, or all. ndk must be enabled explicitly.])],
  [],
  [AS_VAR_SET([enable_sdk],[all])])

for enabled_sdk_token in $(echo $enable_sdk | $AWK 'BEGIN {FS = ","} {for (i=1; i <= NF; i++) printf "%s ", $i}')
do
AS_CASE([$enabled_sdk_token],
  [all|yes],[
    AS_ECHO_N([all ])
    # AS_VAR_SET([enable_ndk],[yes])
    AS_VAR_SET([enable_directx],[yes])
    AS_VAR_SET([enable_ddk],[yes])],
  [ddk],[
    AS_ECHO_N([DDK ])
    AS_VAR_SET([enable_ddk],[yes])],
  [ndk],[
    AS_ECHO_N([NDK ])
    AS_VAR_SET([enable_ndk],[yes])],
  [directx],[
    AS_ECHO_N([DirectX ])
    AS_VAR_SET([enable_directx],[yes])],
  [no],[],
  [AC_MSG_ERROR([Invalid --enable-sdk option: $enabled_sdk_token.])])
done
AS_ECHO([])

AS_VAR_IF([enable_directx],[yes],[
    DXHEAD_LIST=$srcdir/direct-x/include/*.[[hi]]*
    MINGW_HAS_DX=1
  ],[
    MINGW_HAS_DX=0
  ])
AC_SUBST([DXHEAD_LIST])
AC_SUBST([MINGW_HAS_DX])

AC_SUBST([PKGCONFIG_DDK_PATH],["${prefix}/${host}"])
AS_VAR_IF([enable_ddk],[yes],[
    DDKHEAD_LIST=$srcdir/ddk/include/ddk/*.h
    MINGW_HAS_DDK=1
    AC_CONFIG_FILES([mingw-w64-headers-ddk.pc:pkgconfig/mingw-w64-headers-ddk.pc.in])
  ],[
    MINGW_HAS_DDK=0
  ])
AC_SUBST([DDKHEAD_LIST])
AC_SUBST([MINGW_HAS_DDK])
AM_CONDITIONAL([HAVE_DDK],[test x${enable_ddk} = xyes])

AC_SUBST([PKGCONFIG_NDK_PATH],["${prefix}/${host}"])
AS_VAR_IF([enable_ndk],[yes],[
    NDKHEAD_LIST=${srcdir}/ndk/*.*
    NDKHEAD_AMD64=${srcdir}/ndk/amd64/*
    NDKHEAD_ARCH=${srcdir}/ndk/arch/*
    NDKHEAD_ARM=${srcdir}/ndk/arm/*
    NDKHEAD_i386=${srcdir}/ndk/i386/*
    NDKHEAD_PPC=${srcdir}/ndk/powerpc/*
    NDKHEAD_TESTS=${srcdir}/ndk/tests/*
    MINGW_HAS_NDK=1
    AC_CONFIG_FILES([mingw-w64-headers-ndk.pc:pkgconfig/mingw-w64-headers-ndk.pc.in])
  ],[
    MINGW_HAS_NDK=1
  ])
AC_SUBST([NDKHEAD_LIST])
AC_SUBST([NDKHEAD_AMD64])
AC_SUBST([NDKHEAD_ARCH])
AC_SUBST([NDKHEAD_ARM])
AC_SUBST([NDKHEAD_i386])
AC_SUBST([NDKHEAD_PPC])
AC_SUBST([NDKHEAD_TESTS])
AC_SUBST([MINGW_HAS_NDK])
AM_CONDITIONAL([HAVE_NDK],[test x${enable_ndk} = xyes])

AC_MSG_CHECKING([if installing idl files is enabled])
AC_ARG_ENABLE([idl],
    [AS_HELP_STRING([--enable-idl],
        [Enable installing idl files (default enabled)])],
    [],[AS_VAR_SET([enable_idl],[yes])])
AC_MSG_RESULT([$enable_idl])
AS_VAR_IF([enable_idl],[yes],
    [IDLHEAD_LIST=$srcdir/include/*.idl],
    [IDLHEAD_LIST=""])
AC_SUBST([IDLHEAD_LIST])

AC_MSG_CHECKING([whether to enable the secure API])
AC_ARG_ENABLE([secure-api],
  [AS_HELP_STRING([--enable-secure-api],
    [Enable secure API by default])],
  [],[enable_secure_api=yes])
AC_MSG_RESULT([$enable_secure_api])
AS_VAR_IF([enable_secure_api],[yes],
  [MINGW_HAS_SECURE_API="#define MINGW_HAS_SECURE_API 1"],
  [MINGW_HAS_SECURE_API=""])
AC_SUBST([MINGW_HAS_SECURE_API])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([
  Makefile
  crt/_mingw.h
])
AC_CONFIG_FILES([crt/sdks/_mingw_directx.h])
AC_CONFIG_FILES([crt/sdks/_mingw_ddk.h])
AC_OUTPUT

