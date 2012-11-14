ACLOCAL_AMFLAGS = -I build-aux

lib_LIBRARIES = libironcrate.a
bin_PROGRAMS = libironcrate-0.dll

if MSVC_MODE
AM_CPPFLAGS = -O2 -Zi
AM_CFLAGS =
noinst_DATA = ironcrate.lib
SHARED_FLAG = -LD
ironcrate.lib: libironcrate.a
	/bin/cp $< $@
	/bin/touch -m $< $@
else
SHARED_FLAG = -shared -Wl,-out-implib,libironcrate.dll.a
endif

clean-local:
	-/bin/rm -f libironcrate.dll.a ironcrate.lib

libironcrate_0_dll_SOURCES = $(libironcrate_a_SOURCES)
libironcrate_0_dll_CPPFLAGS = $(libironcrate_a_CPPFLAGS) -D__IN_IRONCRATE_DLL=1
libironcrate_0_dll_SHORTNAME = libironcrate_shared
libironcrate_0_dll_LDFLAGS = $(SHARED_FLAG)

libironcrate_a_CPPFLAGS = -I${srcdir}/include -D__IN_IRONCRATE=1
libironcrate_a_SHORTNAME = libironcrate_static

libironcrate_a_SOURCES = \
error/_ic_errno.c \
error/_ic_get_doserrno.c \
error/_ic_get_errno.c \
error/_ic_get_errno_from_winerr.c \
error/_ic_get_sys_errmsg.c \
error/_ic_mapwinerr.c \
error/_ic_set_doserrno.c \
error/_ic_set_errno.c \
error/_ic_sys_errlist.c \
error/_ic_sys_nerr.c \
error/__ic_doserrno.c \
error/__ic_sys_errlist.c \
error/__ic_sys_nerr.c \
except/__ic_excpt_act_table.c \
except/__ic_excpt_act_table_num.c \
except/__ic_excpt_act_table_sz.c \
locale/ic_lctemp_dest.c \
locale/ic_lctemp_init.c \
locale/_ic_configthreadlocale.c \
locale/_ic_free_locale.c \
locale/_ic_get_current_locale.c \
locale/_ic_localeconv.c \
locale/_ic_mbcasemap.c \
locale/_ic_mbctype.c \
locale/_ic_pctype.c \
locale/_ic_pwctype.c \
locale/_ic_wctype.c \
locale/__ic_add_locale_ref.c \
locale/__ic_cmpMBString.c \
locale/__ic_cmpWCString.c \
locale/__ic_free_lconv_mon.c \
locale/__ic_free_lconv_num.c \
locale/__ic_free_lc_time.c \
locale/__ic_free_thrdlocinfo.c \
locale/__ic_getlocaleinfoMBString.c \
locale/__ic_gettypeMBString.c \
locale/__ic_global_li.c \
locale/__ic_global_locale_status.c \
locale/__ic_global_locinfo.c \
locale/__ic_global_mbcinfo.c \
locale/__ic_ismbcodepage.c \
locale/__ic_is_systemcp.c \
locale/__ic_lcmapMBString.c \
locale/__ic_lcmapWCString.c \
locale/__ic_lconv.c \
locale/__ic_lconv_c.c \
locale/__ic_lconv_str_decimal.c \
locale/__ic_lconv_str_empty.c \
locale/__ic_lc_clike.c \
locale/__ic_lc_codepage.c \
locale/__ic_lc_collate_cp.c \
locale/__ic_lc_handle.c \
locale/__ic_lc_id.c \
locale/__ic_lc_time_c.c \
locale/__ic_lc_time_curr.c \
locale/__ic_locale_changed.c \
locale/__ic_mbcodepage.c \
locale/__ic_mblcid.c \
locale/__ic_mbulinfo.c \
locale/__ic_mb_cur_max.c \
locale/__ic_newclmap.c \
locale/__ic_newctype.c \
locale/__ic_newcumap.c \
locale/__ic_ptmbcinfo.c \
locale/__ic_release_locale_ref.c \
locale/__ic_str_C.c \
locale/__ic_tls_li.c \
locale/__ic_update_minfo.c \
locale/__ic_update_tlocinfo.c \
memory/ic_calloc.c \
memory/ic_free.c \
memory/ic_malloc.c \
memory/ic_memchr.c \
memory/ic_memcmp.c \
memory/ic_memcpy.c \
memory/ic_memcpy_s.c \
memory/ic_memmove.c \
memory/ic_memmove_s.c \
memory/ic_memset.c \
memory/ic_realloc.c \
memory/ic_set_new_handler.c \
memory/ic_wmemchr.c \
memory/ic_wmemcmp.c \
memory/ic_wmemcpy.c \
memory/ic_wmemcpy_s.c \
memory/ic_wmemmove.c \
memory/ic_wmemmove_s.c \
memory/ic_wmemset.c \
memory/_ic_aligned_free.c \
memory/_ic_aligned_malloc.c \
memory/_ic_aligned_msize.c \
memory/_ic_aligned_offset_malloc.c \
memory/_ic_aligned_offset_realloc.c \
memory/_ic_aligned_offset_recalloc.c \
memory/_ic_aligned_realloc.c \
memory/_ic_aligned_recalloc.c \
memory/_ic_amblksiz.c \
memory/_ic_callnewh.c \
memory/_ic_expand.c \
memory/_ic_freea.c \
memory/_ic_get_amblksiz.c \
memory/_ic_get_heap_handle.c \
memory/_ic_get_sbh_threshold.c \
memory/_ic_heapadd.c \
memory/_ic_heapchk.c \
memory/_ic_heapmin.c \
memory/_ic_heapset.c \
memory/_ic_heapused.c \
memory/_ic_heapwalk.c \
memory/_ic_heap_abort.c \
memory/_ic_heap_init.c \
memory/_ic_heap_term.c \
memory/_ic_markalloca.c \
memory/_ic_memccpy.c \
memory/_ic_memicmp.c \
memory/_ic_memicmp_l.c \
memory/_ic_msize.c \
memory/_ic_newmode.c \
memory/_ic_query_new_handler.c \
memory/_ic_recalloc.c \
memory/_ic_set_amblksiz.c \
memory/_ic_set_new_handler.c \
memory/_ic_set_sbh_threshold.c \
memory/_ic_theheap.c \
memory/__ic_memicmp_a.c \
memory/__ic_newhandle_fct.c \
memory/__p_ic_amblksiz.c \
misc/ic_rand.c \
misc/ic_rand_s.c \
misc/ic_srand.c \
sort/ic_bsearch.c \
sort/ic_bsearch_s.c \
sort/ic_qsort.c \
sort/ic_qsort_s.c \
sort/_ic_lfind.c \
sort/_ic_lfind_s.c \
sort/_ic_lsearch.c \
sort/_ic_lsearch_s.c \
threads/locks.c \
threads/tls.c \
threads/__ic_initCritSect.c \
threads/__ic_threadhandle.c \
threads/__ic_threadid.c

EXTRA_DIST = \
testsuite/dir/chmkrmdir1.c \
testsuite/dir/wchmkrmdir1.c \
testsuite/mbstring/_ismbbalnum.c \
testsuite/mbstring/_ismbbalnum_l.c \
testsuite/mbstring/_ismbbalpha.c \
testsuite/mbstring/_ismbbalpha_l.c \
testsuite/mbstring/_ismbbgraph.c \
testsuite/mbstring/_ismbbgraph_l.c \
testsuite/mbstring/_ismbbkalnum.c \
testsuite/mbstring/_ismbbkalnum_l.c \
testsuite/mbstring/_ismbbkana.c \
testsuite/mbstring/_ismbbkana_l.c \
testsuite/mbstring/_ismbbkprint.c \
testsuite/mbstring/_ismbbkprint_l.c \
testsuite/mbstring/_ismbbkpunct.c \
testsuite/mbstring/_ismbbkpunct_l.c \
testsuite/mbstring/_ismbblead.c \
testsuite/mbstring/_ismbblead_l.c \
testsuite/mbstring/_ismbbprint.c \
testsuite/mbstring/_ismbbprint_l.c \
testsuite/mbstring/_ismbbpunct.c \
testsuite/mbstring/_ismbbpunct_l.c \
testsuite/mbstring/_ismbbtrail.c \
testsuite/mbstring/_ismbbtrail_l.c \
testsuite/mbstring/_mbbtype.c \
testsuite/mbstring/_mbbtype_l.c \
testsuite/memory/memccpy.c \
testsuite/memory/memchr.c \
testsuite/memory/memcmp.c \
testsuite/memory/memcpy.c \
testsuite/memory/memcpy_s.c \
testsuite/memory/memicmp.c \
testsuite/memory/memicmp_l.c \
testsuite/memory/memmove.c \
testsuite/memory/memmove_s.c \
testsuite/memory/memset.c \
testsuite/string/strcat.c \
testsuite/string/strcat_s.c \
testsuite/string/strchr.c \
testsuite/string/strcmp.c \
testsuite/string/strcoll.c \
testsuite/string/strcoll_l.c \
testsuite/string/strcpy.c \
testsuite/string/strcpy_s.c \
testsuite/string/strcspn.c \
testsuite/string/strdup.c \
testsuite/string/stricmp.c \
testsuite/string/stricmp_l.c \
testsuite/string/strlen.c \
testsuite/string/strncat.c \
testsuite/string/strncat_s.c \
testsuite/string/strncmp.c \
testsuite/string/strncpy.c \
testsuite/string/strncpy_s.c \
testsuite/string/strnlen.c \
testsuite/string/strpbrk.c \
testsuite/string/strrchr.c \
testsuite/string/strspn.c \
testsuite/string/tolower.c \
testsuite/string/toupper.c \
testsuite/string/_strdate.c \
testsuite/string/_strdate_s.c \
testsuite/string/_stricoll.c \
testsuite/string/_stricoll_l.c \
testsuite/string/_strlwr.c \
testsuite/string/_strlwr_s_l.c \
testsuite/string/_strncoll.c \
testsuite/string/_strncoll_l.c \
testsuite/string/_strnicmp.c \
testsuite/string/_strnicmp_l.c \
testsuite/string/_strnicoll.c \
testsuite/string/_strnicoll_l.c \
testsuite/string/_strnset.c \
testsuite/string/_strnset_s.c \
testsuite/string/_strrev.c \
testsuite/string/_strset.c \
testsuite/string/_strset_s.c \
testsuite/string/_strtime.c \
testsuite/string/_strtime_s.c \
testsuite/string/_strupr.c \
testsuite/string/_strupr_s_l.c \
testsuite/string/__strncnt.c \
testsuite/testlib/main_test.c \
testsuite/time/strdate.c \
testsuite/time/strdate_s.c \
testsuite/time/strtime.c \
testsuite/time/strtime_s.c

check_PROGRAMS = \
testsuite/dir/chmkrmdir1$(EXEEXT) \
testsuite/dir/wchmkrmdir1$(EXEEXT) \
testsuite/mbstring/_ismbbalnum$(EXEEXT) \
testsuite/mbstring/_ismbbalnum_l$(EXEEXT) \
testsuite/mbstring/_ismbbalpha$(EXEEXT) \
testsuite/mbstring/_ismbbalpha_l$(EXEEXT) \
testsuite/mbstring/_ismbbgraph$(EXEEXT) \
testsuite/mbstring/_ismbbgraph_l$(EXEEXT) \
testsuite/mbstring/_ismbbkalnum$(EXEEXT) \
testsuite/mbstring/_ismbbkalnum_l$(EXEEXT) \
testsuite/mbstring/_ismbbkana$(EXEEXT) \
testsuite/mbstring/_ismbbkana_l$(EXEEXT) \
testsuite/mbstring/_ismbbkprint$(EXEEXT) \
testsuite/mbstring/_ismbbkprint_l$(EXEEXT) \
testsuite/mbstring/_ismbbkpunct$(EXEEXT) \
testsuite/mbstring/_ismbbkpunct_l$(EXEEXT) \
testsuite/mbstring/_ismbblead$(EXEEXT) \
testsuite/mbstring/_ismbblead_l$(EXEEXT) \
testsuite/mbstring/_ismbbprint$(EXEEXT) \
testsuite/mbstring/_ismbbprint_l$(EXEEXT) \
testsuite/mbstring/_ismbbpunct$(EXEEXT) \
testsuite/mbstring/_ismbbpunct_l$(EXEEXT) \
testsuite/mbstring/_ismbbtrail$(EXEEXT) \
testsuite/mbstring/_ismbbtrail_l$(EXEEXT) \
testsuite/mbstring/_mbbtype$(EXEEXT) \
testsuite/mbstring/_mbbtype_l$(EXEEXT) \
testsuite/memory/memccpy$(EXEEXT) \
testsuite/memory/memchr$(EXEEXT) \
testsuite/memory/memcmp$(EXEEXT) \
testsuite/memory/memcpy$(EXEEXT) \
testsuite/memory/memcpy_s$(EXEEXT) \
testsuite/memory/memicmp$(EXEEXT) \
testsuite/memory/memicmp_l$(EXEEXT) \
testsuite/memory/memmove$(EXEEXT) \
testsuite/memory/memmove_s$(EXEEXT) \
testsuite/memory/memset$(EXEEXT) \
testsuite/string/strcat$(EXEEXT) \
testsuite/string/strcat_s$(EXEEXT) \
testsuite/string/strchr$(EXEEXT) \
testsuite/string/strcmp$(EXEEXT) \
testsuite/string/strcoll$(EXEEXT) \
testsuite/string/strcoll_l$(EXEEXT) \
testsuite/string/strcpy$(EXEEXT) \
testsuite/string/strcpy_s$(EXEEXT) \
testsuite/string/strcspn$(EXEEXT) \
testsuite/string/strdup$(EXEEXT) \
testsuite/string/stricmp$(EXEEXT) \
testsuite/string/stricmp_l$(EXEEXT) \
testsuite/string/strlen$(EXEEXT) \
testsuite/string/strncat$(EXEEXT) \
testsuite/string/strncat_s$(EXEEXT) \
testsuite/string/strncmp$(EXEEXT) \
testsuite/string/strncpy$(EXEEXT) \
testsuite/string/strncpy_s$(EXEEXT) \
testsuite/string/strnlen$(EXEEXT) \
testsuite/string/strpbrk$(EXEEXT) \
testsuite/string/strrchr$(EXEEXT) \
testsuite/string/strspn$(EXEEXT) \
testsuite/string/tolower$(EXEEXT) \
testsuite/string/toupper$(EXEEXT) \
testsuite/string/_strdate$(EXEEXT) \
testsuite/string/_strdate_s$(EXEEXT) \
testsuite/string/_stricoll$(EXEEXT) \
testsuite/string/_stricoll_l$(EXEEXT) \
testsuite/string/_strlwr$(EXEEXT) \
testsuite/string/_strlwr_s_l$(EXEEXT) \
testsuite/string/_strncoll$(EXEEXT) \
testsuite/string/_strncoll_l$(EXEEXT) \
testsuite/string/_strnicmp$(EXEEXT) \
testsuite/string/_strnicmp_l$(EXEEXT) \
testsuite/string/_strnicoll$(EXEEXT) \
testsuite/string/_strnicoll_l$(EXEEXT) \
testsuite/string/_strnset$(EXEEXT) \
testsuite/string/_strnset_s$(EXEEXT) \
testsuite/string/_strrev$(EXEEXT) \
testsuite/string/_strset$(EXEEXT) \
testsuite/string/_strset_s$(EXEEXT) \
testsuite/string/_strtime$(EXEEXT) \
testsuite/string/_strtime_s$(EXEEXT) \
testsuite/string/_strupr$(EXEEXT) \
testsuite/string/_strupr_s_l$(EXEEXT) \
testsuite/string/__strncnt$(EXEEXT) \
testsuite/time/strdate$(EXEEXT) \
testsuite/time/strdate_s$(EXEEXT) \
testsuite/time/strtime$(EXEEXT) \
testsuite/time/strtime_s$(EXEEXT)

TESTS = $(testers_list)
