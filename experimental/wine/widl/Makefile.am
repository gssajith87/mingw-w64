AM_CFLAGS=-I$(top_srcdir)/include
	
bin_PROGRAMS = widl

widl_SOURCES = \
  src/client.c \
  src/expr.c \
  src/hash.c \
  src/header.c \
  src/parser.tab.c \
  src/parser.yy.c \
  src/port/port.c \
  src/proxy.c \
  src/server.c \
  src/typegen.c \
  src/typelib.c \
  src/typetree.c \
  src/utils.c \
  src/widl.c \
  src/write_msft.c \
  src/wpp/ppl.yy.c \
  src/wpp/ppy.tab.c \
  src/wpp/preproc.c \
  src/wpp/wpp.c

widl_CFLAGS = -O3 -g -std=gnu99 -Wall -Wextra -Wshadow -Wformat -Wpacked -Wredundant-decls -Winline -pedantic -Wno-pedantic-ms-format -Wmissing-declarations -Wredundant-decls -Wimplicit-function-declaration -Wmissing-noreturn -Wmissing-prototypes -Wstrict-aliasing=2

DISTCHECK_CONFIGURE_FLAGS = --host=$(host_triplet)

