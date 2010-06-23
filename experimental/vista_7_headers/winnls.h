/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#ifndef _WINNLS_
#define _WINNLS_

#include <_mingw_unicode.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NONLS

#define MAX_LEADBYTES 12
#define MAX_DEFAULTCHAR 2

#define MB_PRECOMPOSED 0x00000001
#define MB_COMPOSITE 0x00000002
#define MB_USEGLYPHCHARS 0x00000004
#define MB_ERR_INVALID_CHARS 0x00000008

#define WC_COMPOSITECHECK 0x00000200
#define WC_DISCARDNS 0x00000010
#define WC_SEPCHARS 0x00000020
#define WC_DEFAULTCHAR 0x00000040
#define WC_NO_BEST_FIT_CHARS 0x00000400

#define CT_CTYPE1 0x00000001
#define CT_CTYPE2 0x00000002
#define CT_CTYPE3 0x00000004

#define C1_UPPER 0x0001
#define C1_LOWER 0x0002
#define C1_DIGIT 0x0004
#define C1_SPACE 0x0008
#define C1_PUNCT 0x0010
#define C1_CNTRL 0x0020
#define C1_BLANK 0x0040
#define C1_XDIGIT 0x0080
#define C1_ALPHA 0x0100
#define C1_DEFINED 0x0200

#define C2_LEFTTORIGHT 0x0001
#define C2_RIGHTTOLEFT 0x0002

#define C2_EUROPENUMBER 0x0003
#define C2_EUROPESEPARATOR 0x0004
#define C2_EUROPETERMINATOR 0x0005
#define C2_ARABICNUMBER 0x0006
#define C2_COMMONSEPARATOR 0x0007

#define C2_BLOCKSEPARATOR 0x0008
#define C2_SEGMENTSEPARATOR 0x0009
#define C2_WHITESPACE 0x000A
#define C2_OTHERNEUTRAL 0x000B

#define C2_NOTAPPLICABLE 0x0000

#define C3_NONSPACING 0x0001
#define C3_DIACRITIC 0x0002
#define C3_VOWELMARK 0x0004
#define C3_SYMBOL 0x0008

#define C3_KATAKANA 0x0010
#define C3_HIRAGANA 0x0020
#define C3_HALFWIDTH 0x0040
#define C3_FULLWIDTH 0x0080
#define C3_IDEOGRAPH 0x0100
#define C3_KASHIDA 0x0200
#define C3_LEXICAL 0x0400

#define C3_ALPHA 0x8000

#define C3_NOTAPPLICABLE 0x0000

#define NORM_IGNORECASE 0x00000001
#define NORM_IGNORENONSPACE 0x00000002
#define NORM_IGNORESYMBOLS 0x00000004

#define NORM_IGNOREKANATYPE 0x00010000
#define NORM_IGNOREWIDTH 0x00020000

#define MAP_FOLDCZONE 0x00000010
#define MAP_PRECOMPOSED 0x00000020
#define MAP_COMPOSITE 0x00000040
#define MAP_FOLDDIGITS 0x00000080
#define MAP_EXPAND_LIGATURES 0x00002000

#define LCMAP_LOWERCASE 0x00000100
#define LCMAP_UPPERCASE 0x00000200
#define LCMAP_SORTKEY 0x00000400
#define LCMAP_BYTEREV 0x00000800

#define LCMAP_HIRAGANA 0x00100000
#define LCMAP_KATAKANA 0x00200000
#define LCMAP_HALFWIDTH 0x00400000
#define LCMAP_FULLWIDTH 0x00800000

#define LCMAP_LINGUISTIC_CASING 0x01000000

#define LCMAP_SIMPLIFIED_CHINESE 0x02000000
#define LCMAP_TRADITIONAL_CHINESE 0x04000000

#define LGRPID_INSTALLED 0x00000001
#define LGRPID_SUPPORTED 0x00000002

#define LCID_INSTALLED 0x00000001
#define LCID_SUPPORTED 0x00000002
#define LCID_ALTERNATE_SORTS 0x00000004

#define CP_INSTALLED 0x00000001
#define CP_SUPPORTED 0x00000002

#define SORT_STRINGSORT 0x00001000

#define CSTR_LESS_THAN 1
#define CSTR_EQUAL 2
#define CSTR_GREATER_THAN 3

#define CP_ACP 0
#define CP_OEMCP 1
#define CP_MACCP 2
#define CP_THREAD_ACP 3
#define CP_SYMBOL 42

#define CP_UTF7 65000
#define CP_UTF8 65001

#define CTRY_DEFAULT 0

#define CTRY_ALBANIA 355
#define CTRY_ALGERIA 213
#define CTRY_ARGENTINA 54
#define CTRY_ARMENIA 374
#define CTRY_AUSTRALIA 61
#define CTRY_AUSTRIA 43
#define CTRY_AZERBAIJAN 994
#define CTRY_BAHRAIN 973
#define CTRY_BELARUS 375
#define CTRY_BELGIUM 32
#define CTRY_BELIZE 501
#define CTRY_BOLIVIA 591
#define CTRY_BRAZIL 55
#define CTRY_BRUNEI_DARUSSALAM 673
#define CTRY_BULGARIA 359
#define CTRY_CANADA 2
#define CTRY_CARIBBEAN 1
#define CTRY_CHILE 56
#define CTRY_COLOMBIA 57
#define CTRY_COSTA_RICA 506
#define CTRY_CROATIA 385
#define CTRY_CZECH 420
#define CTRY_DENMARK 45
#define CTRY_DOMINICAN_REPUBLIC 1
#define CTRY_ECUADOR 593
#define CTRY_EGYPT 20
#define CTRY_EL_SALVADOR 503
#define CTRY_ESTONIA 372
#define CTRY_FAEROE_ISLANDS 298
#define CTRY_FINLAND 358
#define CTRY_FRANCE 33
#define CTRY_GEORGIA 995
#define CTRY_GERMANY 49
#define CTRY_GREECE 30
#define CTRY_GUATEMALA 502
#define CTRY_HONDURAS 504
#define CTRY_HONG_KONG 852
#define CTRY_HUNGARY 36
#define CTRY_ICELAND 354
#define CTRY_INDIA 91
#define CTRY_INDONESIA 62
#define CTRY_IRAN 981
#define CTRY_IRAQ 964
#define CTRY_IRELAND 353
#define CTRY_ISRAEL 972
#define CTRY_ITALY 39
#define CTRY_JAMAICA 1
#define CTRY_JAPAN 81
#define CTRY_JORDAN 962
#define CTRY_KAZAKSTAN 7
#define CTRY_KENYA 254
#define CTRY_KUWAIT 965
#define CTRY_KYRGYZSTAN 996
#define CTRY_LATVIA 371
#define CTRY_LEBANON 961
#define CTRY_LIBYA 218
#define CTRY_LIECHTENSTEIN 41
#define CTRY_LITHUANIA 370
#define CTRY_LUXEMBOURG 352
#define CTRY_MACAU 853
#define CTRY_MACEDONIA 389
#define CTRY_MALAYSIA 60
#define CTRY_MALDIVES 960
#define CTRY_MEXICO 52
#define CTRY_MONACO 33
#define CTRY_MONGOLIA 976
#define CTRY_MOROCCO 212
#define CTRY_NETHERLANDS 31
#define CTRY_NEW_ZEALAND 64
#define CTRY_NICARAGUA 505
#define CTRY_NORWAY 47
#define CTRY_OMAN 968
#define CTRY_PAKISTAN 92
#define CTRY_PANAMA 507
#define CTRY_PARAGUAY 595
#define CTRY_PERU 51
#define CTRY_PHILIPPINES 63
#define CTRY_POLAND 48
#define CTRY_PORTUGAL 351
#define CTRY_PRCHINA 86
#define CTRY_PUERTO_RICO 1
#define CTRY_QATAR 974
#define CTRY_ROMANIA 40
#define CTRY_RUSSIA 7
#define CTRY_SAUDI_ARABIA 966
#define CTRY_SERBIA 381
#define CTRY_SINGAPORE 65
#define CTRY_SLOVAK 421
#define CTRY_SLOVENIA 386
#define CTRY_SOUTH_AFRICA 27
#define CTRY_SOUTH_KOREA 82
#define CTRY_SPAIN 34
#define CTRY_SWEDEN 46
#define CTRY_SWITZERLAND 41
#define CTRY_SYRIA 963
#define CTRY_TAIWAN 886
#define CTRY_TATARSTAN 7
#define CTRY_THAILAND 66
#define CTRY_TRINIDAD_Y_TOBAGO 1
#define CTRY_TUNISIA 216
#define CTRY_TURKEY 90
#define CTRY_UAE 971
#define CTRY_UKRAINE 380
#define CTRY_UNITED_KINGDOM 44
#define CTRY_UNITED_STATES 1
#define CTRY_URUGUAY 598
#define CTRY_UZBEKISTAN 7
#define CTRY_VENEZUELA 58
#define CTRY_VIET_NAM 84
#define CTRY_YEMEN 967
#define CTRY_ZIMBABWE 263

#define LOCALE_NOUSEROVERRIDE 0x80000000
#define LOCALE_USE_CP_ACP 0x40000000
#define LOCALE_RETURN_NUMBER 0x20000000

#define LOCALE_ILANGUAGE 0x00000001
#define LOCALE_SLANGUAGE 0x00000002
#define LOCALE_SENGLANGUAGE 0x00001001
#define LOCALE_SABBREVLANGNAME 0x00000003
#define LOCALE_SNATIVELANGNAME 0x00000004

#define LOCALE_ICOUNTRY 0x00000005
#define LOCALE_SCOUNTRY 0x00000006
#define LOCALE_SENGCOUNTRY 0x00001002
#define LOCALE_SABBREVCTRYNAME 0x00000007
#define LOCALE_SNATIVECTRYNAME 0x00000008

#define LOCALE_IDEFAULTLANGUAGE 0x00000009
#define LOCALE_IDEFAULTCOUNTRY 0x0000000A
#define LOCALE_IDEFAULTCODEPAGE 0x0000000B
#define LOCALE_IDEFAULTANSICODEPAGE 0x00001004
#define LOCALE_IDEFAULTMACCODEPAGE 0x00001011

#define LOCALE_SLIST 0x0000000C
#define LOCALE_IMEASURE 0x0000000D

#define LOCALE_SDECIMAL 0x0000000E
#define LOCALE_STHOUSAND 0x0000000F
#define LOCALE_SGROUPING 0x00000010
#define LOCALE_IDIGITS 0x00000011
#define LOCALE_ILZERO 0x00000012
#define LOCALE_INEGNUMBER 0x00001010
#define LOCALE_SNATIVEDIGITS 0x00000013

#define LOCALE_SCURRENCY 0x00000014
#define LOCALE_SINTLSYMBOL 0x00000015
#define LOCALE_SMONDECIMALSEP 0x00000016
#define LOCALE_SMONTHOUSANDSEP 0x00000017
#define LOCALE_SMONGROUPING 0x00000018
#define LOCALE_ICURRDIGITS 0x00000019
#define LOCALE_IINTLCURRDIGITS 0x0000001A
#define LOCALE_ICURRENCY 0x0000001B
#define LOCALE_INEGCURR 0x0000001C

#define LOCALE_SDATE 0x0000001D
#define LOCALE_STIME 0x0000001E
#define LOCALE_SSHORTDATE 0x0000001F
#define LOCALE_SLONGDATE 0x00000020
#define LOCALE_STIMEFORMAT 0x00001003
#define LOCALE_IDATE 0x00000021
#define LOCALE_ILDATE 0x00000022
#define LOCALE_ITIME 0x00000023
#define LOCALE_ITIMEMARKPOSN 0x00001005
#define LOCALE_ICENTURY 0x00000024
#define LOCALE_ITLZERO 0x00000025
#define LOCALE_IDAYLZERO 0x00000026
#define LOCALE_IMONLZERO 0x00000027
#define LOCALE_S1159 0x00000028
#define LOCALE_S2359 0x00000029

#define LOCALE_ICALENDARTYPE 0x00001009
#define LOCALE_IOPTIONALCALENDAR 0x0000100B
#define LOCALE_IFIRSTDAYOFWEEK 0x0000100C
#define LOCALE_IFIRSTWEEKOFYEAR 0x0000100D

#define LOCALE_SDAYNAME1 0x0000002A
#define LOCALE_SDAYNAME2 0x0000002B
#define LOCALE_SDAYNAME3 0x0000002C
#define LOCALE_SDAYNAME4 0x0000002D
#define LOCALE_SDAYNAME5 0x0000002E
#define LOCALE_SDAYNAME6 0x0000002F
#define LOCALE_SDAYNAME7 0x00000030
#define LOCALE_SABBREVDAYNAME1 0x00000031
#define LOCALE_SABBREVDAYNAME2 0x00000032
#define LOCALE_SABBREVDAYNAME3 0x00000033
#define LOCALE_SABBREVDAYNAME4 0x00000034
#define LOCALE_SABBREVDAYNAME5 0x00000035
#define LOCALE_SABBREVDAYNAME6 0x00000036
#define LOCALE_SABBREVDAYNAME7 0x00000037
#define LOCALE_SMONTHNAME1 0x00000038
#define LOCALE_SMONTHNAME2 0x00000039
#define LOCALE_SMONTHNAME3 0x0000003A
#define LOCALE_SMONTHNAME4 0x0000003B
#define LOCALE_SMONTHNAME5 0x0000003C
#define LOCALE_SMONTHNAME6 0x0000003D
#define LOCALE_SMONTHNAME7 0x0000003E
#define LOCALE_SMONTHNAME8 0x0000003F
#define LOCALE_SMONTHNAME9 0x00000040
#define LOCALE_SMONTHNAME10 0x00000041
#define LOCALE_SMONTHNAME11 0x00000042
#define LOCALE_SMONTHNAME12 0x00000043
#define LOCALE_SMONTHNAME13 0x0000100E
#define LOCALE_SABBREVMONTHNAME1 0x00000044
#define LOCALE_SABBREVMONTHNAME2 0x00000045
#define LOCALE_SABBREVMONTHNAME3 0x00000046
#define LOCALE_SABBREVMONTHNAME4 0x00000047
#define LOCALE_SABBREVMONTHNAME5 0x00000048
#define LOCALE_SABBREVMONTHNAME6 0x00000049
#define LOCALE_SABBREVMONTHNAME7 0x0000004A
#define LOCALE_SABBREVMONTHNAME8 0x0000004B
#define LOCALE_SABBREVMONTHNAME9 0x0000004C
#define LOCALE_SABBREVMONTHNAME10 0x0000004D
#define LOCALE_SABBREVMONTHNAME11 0x0000004E
#define LOCALE_SABBREVMONTHNAME12 0x0000004F
#define LOCALE_SABBREVMONTHNAME13 0x0000100F

#define LOCALE_SPOSITIVESIGN 0x00000050
#define LOCALE_SNEGATIVESIGN 0x00000051
#define LOCALE_IPOSSIGNPOSN 0x00000052
#define LOCALE_INEGSIGNPOSN 0x00000053
#define LOCALE_IPOSSYMPRECEDES 0x00000054
#define LOCALE_IPOSSEPBYSPACE 0x00000055
#define LOCALE_INEGSYMPRECEDES 0x00000056
#define LOCALE_INEGSEPBYSPACE 0x00000057
#define LOCALE_FONTSIGNATURE 0x00000058
#define LOCALE_SISO639LANGNAME 0x00000059
#define LOCALE_SISO3166CTRYNAME 0x0000005A

#define LOCALE_IDEFAULTEBCDICCODEPAGE 0x00001012
#define LOCALE_IPAPERSIZE 0x0000100A
#define LOCALE_SENGCURRNAME 0x00001007
#define LOCALE_SNATIVECURRNAME 0x00001008
#define LOCALE_SYEARMONTH 0x00001006
#define LOCALE_SSORTNAME 0x00001013
#define LOCALE_IDIGITSUBSTITUTION 0x00001014

#define TIME_NOMINUTESORSECONDS 0x00000001
#define TIME_NOSECONDS 0x00000002
#define TIME_NOTIMEMARKER 0x00000004
#define TIME_FORCE24HOURFORMAT 0x00000008

#define DATE_SHORTDATE 0x00000001
#define DATE_LONGDATE 0x00000002
#define DATE_USE_ALT_CALENDAR 0x00000004
#define DATE_YEARMONTH 0x00000008
#define DATE_LTRREADING 0x00000010
#define DATE_RTLREADING 0x00000020

#define CAL_NOUSEROVERRIDE LOCALE_NOUSEROVERRIDE
#define CAL_USE_CP_ACP LOCALE_USE_CP_ACP
#define CAL_RETURN_NUMBER LOCALE_RETURN_NUMBER

#define CAL_ICALINTVALUE 0x00000001
#define CAL_SCALNAME 0x00000002
#define CAL_IYEAROFFSETRANGE 0x00000003
#define CAL_SERASTRING 0x00000004
#define CAL_SSHORTDATE 0x00000005
#define CAL_SLONGDATE 0x00000006
#define CAL_SDAYNAME1 0x00000007
#define CAL_SDAYNAME2 0x00000008
#define CAL_SDAYNAME3 0x00000009
#define CAL_SDAYNAME4 0x0000000a
#define CAL_SDAYNAME5 0x0000000b
#define CAL_SDAYNAME6 0x0000000c
#define CAL_SDAYNAME7 0x0000000d
#define CAL_SABBREVDAYNAME1 0x0000000e
#define CAL_SABBREVDAYNAME2 0x0000000f
#define CAL_SABBREVDAYNAME3 0x00000010
#define CAL_SABBREVDAYNAME4 0x00000011
#define CAL_SABBREVDAYNAME5 0x00000012
#define CAL_SABBREVDAYNAME6 0x00000013
#define CAL_SABBREVDAYNAME7 0x00000014
#define CAL_SMONTHNAME1 0x00000015
#define CAL_SMONTHNAME2 0x00000016
#define CAL_SMONTHNAME3 0x00000017
#define CAL_SMONTHNAME4 0x00000018
#define CAL_SMONTHNAME5 0x00000019
#define CAL_SMONTHNAME6 0x0000001a
#define CAL_SMONTHNAME7 0x0000001b
#define CAL_SMONTHNAME8 0x0000001c
#define CAL_SMONTHNAME9 0x0000001d
#define CAL_SMONTHNAME10 0x0000001e
#define CAL_SMONTHNAME11 0x0000001f
#define CAL_SMONTHNAME12 0x00000020
#define CAL_SMONTHNAME13 0x00000021
#define CAL_SABBREVMONTHNAME1 0x00000022
#define CAL_SABBREVMONTHNAME2 0x00000023
#define CAL_SABBREVMONTHNAME3 0x00000024
#define CAL_SABBREVMONTHNAME4 0x00000025
#define CAL_SABBREVMONTHNAME5 0x00000026
#define CAL_SABBREVMONTHNAME6 0x00000027
#define CAL_SABBREVMONTHNAME7 0x00000028
#define CAL_SABBREVMONTHNAME8 0x00000029
#define CAL_SABBREVMONTHNAME9 0x0000002a
#define CAL_SABBREVMONTHNAME10 0x0000002b
#define CAL_SABBREVMONTHNAME11 0x0000002c
#define CAL_SABBREVMONTHNAME12 0x0000002d
#define CAL_SABBREVMONTHNAME13 0x0000002e
#define CAL_SYEARMONTH 0x0000002f
#define CAL_ITWODIGITYEARMAX 0x00000030

#define ENUM_ALL_CALENDARS 0xffffffff

#define CAL_GREGORIAN 1
#define CAL_GREGORIAN_US 2
#define CAL_JAPAN 3
#define CAL_TAIWAN 4
#define CAL_KOREA 5
#define CAL_HIJRI 6
#define CAL_THAI 7
#define CAL_HEBREW 8
#define CAL_GREGORIAN_ME_FRENCH 9
#define CAL_GREGORIAN_ARABIC 10
#define CAL_GREGORIAN_XLIT_ENGLISH 11
#define CAL_GREGORIAN_XLIT_FRENCH 12
#if (_WIN32_WINNT >= 0x0600)
#define CAL_UMALQURA 23
#endif /* (_WIN32_WINNT >= 0x0600) */

#define LGRPID_WESTERN_EUROPE 0x0001
#define LGRPID_CENTRAL_EUROPE 0x0002
#define LGRPID_BALTIC 0x0003
#define LGRPID_GREEK 0x0004
#define LGRPID_CYRILLIC 0x0005
#define LGRPID_TURKISH 0x0006
#define LGRPID_JAPANESE 0x0007
#define LGRPID_KOREAN 0x0008
#define LGRPID_TRADITIONAL_CHINESE 0x0009
#define LGRPID_SIMPLIFIED_CHINESE 0x000a
#define LGRPID_THAI 0x000b
#define LGRPID_HEBREW 0x000c
#define LGRPID_ARABIC 0x000d
#define LGRPID_VIETNAMESE 0x000e
#define LGRPID_INDIC 0x000f
#define LGRPID_GEORGIAN 0x0010
#define LGRPID_ARMENIAN 0x0011
#define IS_HIGH_SURROGATE(c) (((c) & 0xFC00) == 0xD800)
#define IS_LOW_SURROGATE(c) (((c) & 0xFC00) == 0xDC00)
#define IS_SURROGATE_PAIR(hc,lc) (IS_HIGH_SURROGATE(hc) && IS_LOW_SURROGATE(lc))

  typedef DWORD LGRPID;
  typedef DWORD LCTYPE;
  typedef DWORD CALTYPE;
  typedef DWORD CALID;

  typedef struct _cpinfo {
    UINT MaxCharSize;
    BYTE DefaultChar[MAX_DEFAULTCHAR];
    BYTE LeadByte[MAX_LEADBYTES];
  } CPINFO,*LPCPINFO;

  typedef struct _cpinfoexA {
    UINT MaxCharSize;
    BYTE DefaultChar[MAX_DEFAULTCHAR];
    BYTE LeadByte[MAX_LEADBYTES];
    WCHAR UnicodeDefaultChar;
    UINT CodePage;
    CHAR CodePageName[MAX_PATH];
  } CPINFOEXA,*LPCPINFOEXA;

  typedef struct _cpinfoexW {
    UINT MaxCharSize;
    BYTE DefaultChar[MAX_DEFAULTCHAR];
    BYTE LeadByte[MAX_LEADBYTES];
    WCHAR UnicodeDefaultChar;
    UINT CodePage;
    WCHAR CodePageName[MAX_PATH];
  } CPINFOEXW,*LPCPINFOEXW;

  __MINGW_TYPEDEF_AW(CPINFOEX)
  __MINGW_TYPEDEF_AW(LPCPINFOEX)

  typedef struct _numberfmtA {
    UINT NumDigits;
    UINT LeadingZero;
    UINT Grouping;
    LPSTR lpDecimalSep;
    LPSTR lpThousandSep;
    UINT NegativeOrder;
  } NUMBERFMTA,*LPNUMBERFMTA;

  typedef struct _numberfmtW {
    UINT NumDigits;
    UINT LeadingZero;
    UINT Grouping;
    LPWSTR lpDecimalSep;
    LPWSTR lpThousandSep;
    UINT NegativeOrder;
  } NUMBERFMTW,*LPNUMBERFMTW;

  __MINGW_TYPEDEF_AW(NUMBERFMT)
  __MINGW_TYPEDEF_AW(LPNUMBERFMT)

  typedef struct _currencyfmtA {
    UINT NumDigits;
    UINT LeadingZero;
    UINT Grouping;
    LPSTR lpDecimalSep;
    LPSTR lpThousandSep;
    UINT NegativeOrder;
    UINT PositiveOrder;
    LPSTR lpCurrencySymbol;
  } CURRENCYFMTA,*LPCURRENCYFMTA;

  typedef struct _currencyfmtW {
    UINT NumDigits;
    UINT LeadingZero;
    UINT Grouping;
    LPWSTR lpDecimalSep;
    LPWSTR lpThousandSep;
    UINT NegativeOrder;
    UINT PositiveOrder;
    LPWSTR lpCurrencySymbol;
  } CURRENCYFMTW,*LPCURRENCYFMTW;

  __MINGW_TYPEDEF_AW(CURRENCYFMT)
  __MINGW_TYPEDEF_AW(LPCURRENCYFMT)

  enum SYSNLS_FUNCTION {
    COMPARE_STRING = 0x0001
  };

  typedef DWORD NLS_FUNCTION;

  typedef struct _nlsversioninfo{
    DWORD dwNLSVersionInfoSize;
    DWORD dwNLSVersion;
    DWORD dwDefinedVersion;
  } NLSVERSIONINFO,*LPNLSVERSIONINFO;

  typedef LONG GEOID;
  typedef DWORD GEOTYPE;
  typedef DWORD GEOCLASS;

#define GEOID_NOT_AVAILABLE -1

  enum SYSGEOTYPE {
    GEO_NATION = 0x0001,GEO_LATITUDE = 0x0002,GEO_LONGITUDE = 0x0003,GEO_ISO2 = 0x0004,GEO_ISO3 = 0x0005,GEO_RFC1766 = 0x0006,GEO_LCID = 0x0007,
    GEO_FRIENDLYNAME= 0x0008,GEO_OFFICIALNAME= 0x0009,GEO_TIMEZONES = 0x000A,GEO_OFFICIALLANGUAGES = 0x000B
  };

  enum SYSGEOCLASS {
    GEOCLASS_NATION = 16,GEOCLASS_REGION = 14
  };
  
  typedef enum  _NORM_FORM  {
  NormalizationOther   = 0,
  NormalizationC       = 0x1,
  NormalizationD       = 0x2,
  NormalizationKC      = 0x5,
  NormalizationKD      = 0x6 
} NORM_FORM;

  typedef WINBOOL (CALLBACK *LANGUAGEGROUP_ENUMPROCA)(LGRPID,LPSTR,LPSTR,DWORD,LONG_PTR);
  typedef WINBOOL (CALLBACK *LANGGROUPLOCALE_ENUMPROCA)(LGRPID,LCID,LPSTR,LONG_PTR);
  typedef WINBOOL (CALLBACK *UILANGUAGE_ENUMPROCA)(LPSTR,LONG_PTR);
  typedef WINBOOL (CALLBACK *LOCALE_ENUMPROCA)(LPSTR);
  typedef WINBOOL (CALLBACK *CODEPAGE_ENUMPROCA)(LPSTR);
  typedef WINBOOL (CALLBACK *DATEFMT_ENUMPROCA)(LPSTR);
  typedef WINBOOL (CALLBACK *DATEFMT_ENUMPROCEXA)(LPSTR,CALID);
  typedef WINBOOL (CALLBACK *TIMEFMT_ENUMPROCA)(LPSTR);
  typedef WINBOOL (CALLBACK *CALINFO_ENUMPROCA)(LPSTR);
  typedef WINBOOL (CALLBACK *CALINFO_ENUMPROCEXA)(LPSTR,CALID);
  typedef WINBOOL (CALLBACK *LANGUAGEGROUP_ENUMPROCW)(LGRPID,LPWSTR,LPWSTR,DWORD,LONG_PTR);
  typedef WINBOOL (CALLBACK *LANGGROUPLOCALE_ENUMPROCW)(LGRPID,LCID,LPWSTR,LONG_PTR);
  typedef WINBOOL (CALLBACK *UILANGUAGE_ENUMPROCW)(LPWSTR,LONG_PTR);
  typedef WINBOOL (CALLBACK *LOCALE_ENUMPROCW)(LPWSTR);
  typedef WINBOOL (CALLBACK *CODEPAGE_ENUMPROCW)(LPWSTR);
  typedef WINBOOL (CALLBACK *DATEFMT_ENUMPROCW)(LPWSTR);
  typedef WINBOOL (CALLBACK *DATEFMT_ENUMPROCEXW)(LPWSTR,CALID);
  typedef WINBOOL (CALLBACK *TIMEFMT_ENUMPROCW)(LPWSTR);
  typedef WINBOOL (CALLBACK *CALINFO_ENUMPROCW)(LPWSTR);
  typedef WINBOOL (CALLBACK *CALINFO_ENUMPROCEXW)(LPWSTR,CALID);
  typedef WINBOOL (CALLBACK *GEO_ENUMPROC)(GEOID);

#define LANGUAGEGROUP_ENUMPROC __MINGW_NAME_AW(LANGUAGEGROUP_ENUMPROC)
#define LANGGROUPLOCALE_ENUMPROC __MINGW_NAME_AW(LANGGROUPLOCALE_ENUMPROC)
#define UILANGUAGE_ENUMPROC __MINGW_NAME_AW(UILANGUAGE_ENUMPROC)
#define LOCALE_ENUMPROC __MINGW_NAME_AW(LOCALE_ENUMPROC)
#define CODEPAGE_ENUMPROC __MINGW_NAME_AW(CODEPAGE_ENUMPROC)
#define DATEFMT_ENUMPROC __MINGW_NAME_AW(DATEFMT_ENUMPROC)
#define DATEFMT_ENUMPROCEX __MINGW_NAME_AW(DATEFMT_ENUMPROCEX)
#define TIMEFMT_ENUMPROC __MINGW_NAME_AW(TIMEFMT_ENUMPROC)
#define CALINFO_ENUMPROC __MINGW_NAME_AW(CALINFO_ENUMPROC)
#define CALINFO_ENUMPROCEX __MINGW_NAME_AW(CALINFO_ENUMPROCEX)

#define GetCPInfoEx __MINGW_NAME_AW(GetCPInfoEx)
#define CompareString __MINGW_NAME_AW(CompareString)
#define LCMapString __MINGW_NAME_AW(LCMapString)
#define GetLocaleInfo __MINGW_NAME_AW(GetLocaleInfo)
#define SetLocaleInfo __MINGW_NAME_AW(SetLocaleInfo)
#define GetCalendarInfo __MINGW_NAME_AW(GetCalendarInfo)
#define SetCalendarInfo __MINGW_NAME_AW(SetCalendarInfo)
#define GetTimeFormat __MINGW_NAME_AW(GetTimeFormat)
#define GetDateFormat __MINGW_NAME_AW(GetDateFormat)
#define GetNumberFormat __MINGW_NAME_AW(GetNumberFormat)
#define GetCurrencyFormat __MINGW_NAME_AW(GetCurrencyFormat)
#define EnumCalendarInfo __MINGW_NAME_AW(EnumCalendarInfo)
#define EnumCalendarInfoEx __MINGW_NAME_AW(EnumCalendarInfoEx)
#define EnumTimeFormats __MINGW_NAME_AW(EnumTimeFormats)
#define EnumDateFormats __MINGW_NAME_AW(EnumDateFormats)
#define EnumDateFormatsEx __MINGW_NAME_AW(EnumDateFormatsEx)
#define GetGeoInfo __MINGW_NAME_AW(GetGeoInfo)
#define GetStringTypeEx __MINGW_NAME_AW(GetStringTypeEx)
#define FoldString __MINGW_NAME_AW(FoldString)
#define EnumSystemLanguageGroups __MINGW_NAME_AW(EnumSystemLanguageGroups)
#define EnumLanguageGroupLocales __MINGW_NAME_AW(EnumLanguageGroupLocales)
#define EnumUILanguages __MINGW_NAME_AW(EnumUILanguages)
#define EnumSystemLocales __MINGW_NAME_AW(EnumSystemLocales)
#define EnumSystemCodePages __MINGW_NAME_AW(EnumSystemCodePages)

  WINBASEAPI WINBOOL WINAPI IsValidCodePage(UINT CodePage);
  WINBASEAPI UINT WINAPI GetACP(void);
  WINBASEAPI UINT WINAPI GetOEMCP(void);
  WINBASEAPI WINBOOL WINAPI GetCPInfo(UINT CodePage,LPCPINFO lpCPInfo);
  WINBASEAPI WINBOOL WINAPI GetCPInfoExA(UINT CodePage,DWORD dwFlags,LPCPINFOEXA lpCPInfoEx);
  WINBASEAPI WINBOOL WINAPI GetCPInfoExW(UINT CodePage,DWORD dwFlags,LPCPINFOEXW lpCPInfoEx);
  WINBASEAPI WINBOOL WINAPI IsDBCSLeadByte(BYTE TestChar);
  WINBASEAPI WINBOOL WINAPI IsDBCSLeadByteEx(UINT CodePage,BYTE TestChar);
  WINBASEAPI int WINAPI MultiByteToWideChar(UINT CodePage,DWORD dwFlags,LPCSTR lpMultiByteStr,int cbMultiByte,LPWSTR lpWideCharStr,int cchWideChar);
  WINBASEAPI int WINAPI WideCharToMultiByte(UINT CodePage,DWORD dwFlags,LPCWSTR lpWideCharStr,int cchWideChar,LPSTR lpMultiByteStr,int cbMultiByte,LPCSTR lpDefaultChar,LPBOOL lpUsedDefaultChar);
  WINBASEAPI int WINAPI CompareStringA(LCID Locale,DWORD dwCmpFlags,LPCSTR lpString1,int cchCount1,LPCSTR lpString2,int cchCount2);
  WINBASEAPI int WINAPI CompareStringW(LCID Locale,DWORD dwCmpFlags,LPCWSTR lpString1,int cchCount1,LPCWSTR lpString2,int cchCount2);
  WINBASEAPI int WINAPI LCMapStringA(LCID Locale,DWORD dwMapFlags,LPCSTR lpSrcStr,int cchSrc,LPSTR lpDestStr,int cchDest);
  WINBASEAPI int WINAPI LCMapStringW(LCID Locale,DWORD dwMapFlags,LPCWSTR lpSrcStr,int cchSrc,LPWSTR lpDestStr,int cchDest);
  WINBASEAPI int WINAPI GetLocaleInfoA(LCID Locale,LCTYPE LCType,LPSTR lpLCData,int cchData);
  WINBASEAPI int WINAPI GetLocaleInfoW(LCID Locale,LCTYPE LCType,LPWSTR lpLCData,int cchData);
  WINBASEAPI WINBOOL WINAPI SetLocaleInfoA(LCID Locale,LCTYPE LCType,LPCSTR lpLCData);
  WINBASEAPI WINBOOL WINAPI SetLocaleInfoW(LCID Locale,LCTYPE LCType,LPCWSTR lpLCData);
  WINBASEAPI int WINAPI GetCalendarInfoA(LCID Locale,CALID Calendar,CALTYPE CalType,LPSTR lpCalData,int cchData,LPDWORD lpValue);
  WINBASEAPI int WINAPI GetCalendarInfoW(LCID Locale,CALID Calendar,CALTYPE CalType,LPWSTR lpCalData,int cchData,LPDWORD lpValue);
  WINBASEAPI WINBOOL WINAPI SetCalendarInfoA(LCID Locale,CALID Calendar,CALTYPE CalType,LPCSTR lpCalData);
  WINBASEAPI WINBOOL WINAPI SetCalendarInfoW(LCID Locale,CALID Calendar,CALTYPE CalType,LPCWSTR lpCalData);
  WINBASEAPI int WINAPI GetTimeFormatA(LCID Locale,DWORD dwFlags,CONST SYSTEMTIME *lpTime,LPCSTR lpFormat,LPSTR lpTimeStr,int cchTime);
  WINBASEAPI int WINAPI GetTimeFormatW(LCID Locale,DWORD dwFlags,CONST SYSTEMTIME *lpTime,LPCWSTR lpFormat,LPWSTR lpTimeStr,int cchTime);
  WINBASEAPI int WINAPI GetDateFormatA(LCID Locale,DWORD dwFlags,CONST SYSTEMTIME *lpDate,LPCSTR lpFormat,LPSTR lpDateStr,int cchDate);
  WINBASEAPI int WINAPI GetDateFormatW(LCID Locale,DWORD dwFlags,CONST SYSTEMTIME *lpDate,LPCWSTR lpFormat,LPWSTR lpDateStr,int cchDate);
  WINBASEAPI int WINAPI GetNumberFormatA(LCID Locale,DWORD dwFlags,LPCSTR lpValue,CONST NUMBERFMTA *lpFormat,LPSTR lpNumberStr,int cchNumber);
  WINBASEAPI int WINAPI GetNumberFormatW(LCID Locale,DWORD dwFlags,LPCWSTR lpValue,CONST NUMBERFMTW *lpFormat,LPWSTR lpNumberStr,int cchNumber);
  WINBASEAPI int WINAPI GetCurrencyFormatA(LCID Locale,DWORD dwFlags,LPCSTR lpValue,CONST CURRENCYFMTA *lpFormat,LPSTR lpCurrencyStr,int cchCurrency);
  WINBASEAPI int WINAPI GetCurrencyFormatW(LCID Locale,DWORD dwFlags,LPCWSTR lpValue,CONST CURRENCYFMTW *lpFormat,LPWSTR lpCurrencyStr,int cchCurrency);
  WINBASEAPI WINBOOL WINAPI EnumCalendarInfoA(CALINFO_ENUMPROCA lpCalInfoEnumProc,LCID Locale,CALID Calendar,CALTYPE CalType);
  WINBASEAPI WINBOOL WINAPI EnumCalendarInfoW(CALINFO_ENUMPROCW lpCalInfoEnumProc,LCID Locale,CALID Calendar,CALTYPE CalType);
  WINBASEAPI WINBOOL WINAPI EnumCalendarInfoExA(CALINFO_ENUMPROCEXA lpCalInfoEnumProcEx,LCID Locale,CALID Calendar,CALTYPE CalType);
  WINBASEAPI WINBOOL WINAPI EnumCalendarInfoExW(CALINFO_ENUMPROCEXW lpCalInfoEnumProcEx,LCID Locale,CALID Calendar,CALTYPE CalType);
  WINBASEAPI WINBOOL WINAPI EnumTimeFormatsA(TIMEFMT_ENUMPROCA lpTimeFmtEnumProc,LCID Locale,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumTimeFormatsW(TIMEFMT_ENUMPROCW lpTimeFmtEnumProc,LCID Locale,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumDateFormatsA(DATEFMT_ENUMPROCA lpDateFmtEnumProc,LCID Locale,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumDateFormatsW(DATEFMT_ENUMPROCW lpDateFmtEnumProc,LCID Locale,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumDateFormatsExA(DATEFMT_ENUMPROCEXA lpDateFmtEnumProcEx,LCID Locale,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumDateFormatsExW(DATEFMT_ENUMPROCEXW lpDateFmtEnumProcEx,LCID Locale,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI IsValidLanguageGroup(LGRPID LanguageGroup,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI GetNLSVersion(NLS_FUNCTION Function,LCID Locale,LPNLSVERSIONINFO lpVersionInformation);
  WINBASEAPI WINBOOL WINAPI IsNLSDefinedString(NLS_FUNCTION Function,DWORD dwFlags,LPNLSVERSIONINFO lpVersionInformation,LPCWSTR lpString,INT cchStr);
  WINBASEAPI WINBOOL WINAPI IsValidLocale(LCID Locale,DWORD dwFlags);
  WINBASEAPI int WINAPI GetGeoInfoA(GEOID Location,GEOTYPE GeoType,LPSTR lpGeoData,int cchData,LANGID LangId);
  WINBASEAPI int WINAPI GetGeoInfoW(GEOID Location,GEOTYPE GeoType,LPWSTR lpGeoData,int cchData,LANGID LangId);
  WINBASEAPI WINBOOL WINAPI EnumSystemGeoID(GEOCLASS GeoClass,GEOID ParentGeoId,GEO_ENUMPROC lpGeoEnumProc);
  WINBASEAPI GEOID WINAPI GetUserGeoID(GEOCLASS GeoClass);
  WINBASEAPI WINBOOL WINAPI SetUserGeoID(GEOID GeoId);
  WINBASEAPI LCID WINAPI ConvertDefaultLocale(LCID Locale);
  WINBASEAPI LCID WINAPI GetThreadLocale(void);
  WINBASEAPI WINBOOL WINAPI SetThreadLocale(LCID Locale);
  WINBASEAPI LANGID WINAPI GetSystemDefaultUILanguage(void);
  WINBASEAPI LANGID WINAPI GetUserDefaultUILanguage(void);
  WINBASEAPI LANGID WINAPI GetSystemDefaultLangID(void);
  WINBASEAPI LANGID WINAPI GetUserDefaultLangID(void);
  WINBASEAPI LCID WINAPI GetSystemDefaultLCID(void);
  WINBASEAPI LCID WINAPI GetUserDefaultLCID(void);
  WINBASEAPI WINBOOL WINAPI GetStringTypeExA(LCID Locale,DWORD dwInfoType,LPCSTR lpSrcStr,int cchSrc,LPWORD lpCharType);
  WINBASEAPI WINBOOL WINAPI GetStringTypeExW(LCID Locale,DWORD dwInfoType,LPCWSTR lpSrcStr,int cchSrc,LPWORD lpCharType);
  WINBASEAPI WINBOOL WINAPI GetStringTypeA(LCID Locale,DWORD dwInfoType,LPCSTR lpSrcStr,int cchSrc,LPWORD lpCharType);
  WINBASEAPI WINBOOL WINAPI GetStringTypeW(DWORD dwInfoType,LPCWSTR lpSrcStr,int cchSrc,LPWORD lpCharType);
  WINBASEAPI int WINAPI FoldStringA(DWORD dwMapFlags,LPCSTR lpSrcStr,int cchSrc,LPSTR lpDestStr,int cchDest);
  WINBASEAPI int WINAPI FoldStringW(DWORD dwMapFlags,LPCWSTR lpSrcStr,int cchSrc,LPWSTR lpDestStr,int cchDest);
  WINBASEAPI WINBOOL WINAPI EnumSystemLanguageGroupsA(LANGUAGEGROUP_ENUMPROCA lpLanguageGroupEnumProc,DWORD dwFlags,LONG_PTR lParam);
  WINBASEAPI WINBOOL WINAPI EnumSystemLanguageGroupsW(LANGUAGEGROUP_ENUMPROCW lpLanguageGroupEnumProc,DWORD dwFlags,LONG_PTR lParam);
  WINBASEAPI WINBOOL WINAPI EnumLanguageGroupLocalesA(LANGGROUPLOCALE_ENUMPROCA lpLangGroupLocaleEnumProc,LGRPID LanguageGroup,DWORD dwFlags,LONG_PTR lParam);
  WINBASEAPI WINBOOL WINAPI EnumLanguageGroupLocalesW(LANGGROUPLOCALE_ENUMPROCW lpLangGroupLocaleEnumProc,LGRPID LanguageGroup,DWORD dwFlags,LONG_PTR lParam);
  WINBASEAPI WINBOOL WINAPI EnumUILanguagesA(UILANGUAGE_ENUMPROCA lpUILanguageEnumProc,DWORD dwFlags,LONG_PTR lParam);
  WINBASEAPI WINBOOL WINAPI EnumUILanguagesW(UILANGUAGE_ENUMPROCW lpUILanguageEnumProc,DWORD dwFlags,LONG_PTR lParam);
  WINBASEAPI WINBOOL WINAPI EnumSystemLocalesA(LOCALE_ENUMPROCA lpLocaleEnumProc,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumSystemLocalesW(LOCALE_ENUMPROCW lpLocaleEnumProc,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumSystemCodePagesA(CODEPAGE_ENUMPROCA lpCodePageEnumProc,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI EnumSystemCodePagesW(CODEPAGE_ENUMPROCW lpCodePageEnumProc,DWORD dwFlags);
  WINBASEAPI WINBOOL WINAPI IsNormalizedString(NORM_FORM NormForm,LPCWSTR lpString,int cwLength);
  WINBASEAPI int WINAPI NormalizeString(NORM_FORM NormForm,LPCWSTR lpSrcString,int cwSrcLength,LPWSTR lpDstString,int cwDstLength);
  WINBASEAPI int WINAPI IdnToAscii(DWORD dwFlags,LPCWSTR lpUnicodeCharStr,int cchUnicodeChar,LPWSTR lpASCIICharStr,int cchASCIIChar);
  WINBASEAPI int WINAPI IdnToNameprepUnicode(DWORD dwFlags,LPCWSTR lpUnicodeCharStr,int cchUnicodeChar,LPWSTR lpNameprepCharStr,int cchNameprepChar);
  WINBASEAPI int WINAPI IdnToUnicode(DWORD dwFlags,LPCWSTR lpASCIICharStr,int cchASCIIChar,LPWSTR lpUnicodeCharStr,int cchUnicodeChar);

#if (_WIN32_WINNT >= 0x0600)
WINBASEAPI int WINAPI CompareStringEx(
  LPCWSTR lpLocaleName,
  DWORD dwCmpFlags,
  LPCWSTR lpString1,
  int cchCount1,
  LPCWSTR lpString2,
  int cchCount2,
  LPNLSVERSIONINFO lpVersionInformation,
  LPVOID lpReserved,
  LPARAM lParam
);

WINBASEAPI int WINAPI CompareStringOrdinal(
  LPCWSTR lpString1,
  int cchCount1,
  LPCWSTR lpString2,
  int cchCount2,
  WINBOOL bIgnoreCase
);

typedef WINBOOL (CALLBACK *CALINFO_ENUMPROCEXEX)(
  LPWSTR lpCalendarInfoString,
  CALID Calendar,
  LPWSTR lpReserved,
  LPARAM lParam
);

typedef WINBOOL (CALLBACK *DATEFMT_ENUMPROCEXEX)(
  LPWSTR lpDateFormatString,
  CALID CalendarID,
  LPARAM lParam
);

WINBASEAPI WINBOOL int WINAPI EnumCalendarInfoExEx(
  CALINFO_ENUMPROCEXEX pCalInfoEnumProcExEx,
  LPCWSTR lpLocaleName,
  CALID Calendar,
  LPCWSTR lpReserved,
  CALTYPE CalType,
  LPARAM lParam
);

WINBASEAPI WINBOOL WINAPI EnumDateFormatsExEx(
  DATEFMT_ENUMPROCEXEX lpDateFmtEnumProcExEx,
  LPCWSTR lpLocaleName,
  DWORD dwFlags,
  LPARAM lParam
);

typedef WINBOOL (CALLBACK *LOCALE_ENUMPROCEX)(
  LPWSTR lpLocaleString,
  DWORD dwFlags,
  LPARAM lParam
);

WINBASEAPI WINBOOL WINAPI EnumSystemLocalesEx(
  LOCALE_ENUMPROCEX lpLocaleEnumProcEx,
  DWORD dwFlags,
  LPARAM lParam,
  LPVOID lpReserved
);

typedef WINBOOL (CALLBACK *TIMEFMT_ENUMPROCEX)(
  LPWSTR lpTimeFormatString,
  LPARAM lParam
);

WINBASEAPI WINBOOL WINAPI EnumTimeFormatsEx(
  TIMEFMT_ENUMPROCEX lpTimeFmtEnumProcEx,
  LPCWSTR lpLocaleName,
  DWORD dwFlags,
  LPARAM lParam
);

typedef struct _FILEMUIINFO {
  DWORD dwSize;
  DWORD dwVersion;
  DWORD dwFileType;
  BYTE  pChecksum[16];
  BYTE  pServiceChecksum[16];
  DWORD dwLanguageNameOffset;
  DWORD dwTypeIDMainSize;
  DWORD dwTypeIDMainOffset;
  DWORD dwTypeNameMainOffset;
  DWORD dwTypeIDMUISize;
  DWORD dwTypeIDMUIOffset;
  DWORD dwTypeNameMUIOffset;
  BYTE  abBuffer[8];
} FILEMUIINFO, *PFILEMUIINFO;

WINBASEAPI int WINAPI FindNLSString(
  LCID Locale,
  DWORD dwFindNLSStringFlags,
  LPCWSTR lpStringSource,
  int cchSource,
  LPCWSTR lpStringValue,
  int cchValue,
  LPINT pcchFound
);

WINBASEAPI int WINAPI FindNLSStringEx(
  LPCWSTR lpLocaleName,
  DWORD dwFindNLSStringFlags,
  LPCWSTR lpStringSource,
  int cchSource,
  LPCWSTR lpStringValue,
  int cchValue,
  LPINT pcchFound,
  LPNLSVERSIONINFO lpVersionInformation,
  LPVOID lpReserved,
  LPARAM lParam
);

#endif /* (_WIN32_WINNT >= 0x0600) */
#endif

#ifdef __cplusplus
}
#endif
#endif
