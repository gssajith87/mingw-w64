#ifndef __W64CRT_MAP_H
#define __W64CRT_MAP_H

/* Map from versioned API to internal unversioned names.  */
/* misc/maperr.c.  */
#define __w64crt_get_errno_from_oserr_0_0 __w64crt_get_errno_from_oserr
/* misc/osdata.c */
#define __w64crt__osplatform_0_0 __w64crt__osplatform
#define __w64crt__osver_0_0 __w64crt__osver
#define __w64crt__winver_0_0 __w64crt__winver
#define __w64crt__winmajor_0_0 __w64crt__winmajor
#define __w64crt__winminor_0_0 __w64crt__winminor

#define __w64crt__get_osplatform_0_0 __w64crt__get_osplatform
#define __w64crt__get_osver_0_0 __w64crt__get_osver
#define __w64crt__get_winver_0_0 __w64crt__get_winver
#define __w64crt__get_winmajor_0_0 __w64crt__get_winmajor
#define __w64crt__get_winminor_0_0 __w64crt__get_winminor

/* Internal API only */
#define __w64crt_get_osplatform_0_0 __w64crt_get_osplatform
#define __w64crt_get_osver_0_0 __w64crt_get_osver
#define __w64crt_get_winver_0_0 __w64crt_get_winver
#define __w64crt_get_winmajor_0_0 __w64crt_get_winmajor
#define __w64crt_get_winminor_0_0 __w64crt_get_winminor

/* Map from internal unversioned names to external symbols.  */

#define __w64crt_get_errno_from_oserr get_errno_from_oserr

#define __w64crt__osplatform _osplatform
#define __w64crt__osver _osver
#define __w64crt__winver _winver
#define __w64crt__winmajor _winmajor
#define __w64crt__winminor _winminor

#define __w64crt__get_osplatform _get_osplatform
#define __w64crt__get_osver _get_osver
#define __w64crt__get_winver _get_winver
#define __w64crt__get_winmajor _get_winmajor
#define __w64crt__get_winminor _get_winminor

#endif

