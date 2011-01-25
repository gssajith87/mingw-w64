/*
 This Software is provided under the Zope Public License (ZPL) Version 2.1.

 Copyright (c) 2009, 2010 by the mingw-w64 project

 See the AUTHORS file for the list of contributors to the mingw-w64 project.

 This license has been certified as open source. It has also been designated
 as GPL compatible by the Free Software Foundation (FSF).

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

   1. Redistributions in source code must retain the accompanying copyright
      notice, this list of conditions, and the following disclaimer.
   2. Redistributions in binary form must reproduce the accompanying
      copyright notice, this list of conditions, and the following disclaimer
      in the documentation and/or other materials provided with the
      distribution.
   3. Names of the copyright holders must not be used to endorse or promote
      products derived from this software without prior written permission
      from the copyright holders.
   4. The right to distribute this software or to use it for any purpose does
      not give you the right to use Servicemarks (sm) or Trademarks (tm) of
      the copyright holders.  Use of them is covered by separate agreement
      with the copyright holders.
   5. If any files are modified, you must cause the modified files to carry
      prominent notices stating that you changed the files and the date of
      any change.

 Disclaimer

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESSED
 OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define __STDC_WANT_DEC_FP__
#include <math.h>

/* Define some PI constants for long double, as they are not defined in math.h  */
#ifndef M_PI_4l
#define M_PI_4l 0.7853981633974483096156608458198757
#define M_PI_2l 1.5707963267948966192313216916397514
#define M_PIl   3.1415926535897932384626433832795029
#endif

typedef union t32 {
 _Decimal32 a;
 unsigned long b;
} t32;

typedef union t64 {
 _Decimal64 a;
 unsigned long long b;
} t64;

/* FIXME: Assuming little endian */
typedef union t128 {
 _Decimal128 a;
 struct {
   unsigned long long a;
   unsigned long long b;
 } b;
} t128;

#pragma pack(push,1)

/* We need to check the BID encoding format

_Decimal32:
MSB-----------------------------------------------------------------LSB
s         | 00eeeeee                      |(0)TTTtttttttttttttttttttt |
[sign bit]|[ proble bits must not be "11"]|[Implicit "0" MSB]         |
          |[ 8-bit exponent, "00" probed ]|[23-bit True Siginifcant  ]|

s         | 11 00eeeeee       |(100) Ttttttttttttttttttttt |
[sign bit]|["11" proble bits ]|                            |
          |[ 10-bit exponent ]|[Implicit "100" MSB]        |
          |                   |[21-bit True Significant   ]|

DFP = -1^s x tttt x [ 10 ^ (eeee - (101(base10))]

Examples:

s 00eeeeee (0)TTTtttttttttttttttttttt
s 01eeeeee (0)TTTtttttttttttttttttttt
s 10eeeeee (0)TTTtttttttttttttttttttt
s 11 01eeeeee (100)Ttttttttttttttttttttt
s 11 10eeeeee (100)Ttttttttttttttttttttt

NAN types:

s 11110 xxxxxxxxxxxxxxxxxxxxxxxxxx
s 111110 xxxxxxxxxxxxxxxxxxxxxxxxx
s 111111 xxxxxxxxxxxxxxxxxxxxxxxxx

_Decimal64:

s 00eeeeeeee TTTtttttttttttttttttttt tttttttttttttttttttttttttttttt
s 01eeeeeeee TTTtttttttttttttttttttt tttttttttttttttttttttttttttttt
s 10eeeeeeee TTTtttttttttttttttttttt tttttttttttttttttttttttttttttt
s 11 00eeeeeeee (100)Ttttttttttttttttttttt tttttttttttttttttttttttttttttt
s 11 01eeeeeeee (100)Ttttttttttttttttttttt tttttttttttttttttttttttttttttt
s 11 10eeeeeeee (100)Ttttttttttttttttttttt tttttttttttttttttttttttttttttt

DFP = -1^s x tttt x [ 10 ^ (eeee - (398(base10))]

_Decimal128:

s 00eeeeeeeeeeee TTTtttttttttttttttttttt tttttttttttttttttttttttttttttt tttttttttttttttttttttttttttttttttttttttttttttttttttttttt
s 01eeeeeeeeeeee TTTtttttttttttttttttttt tttttttttttttttttttttttttttttt tttttttttttttttttttttttttttttttttttttttttttttttttttttttt
s 10eeeeeeeeeeee TTTtttttttttttttttttttt tttttttttttttttttttttttttttttt tttttttttttttttttttttttttttttttttttttttttttttttttttttttt
s 11 00eeeeeeeeeeee (100)Ttttttttttttttttttttt tttttttttttttttttttttttttttttt tttttttttttttttttttttttttttttttttttttttttttttttttttttttt
s 11 01eeeeeeeeeeee (100)Ttttttttttttttttttttt tttttttttttttttttttttttttttttt tttttttttttttttttttttttttttttttttttttttttttttttttttttttt
s 11 10eeeeeeeeeeee (100)Ttttttttttttttttttttt tttttttttttttttttttttttttttttt tttttttttttttttttttttttttttttttttttttttttttttttttttttttt

DFP = -1^s x tttt x [ 10 ^ (eeee - (6176(base10))]

*/

typedef struct type0d32 {
  unsigned long long blob:29;
  unsigned long bits:2;
  unsigned long sign:1;
} type0d32;

typedef struct type1d32 {
  unsigned long long mantissa:23;
  unsigned long exponent:8;
  unsigned long sign:1;
} type1d32;

typedef struct type2d32 {
  unsigned long long mantissa:21;
  unsigned long exponent:10;
  unsigned long sign:1;
} type2d32;

typedef struct type0d64 {
  unsigned long long blob:61;
  unsigned long bits:2;
  unsigned long sign:1;
} type0d64;

typedef struct type1d64 {;
  unsigned long long mantissa:53;
  unsigned long exponent:10;
  unsigned long sign:1;
} type1d64;

typedef struct type2d64 {
  unsigned long long mantissa:51;
  unsigned long exponent:12;
  unsigned long sign:1;
} type2d64;

typedef struct type0d128 {
  unsigned long long blobL:64;
  unsigned long long blobH:61;
  unsigned long bits:2;
  unsigned long sign:1;
} type0d128;

typedef struct type1d128 {
  unsigned long long mantissaL:64;
  unsigned long long mantissaH:59;
  unsigned long exponent:14;
  unsigned long sign:1;
} type1d128;

typedef struct type2d128 {
  unsigned long long mantissaL:64;
  unsigned long long mantissaH:57;
  unsigned long exponent:16;
  unsigned long sign:1;
} type2d128;
#pragma pack(pop)

typedef union ud32 {
  _Decimal32 d;
  type0d32 t0;
  type1d32 t1;
  type2d32 t2;
  unsigned char b[sizeof(_Decimal32)];
} ud32;

/* Some more helpers.  */
#define M_PI_3_4  (M_PI - M_PI_4)
#define M_PI_3_4l (M_PIl - M_PI_4l)

/*** From libdecnumber ***/
#define DECIMAL_NaN     0x7c	/* 0 11111 00 NaN	      */
#define DECIMAL_sNaN    0x7e	/* 0 11111 10 sNaN	      */
#define DECIMAL_Inf     0x78	/* 0 11110 00 Infinity	      */
/* Bit settings for decNumber.bits				      */
#define DECNEG    0x80      /* Sign; 1=negative, 0=positive or zero */
#define DECINF    0x40      /* 1=Infinity			      */
#define DECNAN    0x20      /* 1=NaN				      */
#define DECSNAN   0x10      /* 1=sNaN 			      */
/* The remaining bits are reserved; they must be 0		      */
#define DECSPECIAL (DECINF|DECNAN|DECSNAN) /* any special value     */

#if defined(_DFP32_FLOAT)
# define __FLT_TYPE	_Decimal32
# define __FLT_ABI(N)	N##d32
# define __FLT_CST(N)	N##DF
# define __FLT_EPSILON  __DEC32_EPSILON__
# define __FLT_NAN	nand32("")
# define __FLT_HUGE_VAL	__infd32()
# define __FLT_PI	__FLT_CST(M_PI)
# define __FLT_PI_2	__FLT_CST(M_PI_2)
# define __FLT_PI_4	__FLT_CST(M_PI_4)
# define __FLT_PI_3_4	__FLT_CST(M_PI_3_4)
# define __FLT_MAXLOG	223.350753920422420DF
# define __FLT_MINLOG	-218.7455838344343DF
# define __FLT_LOGE2	0.693147180559945309DF
# define __FLT_REPORT(NAME) NAME "d32"
/********
__FLT_MAXLOG and __FLT_MINLOG are incorrect for _Decimal64 _Decimal128
********/
#elif defined(_DFP64_FLOAT)
# define __FLT_TYPE	_Decimal64
# define __FLT_ABI(N)	N##d64
# define __FLT_EPSILON  __DEC64_EPSILON__
# define __FLT_CST(N)	dd
# define __FLT_NAN	nand64("")
# define __FLT_HUGE_VAL	__infd64()
# define __FLT_PI	__FLT_CST(M_PI)
# define __FLT_PI_2	__FLT_CST(M_PI_2)
# define __FLT_PI_4	__FLT_CST(M_PI_4)
# define __FLT_PI_3_4	__FLT_CST(M_PI_3_4)
# define __FLT_MAXLOG	7.09782712893383996843E2
# define __FLT_MINLOG	-7.08396418532264106224E2
# define __FLT_LOGE2	6.93147180559945309417E-1
# define __FLT_REPORT(NAME)	NAME
#elif defined(_DFP128_FLOAT)
# define __FLT_TYPE	_Decimal128
# define __FLT_ABI(N)	N##d128
# define __FLT_CST(N)	N##dl
# define __FLT_EPSILON  __DEC128_EPSILON__
# define __FLT_NAN	nand128("")
# define __FLT_HUGE_VAL	__infd128()
# define __FLT_PI	__FLT_CST(M_PI)
# define __FLT_PI_2	__FLT_CST(M_PI_2)
# define __FLT_PI_4	__FLT_CST(M_PI_4)
# define __FLT_PI_3_4	__FLT_CST(M_PI_3_4)
# define __FLT_MAXLOG	1.1356523406294143949492E4L
# define __FLT_MINLOG	-1.13994985314888605586758E4L
# define __FLT_LOGE2	6.9314718055994530941723E-1L
# define __FLT_REPORT(NAME) NAME "d128"
#else
# error "Unknown complex number type"
#endif

#define __FLT_RPT_DOMAIN(NAME, ARG1, ARG2, RSLT) \
	errno = EDOM, \
	__mingw_raise_matherr (_DOMAIN, __FLT_REPORT(NAME), (double) (ARG1), \
			       (double) (ARG2), (double) (RSLT))
#define __FLT_RPT_ERANGE(NAME, ARG1, ARG2, RSLT, OVL) \
	errno = ERANGE, \
        __mingw_raise_matherr (((OVL) ? _OVERFLOW : _UNDERFLOW), \
			       __FLT_REPORT(NAME), (double) (ARG1), \
                               (double) (ARG2), (double) (RSLT))

