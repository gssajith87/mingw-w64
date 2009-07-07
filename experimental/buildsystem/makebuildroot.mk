#!/usr/bin/env make

#
# Toolchain bootstrapping build system, ver. N + 1
#
# This exists as an attempt to unify building inside and outside of buildbot.
# Each step of the build system has an alias target that can be called
# externally; all steps _up_to_ the target will be executed.  If no target is
# specified, by default it will build a binary tarball (with matching source
# tarball) for 64bit Windows.
#
# The goal is to be able to replace makebuildroot.sh with all its options
# available.
#

all:: # default target

########################################
# Configurable variables
########################################
TARGET_ARCH ?= x86_64-w64-mingw32
HOST_ARCH ?=
BINUTILS_UPDATE ?= # force update binutils
BINUTILS_CONFIG_EXTRA_ARGS ?=
GCC_CONFIG_EXTRA_ARGS ?= --enable-fully-dynamic-string --disable-multilib
GCC_BRANCH ?= trunk # "tags/gcc_4_4_0_release" or "branches/gcc-4_4-branch"
GCC_REVISION ?= head # revision id "146782" or date "2009-04-25"
GCC_UPDATE ?= # force update gcc
GMP_VERSION ?= 4.3.0 # GMP release version
MPFR_VERSION ?= 2.4.1 # MPFR release version
MINGW_BRANCH ?= trunk # ... not that we have any!
MINGW_REVISION ?= HEAD
MINGW_UPDATE ?= # force update mingw
MINGW_CONFIG_EXTRA_ARGS ?=
SRC_ARCHIVE ?= mingw-w64-src.tar.bz2
BIN_ARCHIVE ?= mingw-w64-bin_$(shell uname -s).tar.bz2

########################################
# Configure
########################################
ifeq (,$(filter-out x86_64-%,$(TARGET_ARCH)))
  MINGW_LIBDIR := lib64
else ifeq (,$(filter-out i386-% i486-% i586-% i686-%,$(TARGET_ARCH)))
  MIGNW_LIBDIR := lib
else
  $(error Unknown CPU for target arch $(TARGET_ARCH))
endif

# the type of _host_ to run on (n.b. not build)
HOST_TYPE := posix
ifneq (,$(filter MINGW%,$(shell uname -s)))
  HOST_TYPE := windows
endif
ifneq (,${HOST_ARCH})
  HOST_TYPE := posix
  BINUTILS_CONFIG_HOST_ARGS = --host=${HOST_ARCH}
  GCC_CONFIG_HOST_ARGS = --host=${HOST_ARCH}
endif
ifneq (,$(filter %-mingw32,${HOST_ARCH}))
  HOST_TYPE := windows
endif


########################################
# Pull mingw-w64-specific patches
########################################

patch-pull: \
    src/patches/.patches.pull.marker

src/patches/.patches.pull.marker: \
    src/patches/.mkdir.marker
	cd $(dir $@) && \
	svn co --non-interactive --no-auth-cache \
	       https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/experimental/patches/ .
	@touch $@


########################################
# Pull binutils
########################################

binutils-pull: \
    src/binutils/.binutils.pull.marker

src/binutils/.binutils.pull.marker: \
    src/binutils/.mkdir.marker
	### XXX Mook: todo: specify revision
ifeq (,$(BINUTILS_UPDATE))
	cd $(dir $@) && \
	cvs -d ":pserver:anoncvs@sourceware.org:/cvs/src" -z3 \
	    checkout -d . -N binutils
	@touch $@
else
	cd $(dir $@) && \
	cvs -d ":pserver:anoncvs@sourceware.org:/cvs/src" -z3 \
	    update
	@touch $@
.PHONY: src/binutils/.binutils.pull.marker
endif

########################################
# Pull GCC
########################################
## find a gcc revision (r???) and a stamp for the file name $(GCC_REV_STAMP)
ifneq (,$(findstring -,$(GCC_REVISION)))
  # GCC_REVISION is a date
  GCC_REV_STAMP := d$(subst -,,$(GCC_REVISION))
  GCC_REVISION := $(shell TZ=Z svn log --non-interactive --no-auth-cache \
                                       -r "{$(subst -,,$(GCC_REVISION))T0000Z}:{$(subst -,,$(GCC_REVISION))T0030Z}" \
                                       svn://gcc.gnu.org/svn/gcc/trunk | \
                          grep gccadmin | \
                          grep $(GCC_REVISION) | \
                          cut -d ' ' -f 1)
  GCC_REVISION := $(subst r,,$(GCC_REVISION))
else ifeq (_,$(if $(GCC_REVISION),,false)_$(strip \
              $(subst 0,, $(subst 1,, $(subst 2,, \
              $(subst 3,, $(subst 4,, $(subst 5,, \
              $(subst 6,, $(subst 7,, $(subst 8,, \
              $(subst 9,, $(subst 0,, $(GCC_REVISION) )))))))))))))
  # GCC_REVISION is a number
  GCC_REVISION := $(GCC_REVISION)
  GCC_REV_STAMP := r$(GCC_REVISION)
else
  # GCC_REVISION is some opaque string (e.g. "head")
  GCC_REV_STAMP := r$(GCC_REVISION)
endif # GCC revision

gcc-pull: \
    src/gcc/gcc/.gcc.pull.marker

src/gcc/gcc/.gcc.pull.marker: \
    src/gcc/gcc/.mkdir.marker
	cd $(dir $@) && \
	svn co --non-interactive --no-auth-cache --revision $(GCC_REVISION) \
	       svn://gcc.gnu.org/svn/gcc/$(strip $(GCC_BRANCH))/ .
	@touch $@

  ifneq (,$(GCC_UPDATE))
.PHONY: src/gcc/gcc/.gcc.pull.marker
  endif

########################################
# Download gmp
########################################

gmp-download: \
    src/gmp.tar.bz2

src/gmp.tar.bz2: \
    src/.mkdir.marker
	wget -O $@ ftp://ftp.gnu.org/gnu/gmp/gmp-$(strip $(GMP_VERSION)).tar.bz2

########################################
# Extract gmp
########################################

gmp-extract: \
    src/gcc/.gmp.extract.marker

src/gcc/.gmp.extract.marker: \
    src/gmp.tar.bz2
	tar -C $(dir $@) -xjvf $<
	mv $(dir $@)/gmp-$(strip $(GMP_VERSION)) $(dir $@)/gcc/gmp
	@touch $@

########################################
# Execute autoconf for gmp
########################################

gmp-autoconf: \
    src/gcc/gcc/gmp/configure

src/gcc/gcc/gmp/configure: \
    src/gcc/.gmp.extract.marker
	cd $(dir $@) && \
	autoconf

########################################
# Download mpfr
########################################

mpfr-download: \
    src/mpfr.tar.bz2

src/mpfr.tar.bz2: \
    src/.mkdir.marker
	wget -O $@ http://www.mpfr.org/mpfr-current/mpfr-$(strip $(MPFR_VERSION)).tar.bz2

########################################
# Extract mpfr
########################################

mpfr-extract: \
    src/gcc/.mpfr.extract.marker

src/gcc/.mpfr.extract.marker: \
    src/mpfr.tar.bz2
	tar -C $(dir $@) -xjvf $<
	mv $(dir $@)/mpfr-$(strip $(MPFR_VERSION)) $(dir $@)/gcc/mpfr
	@touch $@

########################################
# Pull mingw
########################################

mingw-pull: \
    src/mingw/.mingw.pull.marker

src/mingw/.mingw.pull.marker: \
    src/mingw/.mkdir.marker
	svn checkout --non-interactive --no-auth-cache --revision $(MINGW_REVISION) \
	    https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/$(strip $(MINGW_BRANCH))/ \
	    $(dir $@)
	@touch $@

  ifneq (,$(MINGW_UPDATE))
.PHONY: src/mingw/.mingw.pull.marker
  endif

## XXX Mook: stamp the source with the revision used

########################################
# Create source tarball
########################################

src-archive:  $(SRC_ARCHIVE)

ifeq (,$(wildcard $(SRC_ARCHIVE)))
$(SRC_ARCHIVE): \
    src/binutils/.binutils.pull.marker \
    src/gcc/gcc/.gcc.pull.marker \
    src/gcc/gcc/gmp/configure \
    src/gcc/.mpfr.extract.marker \
    src/mingw/.mingw.pull.marker
endif

$(SRC_ARCHIVE):
	tar cjf $@ --owner 0 --group 0 --checkpoint --exclude=.svn --exclude=.*.marker \
            --exclude=CVS --exclude=gmp.tar.bz2 --exclude=mpfr.tar.bz2 -C src .

########################################
# Extract source tarball
########################################
src-extract:: \
    build/.extract.marker

build/.extract.marker: \
    $(SRC_ARCHIVE)
	-mkdir -p $(dir $@)
	tar -C $(dir $@) -xvjpf $<
	@touch $@

build/.root.init.marker: \
    build/root/${TARGET_ARCH}/.mkdir.marker \
    build/.extract.marker
ifneq (,$(filter MINGW%,$(shell uname -s)))
	test -e build/root/mingw  || \
	  junction build/root/mingw "build/root/${TARGET_ARCH}"
	test -e build/root/mingw
else
	test -h build/root/mingw  || \
	  ln -s "${TARGET_ARCH}" build/root/mingw
	test -h build/root/mingw
endif
	@touch $@

########################################
# Install mingw-w64 headers
########################################
headers-install: \
    build/root/mingw/.headers.install.marker

build/root/mingw/.headers.install.marker: \
    build/.root.init.marker \
    build/root/$(TARGET_ARCH)/include/.mkdir.marker
	tar cf - --exclude=.svn -C build/mingw/mingw-w64-headers/include . | \
	  tar xpvf - -C build/root/$(TARGET_ARCH)/include
	@touch $@

########################################
# Configure binutils
########################################
binutils-configure: \
    build/binutils/obj/.config.marker

build/binutils/obj/.config.marker: \
    build/root/mingw/.headers.install.marker\
    build/binutils/obj/.mkdir.marker \
    build/.root.init.marker
	cd $(dir $@) && \
	../src/configure --target=$(TARGET_ARCH) \
	                 $(BINUTILS_CONFIG_HOST_ARGS) \
	                 --prefix=$(CURDIR)/build/root \
	                 --with-sysroot=$(CURDIR)/build/root \
	                 $(BINUTILS_CONFIG_EXTRA_ARGS)
	@touch $@

########################################
# Compile binutils
########################################
binutils-compile: \
    build/binutils/obj/.compile.marker

build/binutils/obj/.compile.marker: \
    build/binutils/obj/.config.marker
	make -C $(dir $@)
	@touch $@

########################################
# Install binutils
########################################
binutils-install: \
    build/binutils/obj/.install.marker

build/binutils/obj/.install.marker: \
    build/binutils/obj/.compile.marker
	make -C $(dir $@) install
	@touch $@

########################################
# GCC cross compiling support - winsup
########################################
gcc-winsup: \
    build/gcc/gcc/.winsup.marker

build/gcc/gcc/.winsup.marker: \
    build/.extract.marker \
    build/.root.init.marker
ifneq (,$(filter MINGW%,$(shell uname -s)))
	test -e build/gcc/gcc/winsup  || \
	  junction build/gcc/gcc/winsup "build/root"
	test -e build/gcc/gcc/winsup
else
	test -h build/gcc/gcc/winsup  || \
	  ln -s "../../root" build/gcc/gcc/winsup
	test -h build/gcc/gcc/winsup
endif
	@touch $@

########################################
# Configure GCC
########################################
gcc-configure: \
    build/gcc/obj/.config.marker

ifneq (,$(filter %-mingw32,${HOST_ARCH}))
build/gcc/obj/.config.marker: \
    build/gcc/gcc/.winsup.marker
endif

build/gcc/obj/.config.marker: \
    build/gcc/obj/.mkdir.marker \
    build/binutils/obj/.install.marker \
    build/.root.init.marker
	cd $(dir $@) && \
	../gcc/configure --target=$(TARGET_ARCH) \
	                 $(GCC_CONFIG_HOST_ARGS) \
	                 --prefix=$(CURDIR)/build/root \
	                 --with-sysroot=$(CURDIR)/build/root \
	                 --enable-languages=all,obj-c++ \
	                 $(GCC_CONFIG_EXTRA_ARGS)
	@touch $@

########################################
# Compile GCC stage 1
########################################
gcc-bootstrap-compile: \
    build/gcc/obj/.bootstrap.compile.marker

build/gcc/obj/.bootstrap.compile.marker: \
    build/gcc/obj/.config.marker \
    build/root/mingw/.headers.install.marker
	found_asm=yes make -C $(dir $@) all-gcc
	@touch $@

########################################
# Install GCC stage 1
########################################
gcc-bootstrap-install: \
    build/gcc/obj/.bootstrap.install.marker

build/gcc/obj/.bootstrap.install.marker: \
    build/gcc/obj/.bootstrap.compile.marker
	make -C $(dir $@) install-gcc
	@touch $@

########################################
# Configure mingw-w64 CRT
########################################
crt-configure: \
    build/mingw/obj/.config.marker

build/mingw/obj/.config.marker: \
    build/gcc/obj/.bootstrap.install.marker \
    build/mingw/obj/.mkdir.marker
	cd $(dir $@) && \
	PATH=$(realpath build/root/bin):$$PATH \
	../mingw-w64-crt/configure --host=$(TARGET_ARCH) \
	                           --prefix=$(CURDIR)/build/root \
	                           --with-sysroot=$(CURDIR)/build/root \
	                           $(MINGW_CONFIG_EXTRA_ARGS)
	@touch $@

########################################
# Compile mingw-w64 CRT
########################################
crt-compile: \
    build/mingw/obj/.compile.marker

build/mingw/obj/.compile.marker: \
    build/mingw/obj/.config.marker
	PATH=$(realpath build/root/bin):$$PATH \
	make -C $(dir $@)
	@touch $@

########################################
# Install mingw-w64 CRT
########################################
crt-install: \
    build/mingw/obj/.install.marker

build/mingw/obj/.install.marker: \
    build/mingw/obj/.compile.marker
	PATH=$(realpath build/root/bin):$$PATH \
	make -C $(dir $@) install
	@touch $@

########################################
# Compile full GCC
########################################
gcc-compile: \
    build/gcc/obj/.compile.marker \
    build/mingw/obj/.install.marker

build/gcc/obj/.compile.marker: \
    build/gcc/obj/.config.marker \
    build/mingw/obj/.install.marker
	PATH=$(realpath build/root/bin):$$PATH \
	make -C $(dir $@)
	@touch $@

########################################
# Install full GCC
########################################
gcc-install: \
    build/gcc/obj/.install.marker

build/gcc/obj/.install.marker: \
    build/gcc/obj/.compile.marker
	PATH=$(realpath build/root/bin):$$PATH \
	make -C $(dir $@) install
	@touch $@

########################################
# Create release tarball
########################################
release-archive: \
    $(BIN_ARCHIVE)

$(BIN_ARCHIVE): \
    build/gcc/obj/.install.marker
ifeq (windows,$(HOST_TYPE))
	cd build/root && \
	zip -r -9 ../../$(patsubst %.tar.bz2,%.zip,$(BIN_ARCHIVE)) \
	     . -x .*.marker *.*.marker
else
	tar cjf $(BIN_ARCHIVE) -C build/root --owner 0 --group 0 --checkpoint \
	    --exclude=CVS --exclude=.svn --exclude=.*.marker \
            .
endif

########################################
# Helper targets
########################################

%/.mkdir.marker:
	-mkdir -p $(dir $@)
	@touch -d 1970-01-02 $@

help::
	@echo Available targets:
	@echo -e $(foreach t,all $(TARGETS) $@,\\t$(t)\\n)

all:: \
  $(BIN_ARCHIVE)

TARGETS := \
  patch-pull \
  binutils-pull \
  gcc-pull \
  gmp-download \
  gmp-extract \
  gmp-autoconf \
  mpfr-download \
  mpfr-extract \
  mingw-pull \
  src-archive \
  src-extract \
  binutils-configure \
  binutils-compile \
  binutils-install \
  gcc-configure \
  gcc-bootstrap-compile \
  gcc-bootstrap-install \
  headers-install \
  crt-configure \
  crt-compile \
  crt-install \
  gcc-compile \
  gcc-install \
  release-archive \
  $(NULL)


.PHONY: \
  all \
  $(TARGETS) \
  help \
  $(NULL)
