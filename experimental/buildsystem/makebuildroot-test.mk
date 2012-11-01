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
### TODO:
### Add clean-foo targets.
### Add GDB buildstep.
### Add XZ Compressed tarballs.
### Add Some checks for required installed tools before starting.

all:: # default target

########################################
# Build configurable variables
########################################
# TARGET_ARCH - Toolchain default target arch
# MAKE_OPTS - pass -j4 to make gcc/binutils build faster (No longer needed,
#             just use -jN on top make process
#
TARGET_ARCH ?= x86_64-w64-mingw32
BUILD_ARCH ?=
HOST_ARCH ?= ${BUILD_ARCH}
MAKE_OPTS ?=
BUILD_DIR ?= build

########################################
# Makefile output options
########################################
SRC_ARCHIVE ?= mingw-w64-src.tar.bz2
BIN_ARCHIVE ?= mingw-w64-bin_$(shell uname -s).tar.bz2

########################################
# Y/N options
########################################
# ENABLE_MULTILIB - Set to Y to use Multi-lib
# GCC_ADA - Set to Y to build ADA
# GCC_CPP - C++ support
# GCC_FORTRAN - Fortran support
# GCC_OBJC - Objective C support
# GCC_JAVA - Java support
ENABLE_MULTILIB ?= Y
GCC_ADA ?= Y
GCC_CPP ?= Y
GCC_FORTRAN ?= Y
GCC_OBJC ?= Y
GCC_JAVA ?= N
USE_WINPTHREADS ?= Y

########################################
# Version number variables
########################################
GMP_VERSION ?= 5.0.2
MPFR_VERSION ?= 3.1.0
MPC_VERSION ?= 0.8.2
PPL_VERSION ?= 0.11
CLOOG_VERSION ?= 0.17.0
ISL_VERSION ?= 0.10
OSL_VERSION ?= 0.8.4
PIPLIB_VERSION ?= 1.4.0
MINGW_BRANCH ?= trunk
MINGW_REVISION ?= HEAD
WINPTHREADS_REVISION ?= HEAD
GCC_BRANCH ?= trunk # "tags/gcc_4_4_0_release" or "branches/gcc-4_4-branch"
GCC_REVISION ?= head # revision id "146782" or date "2009-04-25"

########################################
# Download URLs
########################################
PTHREADS_CVS_PULL ?= :pserver:anoncvs:anoncvs@sourceware.org:/cvs/pthreads-win32
PTHREADS_CVS_DATE ?= '5/11/2010'

########################################
# Configure options
########################################
BINUTILS_CONFIG_EXTRA_ARGS ?=
GCC_CONFIG_EXTRA_ARGS ?=
PTHREADS_MAKE_ARGS ?= clean GC
MINGW_CONFIG_EXTRA_ARGS ?=

########################################
# Update sources?
########################################
ALL_UPDATE ?= # force update everything
BINUTILS_UPDATE ?= ${ALL_UPDATE} # force update binutils
GCC_UPDATE ?= ${ALL_UPDATE} # force update gcc
MINGW_UPDATE ?= ${ALL_UPDATE} # force update mingw
PTHREADS_UPDATE ?= ${ALL_UPDATE}

#########################################
# DO NOT EDIT PASS THIS LINE
#########################################

########################################
# Multilib helper
########################################
BINUTILS_CONFIG_EXTRA_ARGS_MULTI_Y := --enable-targets=x86_64-w64-mingw32,i686-w64-mingw32
BINUTILS_CONFIG_EXTRA_ARGS_MULTI_N :=
GCC_CONFIG_EXTRA_ARGS_MULTI_Y := --enable-multilib
GCC_CONFIG_EXTRA_ARGS_MULTI_N := --disable-multilib
MINGW_CONFIG_EXTRA_ARGS_MULTI_Y := --enable-lib32 --enable-lib64
MINGW_CONFIG_EXTRA_ARGS_MULTI_N :=

########################################
# MISC helper
########################################

GCC_ADA_Y := ,ada
GCC_ADA_N :=
GCC_CPP_Y := ,c++
GCC_CPP_N :=
GCC_FORTRAN_Y := ,fortran
GCC_FORTRAN_N :=
GCC_OBJC_Y := ,objc,obj-c++
GCC_OBJC_N :=
GCC_JAVA_Y := ,java
GCC_JAVA_N :=
GCC_WINPTHREAD_DEP_N := /pthreads/.pthreads.install.${ENABLE_MULTILIB}
GCC_WINPTHREAD_DEP_Y := /winpthreads/obj.${ENABLE_MULTILIB}/.install.marker
LIBGCC_WINPTHREAD_DEP_N :=
LIBGCC_WINPTHREAD_DEP_Y := /winpthreads/obj.${ENABLE_MULTILIB}/.install.marker

########################################
# Configure
########################################
#Prefer gnutar to tar
TAR := $(or $(shell which gnutar 2>/dev/null),$(shell which tar 2>/dev/null),tar)

ifeq (,$(filter-out x86_64-%,${TARGET_ARCH}))
  MINGW_LIBDIR := lib64
else ifeq (,$(filter-out i386-% i486-% i586-% i686-%,${TARGET_ARCH}))
  MINGW_LIBDIR := lib32
else
  $(error Unknown CPU for target arch ${TARGET_ARCH})
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

ifneq (,${BUILD_ARCH})
  CONFIG_BUILD_ARGS = --build=${BUILD_ARCH}
endif

ifneq (,$(filter %-mingw32,${HOST_ARCH}))
  HOST_TYPE := windows
endif

WGET=wget -c -t0 -T60 -O
ifeq (,$(shell which wget 2>/dev/null))
  WGET=curl -o
endif

ifneq ($(strip $(HOST_ARCH)),$(strip $(BUILD_ARCH)))
  CANADIAN_CROSS_BUILD := Y
else
  ADD_BIN_PATH ?= PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH
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
ifeq (,$(strip ${BINUTILS_UPDATE}))
	cd $(dir $@) && cvs -d :pserver:anoncvs:anoncvs@sourceware.org:/cvs/src -z9 checkout -d . -N binutils
	@touch $@
else
	cd $(dir $@) && cvs -d :pserver:anoncvs:anoncvs@sourceware.org:/cvs/src -z9 update
	@touch $@
.PHONY: src/binutils/.binutils.pull.marker
endif

########################################
# Pull GCC
########################################
## find a gcc revision (r???) and a stamp for the file name ${GCC_REV_STAMP}
ifneq (,$(findstring -,${GCC_REVISION}))
  # GCC_REVISION is a date
  GCC_REV_STAMP := d$(subst -,,${GCC_REVISION})
  GCC_REVISION := $(shell TZ=Z svn log --non-interactive --no-auth-cache \
                                       -r "{$(subst -,,${GCC_REVISION})T0000Z}:{$(subst -,,${GCC_REVISION})T0030Z}" \
                                       svn://gcc.gnu.org/svn/gcc/trunk | \
                          grep gccadmin | \
                          grep ${GCC_REVISION} | \
                          cut -d ' ' -f 1)
  GCC_REVISION := $(subst r,,${GCC_REVISION})
else ifeq (_,$(if ${GCC_REVISION},,false)_$(strip \
              $(subst 0,, $(subst 1,, $(subst 2,, \
              $(subst 3,, $(subst 4,, $(subst 5,, \
              $(subst 6,, $(subst 7,, $(subst 8,, \
              $(subst 9,, $(subst 0,, ${GCC_REVISION} )))))))))))))
  # GCC_REVISION is a number
  GCC_REVISION := ${GCC_REVISION}
  GCC_REV_STAMP := r${GCC_REVISION}
else
  # GCC_REVISION is some opaque string (e.g. "head")
  GCC_REV_STAMP := r${GCC_REVISION}
endif # GCC revision

gcc-pull: \
    src/gcc/gcc/.gcc.pull.marker

src/gcc/gcc/.gcc.pull.marker: \
    src/gcc/gcc/.mkdir.marker
	cd $(dir $@) && \
	svn co --non-interactive --no-auth-cache --revision ${GCC_REVISION} \
	       svn://gcc.gnu.org/svn/gcc/$(strip ${GCC_BRANCH})/ .
	$(WGET) ecj.jar ftp://sourceware.org/pub/java/ecj-latest.jar
	@touch $@

  ifneq (,$(strip ${GCC_UPDATE}))
.PHONY: src/gcc/gcc/.gcc.pull.marker
  endif

########################################
# Pull pthreads-win32 from cvs
########################################
pthreads-download: \
    src/pthreads/.pthreads.download.marker

src/pthreads/.pthreads.download.marker: \
    src/.mkdir.marker
	cd src && cvs -z9 -d ${PTHREADS_CVS_PULL} checkout -D ${PTHREADS_CVS_DATE} pthreads
	@touch $@

ifneq (,$(strip ${PTHREADS_UPDATE}))
.PHONY: src/pthreads/.pthreads.download.marker
endif

########################################
# Pull winpthreads from trunk
########################################
winpthreads-download: \
    src/winpthreads/.winpthreads.download.marker

src/winpthreads/.winpthreads.download.marker: \
    src/.mkdir.marker
	svn co https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/experimental/winpthreads --revision ${WINPTHREADS_REVISION} src/winpthreads
	@touch $@

ifneq (,$(strip ${PTHREADS_UPDATE}))
.PHONY: src/winpthreads/.winpthreads.download.marker
endif
########################################
# Download gmp
########################################

gmp-download: \
    src/gmp.tar.bz2

src/gmp.tar.bz2: \
    src/.mkdir.marker
	$(WGET) $@ ftp://ftp.gnu.org/gnu/gmp/gmp-$(strip ${GMP_VERSION}).tar.bz2

########################################
# Extract gmp
########################################

gmp-extract: \
    src/gmp/.gmp.extract.marker

src/gmp/.gmp.extract.marker: \
    src/gmp.tar.bz2 \
    src/gmp/src/.mkdir.marker \
    src/patches/.patches.pull.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xjvf $<
	@touch $@

########################################
# Download mpfr
########################################

mpfr-download: \
    src/mpfr.tar.bz2

src/mpfr.tar.bz2: \
    src/.mkdir.marker
	$(WGET) $@ http://www.mpfr.org/mpfr-$(strip ${MPFR_VERSION})/mpfr-$(strip ${MPFR_VERSION}).tar.bz2

########################################
# Extract mpfr
########################################

mpfr-extract: \
    src/mpfr/.mpfr.extract.marker

src/mpfr/.mpfr.extract.marker: \
    src/mpfr.tar.bz2 \
    src/mpfr/src/.mkdir.marker \
    src/patches/.patches.pull.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xjvf $<
	cd $(dir $@)src && patch -Np1 -i ../../patches/mpfr-3.1.0/allpatches-p3
	@touch $@

########################################
# Download mpc
########################################

mpc-download: \
    src/mpc.tar.gz

src/mpc.tar.gz: \
    src/.mkdir.marker
	$(WGET) $@ http://www.multiprecision.org/mpc/download/mpc-$(strip ${MPC_VERSION}).tar.gz

########################################
# Extract mpc
########################################

mpc-extract: \
    src/mpc/.mpc.extract.marker

src/mpc/.mpc.extract.marker: \
    src/mpc.tar.gz \
    src/mpc/src/.mkdir.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xzvf $<
	@touch $@


########################################
# Download PPL
########################################

ppl-download: \
    src/ppl.tar.gz

src/ppl.tar.gz: \
    src/.mkdir.marker
	$(WGET) $@ ftp://gcc.gnu.org/pub/gcc/infrastructure/ppl-$(strip ${PPL_VERSION}).tar.gz

########################################
# Extract PPL
########################################

ppl-extract: \
    src/ppl/.ppl.extract.marker

src/ppl/.ppl.extract.marker: \
    src/ppl.tar.gz \
    src/ppl/src/.mkdir.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xzvf $<
	@touch $@

########################################
# Download CLooG
########################################

cloog-download: \
    src/cloog.tar.gz

src/cloog.tar.gz: \
    src/.mkdir.marker
	$(WGET) $@ http://www.bastoul.net/cloog/pages/download/cloog-$(strip ${CLOOG_VERSION}).tar.gz

########################################
# Extract CLooG
########################################

cloog-extract: \
    src/cloog/.cloog.extract.marker

src/cloog/.cloog.extract.marker: \
    src/cloog.tar.gz \
    src/cloog/src/.mkdir.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xzvf $<
	@touch $@

########################################
# Download OSL
########################################
osl-download: \
    src/osl.tar.gz

src/osl.tar.gz: \
    src/.mkdir.marker
	$(WGET) $@ http://www.lri.fr/~bastoul/development/openscop/docs/osl-$(strip ${OSL_VERSION}).tar.gz

########################################
# Extract OSL
########################################

osl-extract: \
    src/osl/.osl.extract.marker

src/osl/.osl.extract.marker: \
    src/osl.tar.gz \
    src/osl/src/.mkdir.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xzvf $<
	@touch $@


########################################
# Download ISL
########################################

isl-download: \
    src/isl.tar.bz2

src/isl.tar.bz2: \
    src/.mkdir.marker
	$(WGET) $@ http://www.kotnet.org/~skimo/isl/isl-$(strip ${ISL_VERSION}).tar.bz2

########################################
# Extract ISL
########################################

isl-extract: \
    src/isl/.isl.extract.marker

src/isl/.isl.extract.marker: \
    src/isl.tar.bz2 \
    src/isl/src/.mkdir.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xjvf $<
	@touch $@

########################################
# Download PIPLIB
########################################

piplib-download: \
    src/piplib.tar.gz

src/piplib.tar.gz: \
    src/.mkdir.marker
	$(WGET) $@ http://www.bastoul.net/cloog/pages/download/piplib-$(strip ${PIPLIB_VERSION}).tar.gz

########################################
# Extract PIPLIB
########################################

piplib-extract: \
    src/piplib/.piplib.extract.marker

src/piplib/.piplib.extract.marker: \
    src/piplib.tar.gz \
    src/piplib/src/.mkdir.marker
	$(TAR) -C $(dir $@)/src --strip-components=1 -xzvf $<
	@touch $(dir $@)/src/NEWS $(dir $@)/src/AUTHORS $(dir $@)/src/ChangeLog
	cd $(dir $@)/src && autoreconf -iv
	@touch $@

########################################
# Pull mingw
########################################

mingw-pull: \
    src/mingw/.mingw.pull.marker

src/mingw/.mingw.pull.marker: \
    src/mingw/.mkdir.marker
	svn checkout --non-interactive --no-auth-cache --revision ${MINGW_REVISION} \
	    https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/$(strip ${MINGW_BRANCH})/ \
	    $(dir $@)
	@touch $@

  ifneq (,$(strip ${MINGW_UPDATE}))
.PHONY: src/mingw/.mingw.pull.marker
  endif

## XXX Mook: stamp the source with the revision used

########################################
# Create source tarball
########################################

src-archive:  ${SRC_ARCHIVE}

ifeq (,$(wildcard ${SRC_ARCHIVE}))
${SRC_ARCHIVE}: \
    src/binutils/.binutils.pull.marker \
    src/gcc/gcc/.gcc.pull.marker \
    src/gmp/.gmp.extract.marker \
    src/mpfr/.mpfr.extract.marker \
    src/mpc/.mpc.extract.marker \
    src/ppl/.ppl.extract.marker \
    src/isl/.isl.extract.marker \
    src/piplib/.piplib.extract.marker \
    src/cloog/.cloog.extract.marker \
    src/mingw/.mingw.pull.marker \
    src/pthreads/.pthreads.download.marker \
    src/winpthreads/.winpthreads.download.marker
endif

${SRC_ARCHIVE}:
	$(TAR) vcjf $@ --owner 0 --group 0 --exclude=.svn\
	    --exclude=.*.marker --exclude=CVS --exclude=gmp.tar.bz2 \
	    --exclude=mpfr.tar.bz2 --exclude=mpc.tar.gz \-C src .

########################################
# Extract source tarball
########################################
src-extract:: \
    ${BUILD_DIR}/.extract.marker

${BUILD_DIR}/.extract.marker: \
    ${SRC_ARCHIVE}
	-mkdir -p $(dir $@)
	$(TAR) -C $(dir $@) -xvjpf $<
	@touch $@

${BUILD_DIR}/root/.root.init.marker: \
    ${BUILD_DIR}/root/${TARGET_ARCH}/.mkdir.marker \
    ${BUILD_DIR}/.extract.marker
ifneq (,$(filter MINGW%,$(shell uname -s)))
	test -e ${BUILD_DIR}/root/mingw  || \
	  junction ${BUILD_DIR}/root/mingw "${BUILD_DIR}/root/${TARGET_ARCH}"
	test -e ${BUILD_DIR}/root/mingw
	test -e ${BUILD_DIR}/root/${TARGET_ARCH}/lib32 || mkdir ${BUILD_DIR}/root/${TARGET_ARCH}/lib32
	test -e ${BUILD_DIR}/root/${TARGET_ARCH}/lib64 || mkdir ${BUILD_DIR}/root/${TARGET_ARCH}/lib64
	test -e ${BUILD_DIR}/root/${TARGET_ARCH}/lib || \
	  junction ${BUILD_DIR}/root/${TARGET_ARCH}/lib "${BUILD_DIR}/root/${TARGET_ARCH}/${MINGW_LIBDIR}"
	test -e ${BUILD_DIR}/root/${TARGET_ARCH}/lib
else
	test -h ${BUILD_DIR}/root/mingw  || \
	  ln -s "${TARGET_ARCH}" ${BUILD_DIR}/root/mingw
	test -h ${BUILD_DIR}/root/mingw
	test -d ${BUILD_DIR}/root/${TARGET_ARCH}/lib32 || mkdir ${BUILD_DIR}/root/${TARGET_ARCH}/lib32
	test -d ${BUILD_DIR}/root/${TARGET_ARCH}/lib64 || mkdir ${BUILD_DIR}/root/${TARGET_ARCH}/lib64
	test -h ${BUILD_DIR}/root/${TARGET_ARCH}/lib  || \
	  ln -s "${MINGW_LIBDIR}" "${BUILD_DIR}/root/${TARGET_ARCH}/lib"
	test -h ${BUILD_DIR}/root/mingw
endif
	@touch $@

########################################
# Configure mingw-w64 headers
########################################
headers-configure: \
    ${BUILD_DIR}/mingw-headers/obj/.config.marker

${BUILD_DIR}/mingw-headers/obj/.config.marker: \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/mingw-headers/obj/.mkdir.marker
	cd $(dir $@) && \
	  ${CURDIR}/${BUILD_DIR}/mingw/mingw-w64-headers/configure \
	  --prefix=${CURDIR}/${BUILD_DIR}/root/${TARGET_ARCH} \
	  --host=${TARGET_ARCH} \
	  ${CONFIG_BUILD_ARGS}
	@touch $@

########################################
# Install mingw-w64 headers
########################################
headers-install: \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker

${BUILD_DIR}/mingw-headers/obj/.install.marker: \
    ${BUILD_DIR}/mingw-headers/obj/.config.marker
	$(MAKE) -C $(dir $@) install
	@touch $@

########################################
# Configure binutils
########################################
binutils-configure: \
    ${BUILD_DIR}/binutils/obj/.config.marker

${BUILD_DIR}/binutils/obj/.config.marker: \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/binutils/obj/.mkdir.marker \
    ${BUILD_DIR}/root/.root.init.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/binutils/src/configure \
	    --target=${TARGET_ARCH} \
	    ${BINUTILS_CONFIG_HOST_ARGS} \
	    ${CONFIG_BUILD_ARGS} \
	    --prefix=${CURDIR}/${BUILD_DIR}/root \
	    --with-sysroot=${CURDIR}/${BUILD_DIR}/root \
	    ${BINUTILS_CONFIG_EXTRA_ARGS_MULTI_${ENABLE_MULTILIB}} \
	    ${BINUTILS_CONFIG_EXTRA_ARGS}
	@touch $@

########################################
# Compile binutils
########################################
binutils-compile: \
    ${BUILD_DIR}/binutils/obj/.compile.marker

${BUILD_DIR}/binutils/obj/.compile.marker: \
    ${BUILD_DIR}/binutils/obj/.config.marker
	$(MAKE) ${MAKE_OPTS} -C $(dir $@)
	@touch $@

########################################
# Install binutils
########################################
binutils-install: \
    ${BUILD_DIR}/binutils/obj/.install.marker

${BUILD_DIR}/binutils/obj/.install.marker: \
    ${BUILD_DIR}/binutils/obj/.compile.marker
	$(MAKE) -C $(dir $@) install
	@touch $@

########################################
# GCC cross compiling support - winsup
########################################
gcc-winsup: \
    ${BUILD_DIR}/gcc/gcc/.winsup.marker

${BUILD_DIR}/gcc/gcc/.winsup.marker: \
    ${BUILD_DIR}/.extract.marker \
    ${BUILD_DIR}/root/.root.init.marker
ifneq (,$(filter MINGW%,$(shell uname -s)))
	test -e ${BUILD_DIR}/gcc/gcc/winsup  || \
	  junction ${BUILD_DIR}/gcc/gcc/winsup "${BUILD_DIR}/root"
	test -e ${BUILD_DIR}/gcc/gcc/winsup
else
	test -h ${BUILD_DIR}/gcc/gcc/winsup  || \
	  ln -s "../../../${BUILD_DIR}/root" ${BUILD_DIR}/gcc/gcc/winsup
	test -h ${BUILD_DIR}/gcc/gcc/winsup
endif
	@touch $@

########################################
# Configure GMP
########################################

gmp-configure: \
    ${BUILD_DIR}/gmp/obj/.config.marker

${BUILD_DIR}/gmp/obj/.config.marker: \
    ${BUILD_DIR}/gmp/obj/.mkdir.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/root/.root.init.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/gmp/src/configure \
	    $(or ${GCC_CONFIG_HOST_ARGS},--host=none-none-none) \
	    $(CONFIG_BUILD_ARGS) \
	    CPPFLAGS=-fexceptions \
	    --enable-cxx \
	    --disable-shared \
	    --prefix=${CURDIR}/${BUILD_DIR}/gmp/install
	@touch $@

########################################
# Compile GMP
########################################
gmp-compile: \
    ${BUILD_DIR}/gmp/obj/.compile.marker

${BUILD_DIR}/gmp/obj/.compile.marker: \
    ${BUILD_DIR}/gmp/obj/.config.marker
	$(MAKE) -C $(dir $@)
	@touch $@

########################################
# Install GMP
########################################
gmp-install: \
    ${BUILD_DIR}/gmp/install/.install.marker

${BUILD_DIR}/gmp/install/.install.marker: \
    ${BUILD_DIR}/gmp/obj/.compile.marker \
    ${BUILD_DIR}/gmp/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/gmp/obj install
	@touch $@

########################################
# Configure MPFR
########################################
mpfr-configure: \
    ${BUILD_DIR}/mpfr/obj/.config.marker

${BUILD_DIR}/mpfr/obj/.config.marker: \
    ${BUILD_DIR}/mpfr/obj/.mkdir.marker \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/mpfr/src/configure \
	    ${GCC_CONFIG_HOST_ARGS} \
	    $(CONFIG_BUILD_ARGS) \
	    --disable-shared \
	    --prefix=${CURDIR}/${BUILD_DIR}/mpfr/install \
            --with-gmp=${CURDIR}/${BUILD_DIR}/gmp/install
	@touch $@

########################################
# Compile MPFR
########################################
mpfr-compile: \
    ${BUILD_DIR}/mpfr/obj/.compile.marker

${BUILD_DIR}/mpfr/obj/.compile.marker: \
    ${BUILD_DIR}/mpfr/obj/.config.marker
	$(MAKE) -C $(dir $@)
	@touch $@

########################################
# Install MPFR
########################################
mpfr-install: \
    ${BUILD_DIR}/mpfr/install/.install.marker

${BUILD_DIR}/mpfr/install/.install.marker: \
    ${BUILD_DIR}/mpfr/obj/.compile.marker \
    ${BUILD_DIR}/mpfr/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/mpfr/obj install
	@touch $@

########################################
# Configure MPC
########################################
mpc-configure: \
    ${BUILD_DIR}/mpc/obj/.config.marker

${BUILD_DIR}/mpc/obj/.config.marker: \
    ${BUILD_DIR}/mpc/obj/.mkdir.marker \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker \
    ${BUILD_DIR}/mpfr/install/.install.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/mpc/src/configure \
	    ${GCC_CONFIG_HOST_ARGS} \
	    $(CONFIG_BUILD_ARGS) \
            --enable-static --disable-shared \
	    --prefix=${CURDIR}/${BUILD_DIR}/mpc/install \
            --with-gmp=${CURDIR}/${BUILD_DIR}/gmp/install \
            --with-mpfr=${CURDIR}/${BUILD_DIR}/mpfr/install
	@touch $@

########################################
# Compile MPC
########################################
mpc-compile: \
    ${BUILD_DIR}/mpc/obj/.compile.marker

${BUILD_DIR}/mpc/obj/.compile.marker: \
    ${BUILD_DIR}/mpc/obj/.config.marker
	$(MAKE) -C $(dir $@)
	@touch $@

########################################
# Install MPC
########################################
mpc-install: \
    ${BUILD_DIR}/mpc/install/.install.marker

${BUILD_DIR}/mpc/install/.install.marker: \
    ${BUILD_DIR}/mpc/obj/.compile.marker \
    ${BUILD_DIR}/mpc/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/mpc/obj install
	@touch $@

########################################
# Configure PPL
########################################
ppl-configure: \
    ${BUILD_DIR}/ppl/obj/.config.marker

${BUILD_DIR}/ppl/obj/.config.marker: \
    ${BUILD_DIR}/ppl/obj/.mkdir.marker \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/ppl/src/configure \
        ${GCC_CONFIG_HOST_ARGS} \
        $(CONFIG_BUILD_ARGS) \
        --enable-static --disable-shared \
        --enable-pch --enable-watchdog \
        --prefix=${CURDIR}/${BUILD_DIR}/ppl/install \
        --with-gmp-prefix=${CURDIR}/${BUILD_DIR}/gmp/install \
        CPPFLAGS=-fexceptions
	@touch $@

########################################
# Compile PPL
########################################
ppl-compile: \
    ${BUILD_DIR}/ppl/obj/.compile.marker

${BUILD_DIR}/ppl/obj/.compile.marker: \
    ${BUILD_DIR}/ppl/obj/.config.marker
	$(MAKE) -C $(dir $@)
	@touch $@

########################################
# Install PPL
########################################
ppl-install: \
    ${BUILD_DIR}/ppl/install/.install.marker

${BUILD_DIR}/ppl/install/.install.marker: \
    ${BUILD_DIR}/ppl/obj/.compile.marker \
    ${BUILD_DIR}/ppl/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/ppl/obj install
	@touch $@

########################################
# Configure PIPLIB
########################################
piplib-configure: \
    ${BUILD_DIR}/piplib/obj/.config.marker

${BUILD_DIR}/piplib/obj/.config.marker: \
    ${BUILD_DIR}/piplib/obj/.mkdir.marker \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/piplib/src/configure \
        ${GCC_CONFIG_HOST_ARGS} \
        $(CONFIG_BUILD_ARGS) \
        --enable-static --disable-shared \
        --prefix=${CURDIR}/${BUILD_DIR}/piplib/install \
        --with-gmp=${CURDIR}/${BUILD_DIR}/gmp/install \
        CPPFLAGS=-fexceptions
	@touch $@

########################################
# Compile PIPLIB
########################################
piplib-compile: \
    ${BUILD_DIR}/piplib/obj/.compile.marker

${BUILD_DIR}/piplib/obj/.compile.marker: \
    ${BUILD_DIR}/piplib/obj/.config.marker
	$(MAKE) -C $(dir $@)
	@touch $@

########################################
# Install PIPLIB
########################################
piplib-install: \
    ${BUILD_DIR}/piplib/install/.install.marker

${BUILD_DIR}/piplib/install/.install.marker: \
    ${BUILD_DIR}/piplib/obj/.compile.marker \
    ${BUILD_DIR}/piplib/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/piplib/obj install
	@touch $@

########################################
# Configure OSL
########################################
osl-configure: \
    ${BUILD_DIR}/osl/obj/.config.marker

${BUILD_DIR}/osl/obj/.config.marker: \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/osl/obj/.mkdir.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/osl/src/configure \
        ${GCC_CONFIG_HOST_ARGS} \
        $(CONFIG_BUILD_ARGS) \
        --enable-static --disable-shared \
        --prefix=${CURDIR}/${BUILD_DIR}/osl/install \
        --with-gmp=system \
        --with-gmp-prefix=${CURDIR}/${BUILD_DIR}/gmp/install \
        CPPFLAGS="-fexceptions -I${CURDIR}/${BUILD_DIR}/gmp/install/include" \
        LDFLAGS="-L${CURDIR}/${BUILD_DIR}/gmp/install/lib" \
        LIBS="-lgmp"
	@touch $@

########################################
# Compile OSL
########################################
osl-compile: \
    ${BUILD_DIR}/osl/obj/.compile.marker

${BUILD_DIR}/osl/obj/.compile.marker: \
    ${BUILD_DIR}/osl/obj/.config.marker
	$(MAKE) -C $(dir $@) V=1
	@touch $@

########################################
# Install OSL
########################################
osl-install: \
    ${BUILD_DIR}/osl/install/.install.marker

${BUILD_DIR}/osl/install/.install.marker: \
    ${BUILD_DIR}/osl/obj/.compile.marker \
    ${BUILD_DIR}/osl/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/osl/obj install
	@touch $@

########################################
# Configure ISL
########################################
isl-configure: \
    ${BUILD_DIR}/isl/obj/.config.marker

${BUILD_DIR}/isl/obj/.config.marker: \
    ${BUILD_DIR}/isl/obj/.mkdir.marker \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker \
    ${BUILD_DIR}/piplib/install/.install.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/isl/src/configure \
        ${GCC_CONFIG_HOST_ARGS} \
        $(CONFIG_BUILD_ARGS) \
        --enable-static --disable-shared \
        --prefix=${CURDIR}/${BUILD_DIR}/isl/install \
        --with-gmp=system \
        --with-gmp-prefix=${CURDIR}/${BUILD_DIR}/gmp/install \
        --with-piplib=system \
        --with-piplib-prefix=${CURDIR}/${BUILD_DIR}/piplib/install \
        CPPFLAGS="-fexceptions -I${CURDIR}/${BUILD_DIR}/gmp/install/include -I${CURDIR}/${BUILD_DIR}/piplib/install/include" \
        LDFLAGS="-L${CURDIR}/${BUILD_DIR}/gmp/install/lib -L${CURDIR}/${BUILD_DIR}/piplib/install/lib" \
        LIBS="-lpiplibMP -lgmp"
	@touch $@

########################################
# Compile ISL
########################################
isl-compile: \
    ${BUILD_DIR}/isl/obj/.compile.marker

${BUILD_DIR}/isl/obj/.compile.marker: \
    ${BUILD_DIR}/isl/obj/.config.marker
	$(MAKE) -C $(dir $@)
	@touch $@

########################################
# Install ISL
########################################
isl-install: \
    ${BUILD_DIR}/isl/install/.install.marker

${BUILD_DIR}/isl/install/.install.marker: \
    ${BUILD_DIR}/isl/obj/.compile.marker \
    ${BUILD_DIR}/isl/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/isl/obj install
	@touch $@

########################################
# Configure CLooG
########################################
# PPL no longer needed
# ${BUILD_DIR}/ppl/install/.install.marker
cloog-configure: \
    ${BUILD_DIR}/cloog/obj/.config.marker

${BUILD_DIR}/cloog/obj/.config.marker: \
    ${BUILD_DIR}/cloog/obj/.mkdir.marker \
    ${BUILD_DIR}/root/.root.init.marker \
    ${BUILD_DIR}/mingw-headers/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker \
    ${BUILD_DIR}/piplib/install/.install.marker \
    ${BUILD_DIR}/isl/install/.install.marker \
    ${BUILD_DIR}/osl/install/.install.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/cloog/src/configure \
        ${GCC_CONFIG_HOST_ARGS} \
        $(CONFIG_BUILD_ARGS) \
            --enable-static --disable-shared \
            --with-isl=system \
            --with-osl=system \
            --with-gmp=system \
            --prefix=${CURDIR}/${BUILD_DIR}/cloog/install \
            --with-gmp-prefix=${CURDIR}/${BUILD_DIR}/gmp/install \
            --with-isl-prefix=${CURDIR}/${BUILD_DIR}/isl/install \
            --with-osl-prefix=${CURDIR}/${BUILD_DIR}/osl/install
	@touch $@

########################################
# Compile CLooG
########################################
cloog-compile: \
    ${BUILD_DIR}/cloog/obj/.compile.marker

${BUILD_DIR}/cloog/obj/.compile.marker: \
    ${BUILD_DIR}/cloog/obj/.config.marker
	$(MAKE) -C $(dir $@) V=1
	@touch $@

########################################
# Install CLooG
########################################
# Workaround to make gcc link properly with static deps
cloog-install: \
    ${BUILD_DIR}/cloog/install/.install.marker

${BUILD_DIR}/cloog/install/.install.marker: \
    ${BUILD_DIR}/cloog/obj/.compile.marker \
    ${BUILD_DIR}/cloog/install/.mkdir.marker
	$(MAKE) -C ${BUILD_DIR}/cloog/obj install
	@mv ${CURDIR}/${BUILD_DIR}/cloog/install/lib/libcloog-isl.a ${CURDIR}/${BUILD_DIR}/cloog/install/lib/libcloog-isl-real.a
	@echo SEARCH_DIR\(${CURDIR}/${BUILD_DIR}/cloog/install/lib\) > ${CURDIR}/${BUILD_DIR}/cloog/install/lib/libcloog-isl.a
	@echo SEARCH_DIR\(${CURDIR}/${BUILD_DIR}/osl/install/lib\) >> ${CURDIR}/${BUILD_DIR}/cloog/install/lib/libcloog-isl.a
	@echo SEARCH_DIR\(${CURDIR}/${BUILD_DIR}/isl/install/lib\) >> ${CURDIR}/${BUILD_DIR}/cloog/install/lib/libcloog-isl.a
	@echo SEARCH_DIR\(${CURDIR}/${BUILD_DIR}/piplib/install/lib\) >> ${CURDIR}/${BUILD_DIR}/cloog/install/lib/libcloog-isl.a
	@echo 'INPUT(-lcloog-isl-real -losl -lisl -lpiplibMP -lmpfr -lgmp)' >> ${CURDIR}/${BUILD_DIR}/cloog/install/lib/libcloog-isl.a
	@touch $@

########################################
# Configure GCC
########################################
# PPL no longer needed
# ${BUILD_DIR}/ppl/install/.install.marker
gcc-configure: \
    ${BUILD_DIR}/gcc/obj/.config.marker

ifneq (,$(filter %-mingw32,${HOST_ARCH}))
${BUILD_DIR}/gcc/obj/.config.marker: \
    ${BUILD_DIR}/gcc/gcc/.winsup.marker
endif

# --enable-sjlj-exceptions no longer needed for win64 target, SEH is in use
# SJLJ is still used for win32 by default though

${BUILD_DIR}/gcc/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.mkdir.marker \
    ${BUILD_DIR}/binutils/obj/.install.marker \
    ${BUILD_DIR}/gmp/install/.install.marker \
    ${BUILD_DIR}/mpfr/install/.install.marker \
    ${BUILD_DIR}/mpc/install/.install.marker \
    ${BUILD_DIR}/isl/install/.install.marker \
    ${BUILD_DIR}/piplib/install/.install.marker \
    ${BUILD_DIR}/cloog/install/.install.marker \
    ${BUILD_DIR}/root/.root.init.marker
	cd $(dir $@) && \
	../../../${BUILD_DIR}/gcc/gcc/configure \
        --target=${TARGET_ARCH} \
        ${GCC_CONFIG_HOST_ARGS} \
        $(CONFIG_BUILD_ARGS) \
        --prefix=${CURDIR}/${BUILD_DIR}/root \
        --with-gnu-ld --with-gnu-as \
        --enable-cloog-backend=isl \
        --enable-graphite --enable-lto \
        --enable-long-long --enable-threads=win32 \
        --enable-c99 --enable-wchar_t \
        --enable-libstdcxx-debug \
        --enable-fully-dynamic-string --enable-libgomp \
        --with-dwarf2 \
        --enable-version-specific-runtime-libs \
        --with-sysroot=${CURDIR}/${BUILD_DIR}/root \
            --with-gmp=${CURDIR}/${BUILD_DIR}/gmp/install \
            --with-mpfr=${CURDIR}/${BUILD_DIR}/mpfr/install \
            --with-mpc=${CURDIR}/${BUILD_DIR}/mpc/install \
            --with-isl=${CURDIR}/${BUILD_DIR}/isl/install \
            --with-cloog=${CURDIR}/${BUILD_DIR}/cloog/install \
        --enable-languages=c${GCC_CPP_${GCC_CPP}}${GCC_FORTRAN_${GCC_FORTRAN}}${GCC_OBJC_${GCC_OBJC}}${GCC_JAVA_${GCC_JAVA}}${GCC_ADA_${GCC_ADA}} \
        ${GCC_CONFIG_EXTRA_ARGS_MULTI_${ENABLE_MULTILIB}} \
        ${GCC_CONFIG_EXTRA_ARGS}
	@touch $@
# -lm workarounds some weirdness where -lm was missing when linking backends

########################################
# Compile GCC stage 1
########################################
gcc-bootstrap-compile: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.compile.marker

${BUILD_DIR}/gcc/obj/.bootstrap.compile.marker: \
    ${BUILD_DIR}/gcc/obj/.config.marker
	$(MAKE) ${MAKE_OPTS} -C $(dir $@) all-gcc
	@touch $@

########################################
# Install GCC stage 1
########################################
gcc-bootstrap-install: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.install.marker

${BUILD_DIR}/gcc/obj/.bootstrap.install.marker: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.compile.marker
	$(MAKE) -C $(dir $@) install-gcc
	$(MAKE) -C $(dir $@) install-lto-plugin || true
	@touch $@

########################################
# Configure mingw-w64 CRT
########################################
crt-configure: \
    ${BUILD_DIR}/mingw/obj/.config.marker

${BUILD_DIR}/mingw/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.install.marker \
    ${BUILD_DIR}/mingw/obj/.mkdir.marker
	cd $(dir $@) && \
	$(ADD_BIN_PATH) ../../../${BUILD_DIR}/mingw/mingw-w64-crt/configure \
	    $(CONFIG_BUILD_ARGS) \
	    --host=${TARGET_ARCH} \
	    --prefix=${CURDIR}/${BUILD_DIR}/root/${TARGET_ARCH} \
	    --with-sysroot=${CURDIR}/${BUILD_DIR}/root \
	    ${MINGW_CONFIG_EXTRA_ARGS_MULTI_${ENABLE_MULTILIB}} \
	    ${MINGW_CONFIG_EXTRA_ARGS}
	@touch $@

########################################
# Compile mingw-w64 CRT
########################################
crt-compile: \
    ${BUILD_DIR}/mingw/obj/.compile.marker

${BUILD_DIR}/mingw/obj/.compile.marker: \
    ${BUILD_DIR}/mingw/obj/.config.marker
	$(ADD_BIN_PATH) $(MAKE) ${MAKE_OPTS} -C $(dir $@)
	@touch $@

########################################
# Install mingw-w64 CRT
########################################
crt-install: \
    ${BUILD_DIR}/mingw/obj/.install.marker

${BUILD_DIR}/mingw/obj/.install.marker: \
    ${BUILD_DIR}/mingw/obj/.compile.marker
	$(ADD_BIN_PATH) $(MAKE) -C $(dir $@) install
	@touch $@

########################################
# Configure mingw-w64 winpthreads
########################################
winpthreads-configure: \
    ${BUILD_DIR}/winpthreads/obj.${ENABLE_MULTILIB}/.config.marker

${BUILD_DIR}/winpthreads/obj.N/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.install.marker \
    ${BUILD_DIR}/winpthreads/obj.N/.mkdir.marker
	cd $(dir $@) && \
	$(ADD_BIN_PATH) ../../../${BUILD_DIR}/winpthreads/configure \
	    $(CONFIG_BUILD_ARGS) \
	    --host=${TARGET_ARCH} \
	    --prefix=${CURDIR}/${BUILD_DIR}/root/${TARGET_ARCH}
	@touch $@

${BUILD_DIR}/winpthreads/obj.Y/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.install.marker \
    ${BUILD_DIR}/winpthreads/obj.Y/x86_64/.mkdir.marker \
    ${BUILD_DIR}/winpthreads/obj.Y/i686/.mkdir.marker
	cd $(dir $@)x86_64 && \
	$(ADD_BIN_PATH) ../../../../${BUILD_DIR}/winpthreads/configure \
	    $(CONFIG_BUILD_ARGS) \
	    --host=${TARGET_ARCH} \
	    --prefix=${CURDIR}/${BUILD_DIR}/root/${TARGET_ARCH} \
	    CFLAGS=-m64 RCFLAGS="-D_WIN64=1 -F pe-x86-64" \
	    --libdir=${CURDIR}/${BUILD_DIR}/root/${TARGET_ARCH}/lib64
	cd $(dir $@)i686 && \
	$(ADD_BIN_PATH) ../../../../${BUILD_DIR}/winpthreads/configure \
	    $(CONFIG_BUILD_ARGS) \
	    --host=${TARGET_ARCH} \
	    --prefix=${CURDIR}/${BUILD_DIR}/root/${TARGET_ARCH} \
	    CFLAGS=-m32 RCFLAGS="-U_WIN64 -F pe-i386" \
	    --libdir=${CURDIR}/${BUILD_DIR}/root/${TARGET_ARCH}/lib32
	    @touch $@

########################################
# Compile mingw-w64 winpthreads
########################################
winpthreads-compile: \
    ${BUILD_DIR}/winpthreads/obj.${ENABLE_MULTILIB}/.compile.marker

${BUILD_DIR}/winpthreads/obj.N/.compile.marker: \
    ${BUILD_DIR}/winpthreads/obj.N/.config.marker
	$(ADD_BIN_PATH) $(MAKE) ${MAKE_OPTS} -C $(dir $@)
	@touch $@

${BUILD_DIR}/winpthreads/obj.Y/.compile.marker: \
    ${BUILD_DIR}/winpthreads/obj.Y/.config.marker
	$(ADD_BIN_PATH) $(MAKE) ${MAKE_OPTS} -C $(dir $@)x86_64
	$(ADD_BIN_PATH) $(MAKE) ${MAKE_OPTS} -C $(dir $@)i686
	@touch $@

########################################
# Install mingw-w64 winpthreads
########################################
winpthreads-install: \
    ${BUILD_DIR}/winpthreads/obj.${ENABLE_MULTILIB}/.install.marker

${BUILD_DIR}/winpthreads/obj.N/.install.marker: \
    ${BUILD_DIR}/winpthreads/obj.N/.compile.marker
	$(ADD_BIN_PATH) $(MAKE) -C $(dir $@) install
	@touch $@

${BUILD_DIR}/winpthreads/obj.Y/.install.marker: \
    ${BUILD_DIR}/winpthreads/obj.Y/.compile.marker
	$(ADD_BIN_PATH) $(MAKE) -C $(dir $@)x86_64 install
	$(ADD_BIN_PATH) $(MAKE) -C $(dir $@)i686 install
	@touch $@

########################################
# Compile libgcc
########################################

gcc-libgcc-compile: \
    ${BUILD_DIR}/gcc/obj/.libgcc.compile.marker

${BUILD_DIR}/gcc/obj/.libgcc.compile.marker: \
    ${BUILD_DIR}/mingw/obj/.install.marker \
    ${BUILD_DIR}${LIBGCC_WINPTHREAD_DEP_${USE_WINPTHREADS}}
	$(MAKE) ${MAKE_OPTS} -C $(dir $@) all-target-libgcc
	@touch $@

########################################
# Install libgcc
########################################
gcc-libgcc-install: \
    ${BUILD_DIR}/gcc/obj/.libgcc.install.marker

${BUILD_DIR}/gcc/obj/.libgcc.install.marker: \
    ${BUILD_DIR}/gcc/obj/.libgcc.compile.marker
	$(MAKE) -C $(dir $@) install-target-libgcc
	@touch $@

########################################
# Prep pthreads-win32 from cvs
########################################
pthreads-prep: \
    ${BUILD_DIR}/pthreads/.pthreads.prep

${BUILD_DIR}/pthreads/.pthreads.prep: \
    ${BUILD_DIR}/root/.root.init.marker \
    src/patches/.patches.pull.marker \
    src/pthreads/.pthreads.download.marker
	cp -prf src/pthreads ${BUILD_DIR}/
	cp -p src/patches/pthreads_win32/w64sup.patch $(dir $@)
	cd $(dir $@) && patch -Np1 -i w64sup.patch
	cp -p $(dir $@)/config.h $(dir $@)pthreads_win32_config.h
	cp -p $(dir $@)/GNUmakefile $(dir $@)GNUmakefile.ori
	sed -e 's/HAVE_CONFIG_H/1/' \
	  -e 's/config.h/pthreads_win32_config.h/' \
	  < $(dir $@)/pthread.h >$(dir $@)pthread.h.out
	mv $(dir $@)/pthread.h.out $(dir $@)pthread.h
	@touch $@

########################################
# Build pthreads-win32 from cvs
########################################
pthreads-build: \
    ${BUILD_DIR}/pthreads/.pthreads.build.${ENABLE_MULTILIB}

${BUILD_DIR}/pthreads/.pthreads.build.Y: \
    ${BUILD_DIR}/pthreads/.pthreads.build.x86_64-w64-mingw32 \
    ${BUILD_DIR}/pthreads/.pthreads.build.i686-w64-mingw32
	@touch $@

${BUILD_DIR}/pthreads/.pthreads.build.N: \
    ${BUILD_DIR}/pthreads/.pthreads.build.${TARGET_ARCH}
	@touch $@

${BUILD_DIR}/pthreads/.pthreads.build.x86_64-w64-mingw32: \
    ${BUILD_DIR}/pthreads/.pthreads.prep \
    ${BUILD_DIR}/mingw/obj/.install.marker \
    ${BUILD_DIR}/gcc/obj/.libgcc.install.marker
	sed -e 's/dlltool$$/& -m i386:x86-64/' \
	  -e 's/gcc$$/& -m64/' \
	  -e 's/g++$$/& -m64/' \
	  -e 's/windres$$/& -F pe-x86-64/' \
	  -e 's/pthreadGC\$$(DLL_VER)/&-w64/g' \
	  -e 's/pthreadGCE\$$(DLL_VER)/&-w64/g' \
	  < $(dir $@)GNUmakefile.ori > $(dir $@)GNUmakefile
	$(ADD_BIN_PATH) $(MAKE) ${MAKE_OPTS} -C $(dir $@) CROSS=${TARGET_ARCH}- $(PTHREADS_MAKE_ARGS)
	@touch $@

${BUILD_DIR}/pthreads/.pthreads.build.i686-w64-mingw32: \
    ${BUILD_DIR}/pthreads/.pthreads.prep \
    ${BUILD_DIR}/mingw/obj/.install.marker \
    ${BUILD_DIR}/gcc/obj/.libgcc.install.marker
	sed -e 's/dlltool$$/& -m i386/' \
	  -e 's/gcc$$/& -m32/' \
	  -e 's/g++$$/& -m32/' \
	  -e 's/windres$$/& -F pe-i386/' \
	  -e 's/pthreadGC\$$(DLL_VER)/&-w32/g' \
	  -e 's/pthreadGCE\$$(DLL_VER)/&-w32/g' \
	  < $(dir $@)GNUmakefile.ori > $(dir $@)GNUmakefile
	$(ADD_BIN_PATH) $(MAKE) ${MAKE_OPTS} -C $(dir $@) CROSS=${TARGET_ARCH}- $(PTHREADS_MAKE_ARGS)
	@touch $@

########################################
# Install pthreads-win32 from cvs
########################################
ifeq (${TARGET_ARCH}, x86_64-w64-mingw32)
  PTHREAD_DLL := pthreadGC2-w64.dll
else
  PTHREAD_DLL := pthreadGC2-w32.dll
endif

pthreads-install: \
    ${BUILD_DIR}/pthreads/.pthreads.install.${ENABLE_MULTILIB}

${BUILD_DIR}/pthreads/.pthreads.install.common: \
    ${BUILD_DIR}/pthreads/.pthreads.prep
	cp -p ${BUILD_DIR}/pthreads/pthread.h \
	  ${BUILD_DIR}/pthreads/sched.h \
	  ${BUILD_DIR}/pthreads/semaphore.h \
	  ${BUILD_DIR}/pthreads/pthreads_win32_config.h \
	  ${BUILD_DIR}/root/${TARGET_ARCH}/include
	cp -p ${BUILD_DIR}/pthreads/${PTHREAD_DLL} \
	  ${BUILD_DIR}/root/${TARGET_ARCH}/lib/libpthread.a
	@touch $@

${BUILD_DIR}/pthreads/.pthreads.install.Y: \
    ${BUILD_DIR}/pthreads/.pthreads.build.Y \
    ${BUILD_DIR}/pthreads/.pthreads.install.common \
    ${BUILD_DIR}/pthreads/.pthreads.install.x86_64-w64-mingw32 \
    ${BUILD_DIR}/pthreads/.pthreads.install.i686-w64-mingw32
	@touch $@

${BUILD_DIR}/pthreads/.pthreads.install.N: \
    ${BUILD_DIR}/pthreads/.pthreads.build.N \
    ${BUILD_DIR}/pthreads/.pthreads.install.common \
    ${BUILD_DIR}/pthreads/.pthreads.install.${TARGET_ARCH}
	@touch $@

${BUILD_DIR}/pthreads/.pthreads.install.x86_64-w64-mingw32: \
    ${BUILD_DIR}/pthreads/.pthreads.build.x86_64-w64-mingw32
	cp -p ${BUILD_DIR}/pthreads/pthreadGC2-w64.dll \
	  ${BUILD_DIR}/root/bin
	cp -fp ${BUILD_DIR}/pthreads/pthreadGC2-w64.dll \
	  ${BUILD_DIR}/root/${TARGET_ARCH}/lib64/libpthread.a
	@touch $@

${BUILD_DIR}/pthreads/.pthreads.install.i686-w64-mingw32: \
    ${BUILD_DIR}/pthreads/.pthreads.build.i686-w64-mingw32
	cp -p ${BUILD_DIR}/pthreads/pthreadGC2-w32.dll \
	  ${BUILD_DIR}/root/bin
	cp -fp ${BUILD_DIR}/pthreads/pthreadGC2-w32.dll \
	  ${BUILD_DIR}/root/${TARGET_ARCH}/lib32/libpthread.a
	@touch $@

########################################
# Compile full GCC
########################################
gcc-compile: \
    ${BUILD_DIR}/gcc/obj/.compile.marker \
    ${BUILD_DIR}/mingw/obj/.install.marker \

${BUILD_DIR}/gcc/obj/.compile.marker: \
    ${BUILD_DIR}/gcc/obj/.config.marker \
    ${BUILD_DIR}/mingw/obj/.install.marker \
	${BUILD_DIR}${GCC_WINPTHREAD_DEP_${USE_WINPTHREADS}}
	$(ADD_BIN_PATH) $(MAKE) ${MAKE_OPTS} -C $(dir $@)
	@touch $@

########################################
# Install full GCC
########################################
gcc-install: \
    ${BUILD_DIR}/gcc/obj/.install.marker

${BUILD_DIR}/gcc/obj/.install.marker: \
    ${BUILD_DIR}/gcc/obj/.compile.marker
	$(ADD_BIN_PATH) $(MAKE) -C $(dir $@) install
	@touch $@

########################################
# Create release tarball
########################################
release-archive: \
    ${BIN_ARCHIVE}

${BIN_ARCHIVE}: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${BUILD_DIR}/pre.pack
ifeq (windows,${HOST_TYPE})
	cd ${BUILD_DIR}/root && \
	zip -r -9 ../../$(patsubst %.tar.bz2,%.zip,$@) \
	     . -x .*.marker *.*.marker
else
	$(TAR) vcjf $@ -C ${BUILD_DIR}/root --owner 0 --group 0 \
	    --exclude=CVS --exclude=.svn --exclude=.*.marker \
            .
endif

########################################
# Pre-pack cleanups
########################################
# Nothing yet
pre-pack: \
    ${BUILD_DIR}/pre.pack

${BUILD_DIR}/pre.pack: \
    ${BUILD_DIR}/gcc/obj/.install.marker
	@touch $@

################################################################################
# Native (only active when native_dir != build_dir)
################################################################################

NATIVE_DIR := native

ifneq (${NATIVE_DIR},${BUILD_DIR})

########################################
# Initialize build root
########################################

${NATIVE_DIR}/root/.root.init.marker: \
    ${NATIVE_DIR}/root/${TARGET_ARCH}/.mkdir.marker \
    ${BUILD_DIR}/.extract.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure mingw-w64 headers
########################################
native-headers-configure: \
    ${NATIVE_DIR}/mingw-headers/obj/.config.marker

${NATIVE_DIR}/mingw-headers/obj/.config.marker: \
    ${NATIVE_DIR}/root/.root.init.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.mkdir.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install mingw-w64 headers
########################################
native-headers-install: \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker

${NATIVE_DIR}/mingw-headers/obj/.install.marker: \
    ${NATIVE_DIR}/mingw-headers/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure binutils
########################################
native-binutils-configure: \
    ${NATIVE_DIR}/binutils/obj/.config.marker

${NATIVE_DIR}/binutils/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/binutils/obj/.mkdir.marker \
    ${NATIVE_DIR}/root/.root.init.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile binutils
########################################
native-binutils-compile: \
    ${NATIVE_DIR}/binutils/obj/.compile.marker

${NATIVE_DIR}/binutils/obj/.compile.marker: \
    ${NATIVE_DIR}/binutils/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install binutils
########################################
native-binutils-install: \
    ${NATIVE_DIR}/binutils/obj/.install.marker

${NATIVE_DIR}/binutils/obj/.install.marker: \
    ${NATIVE_DIR}/binutils/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

#########################################
# Configure GMP
########################################
native-gmp-configure: \
    ${NATIVE_DIR}/gmp/obj/.config.marker

${NATIVE_DIR}/gmp/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker \
    ${NATIVE_DIR}/gmp/obj/.mkdir.marker \
    ${NATIVE_DIR}/root/.root.init.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile GMP
########################################
native-gmp-compile: \
    ${NATIVE_DIR}/gmp/obj/.compile.marker

${NATIVE_DIR}/gmp/obj/.compile.marker: \
    ${NATIVE_DIR}/gmp/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install GMP
########################################
native-gmp-install: \
    ${NATIVE_DIR}/gmp/install/.install.marker

${NATIVE_DIR}/gmp/install/.install.marker: \
    ${NATIVE_DIR}/gmp/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure MPFR
########################################
native-mpfr-configure: \
    ${NATIVE_DIR}/mpfr/obj/.config.marker

${NATIVE_DIR}/mpfr/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker\
    ${NATIVE_DIR}/mpfr/obj/.mkdir.marker \
    ${NATIVE_DIR}/gmp/install/.install.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile MPFR
########################################
native-mpfr-compile: \
    ${NATIVE_DIR}/mpfr/obj/.compile.marker

${NATIVE_DIR}/mpfr/obj/.compile.marker: \
    ${NATIVE_DIR}/mpfr/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install MPFR
########################################
native-mpfr-install: \
    ${NATIVE_DIR}/mpfr/install/.install.marker

${NATIVE_DIR}/mpfr/install/.install.marker: \
    ${NATIVE_DIR}/mpfr/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure MPC
########################################
native-mpc-configure: \
    ${NATIVE_DIR}/mpc/obj/.config.marker

${NATIVE_DIR}/mpc/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker \
    ${NATIVE_DIR}/mpc/obj/.mkdir.marker \
    ${NATIVE_DIR}/mpfr/install/.install.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile MPC
########################################
native-mpc-compile: \
    ${NATIVE_DIR}/mpc/obj/.compile.marker

${NATIVE_DIR}/mpc/obj/.compile.marker: \
    ${NATIVE_DIR}/mpc/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install MPC
########################################
native-mpc-install: \
    ${NATIVE_DIR}/mpc/install/.install.marker

${NATIVE_DIR}/mpc/install/.install.marker: \
    ${NATIVE_DIR}/mpc/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@


########################################
# Configure ppl
########################################
native-ppl-configure: \
    ${NATIVE_DIR}/ppl/obj/.config.marker

${NATIVE_DIR}/ppl/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker \
    ${NATIVE_DIR}/ppl/obj/.mkdir.marker \
    ${NATIVE_DIR}/gmp/install/.install.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile PPL
########################################
native-ppl-compile: \
    ${NATIVE_DIR}/ppl/obj/.compile.marker

${NATIVE_DIR}/ppl/obj/.compile.marker: \
    ${NATIVE_DIR}/ppl/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install PPL
########################################
native-ppl-install: \
    ${NATIVE_DIR}/ppl/install/.install.marker

${NATIVE_DIR}/ppl/install/.install.marker: \
    ${NATIVE_DIR}/ppl/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure CLooG
########################################
native-cloog-configure: \
    ${NATIVE_DIR}/cloog/obj/.config.marker

${NATIVE_DIR}/cloog/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker \
    ${NATIVE_DIR}/cloog/obj/.mkdir.marker \
    ${NATIVE_DIR}/gmp/install/.install.marker \
    ${NATIVE_DIR}/ppl/install/.install.marker \
    ${NATIVE_DIR}/piplib/install/.install.marker \
    ${NATIVE_DIR}/isl/install/.install.marker \
    ${NATIVE_DIR}/osl/install/.install.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile CLooG
########################################
native-cloog-compile: \
    ${NATIVE_DIR}/cloog/obj/.compile.marker

${NATIVE_DIR}/cloog/obj/.compile.marker: \
    ${NATIVE_DIR}/cloog/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install CLooG
########################################
native-cloog-install: \
    ${NATIVE_DIR}/cloog/install/.install.marker

${NATIVE_DIR}/cloog/install/.install.marker: \
    ${NATIVE_DIR}/cloog/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure PIPLIB
########################################
native-piplib-configure: \
    ${NATIVE_DIR}/piplib/obj/.config.marker

${NATIVE_DIR}/piplib/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker \
    ${NATIVE_DIR}/piplib/obj/.mkdir.marker \
    ${NATIVE_DIR}/gmp/install/.install.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile PIPLIB
########################################
native-piplib-compile: \
    ${NATIVE_DIR}/piplib/obj/.compile.marker

${NATIVE_DIR}/piplib/obj/.compile.marker: \
    ${NATIVE_DIR}/piplib/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install PIPLIB
########################################
native-piplib-install: \
    ${NATIVE_DIR}/piplib/install/.install.marker

${NATIVE_DIR}/piplib/install/.install.marker: \
    ${NATIVE_DIR}/piplib/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure OSL
########################################
native-osl-configure: \
    ${NATIVE_DIR}/osl/obj/.config.marker

${NATIVE_DIR}/osl/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker \
    ${NATIVE_DIR}/osl/obj/.mkdir.marker \
    ${NATIVE_DIR}/gmp/install/.install.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
             HOST_ARCH=${TARGET_ARCH} \
             TARGET_ARCH=${TARGET_ARCH} \
             BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile OSL
########################################
native-osl-compile: \
    ${NATIVE_DIR}/osl/obj/.compile.marker

${NATIVE_DIR}/osl/obj/.compile.marker: \
    ${NATIVE_DIR}/osl/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
             HOST_ARCH=${TARGET_ARCH} \
             TARGET_ARCH=${TARGET_ARCH} \
             BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install OSL
########################################
native-osl-install: \
    ${NATIVE_DIR}/osl/install/.install.marker

${NATIVE_DIR}/osl/install/.install.marker: \
    ${NATIVE_DIR}/osl/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
             HOST_ARCH=${TARGET_ARCH} \
             TARGET_ARCH=${TARGET_ARCH} \
             BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure ISL
########################################
native-isl-configure: \
    ${NATIVE_DIR}/isl/obj/.config.marker

${NATIVE_DIR}/isl/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.install.marker \
    ${NATIVE_DIR}/mingw-headers/obj/.install.marker \
    ${NATIVE_DIR}/isl/obj/.mkdir.marker \
    ${NATIVE_DIR}/piplib/install/.install.marker \
    ${NATIVE_DIR}/gmp/install/.install.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile ISL
########################################
native-isl-compile: \
    ${NATIVE_DIR}/isl/obj/.compile.marker

${NATIVE_DIR}/isl/obj/.compile.marker: \
    ${NATIVE_DIR}/isl/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install ISL
########################################
native-isl-install: \
    ${NATIVE_DIR}/isl/install/.install.marker

${NATIVE_DIR}/isl/install/.install.marker: \
    ${NATIVE_DIR}/isl/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# GCC cross compiling support - winsup
########################################
native-gcc-winsup: \
    ${NATIVE_DIR}/gcc/gcc/.winsup.marker

${NATIVE_DIR}/gcc/gcc/.winsup.marker: \
    ${BUILD_DIR}/.extract.marker \
    ${NATIVE_DIR}/gcc/gcc/.mkdir.marker \
    ${NATIVE_DIR}/root/.root.init.marker
ifneq (,$(filter MINGW%,$(shell uname -s)))
	-test -e ${BUILD_DIR}/gcc/gcc/winsup  && \
	  junction -d ${BUILD_DIR}/gcc/gcc/winsup
	junction ${BUILD_DIR}/gcc/gcc/winsup "${NATIVE_DIR}/root"
	test -e ${BUILD_DIR}/gcc/gcc/winsup
else
	-test -h ${BUILD_DIR}/gcc/gcc/winsup && \
	  rm ${BUILD_DIR}/gcc/gcc/winsup
	ln -s "../../../${NATIVE_DIR}/root" ${BUILD_DIR}/gcc/gcc/winsup
	test -h ${BUILD_DIR}/gcc/gcc/winsup
endif
	@touch $@

########################################
# Configure GCC
########################################
# PPL no longer needed
# ${NATIVE_DIR}/ppl/install/.install.marker

native-gcc-configure: \
    ${NATIVE_DIR}/gcc/obj/.config.marker

${NATIVE_DIR}/gcc/obj/.config.marker: \
    ${NATIVE_DIR}/gcc/gcc/.winsup.marker \
    ${NATIVE_DIR}/gcc/obj/.mkdir.marker \
    ${NATIVE_DIR}/binutils/obj/.install.marker \
    ${NATIVE_DIR}/gmp/install/.install.marker \
    ${NATIVE_DIR}/mpfr/install/.install.marker \
    ${NATIVE_DIR}/mpc/install/.install.marker \
    ${NATIVE_DIR}/isl/install/.install.marker \
    ${NATIVE_DIR}/piplib/install/.install.marker \
    ${NATIVE_DIR}/cloog/install/.install.marker \
    ${NATIVE_DIR}/root/.root.init.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure mingw-w64 CRT
########################################
native-crt-configure: \
    ${NATIVE_DIR}/mingw/obj/.config.marker

${NATIVE_DIR}/mingw/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.install.marker \
    ${NATIVE_DIR}/mingw/obj/.mkdir.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile mingw-w64 CRT
########################################
native-crt-compile: \
    ${NATIVE_DIR}/mingw/obj/.compile.marker

${NATIVE_DIR}/mingw/obj/.compile.marker: \
    ${NATIVE_DIR}/mingw/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install mingw-w64 CRT
########################################
native-crt-install: \
    ${NATIVE_DIR}/mingw/obj/.install.marker

${NATIVE_DIR}/mingw/obj/.install.marker: \
    ${NATIVE_DIR}/mingw/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Configure mingw-w64 winpthreads
########################################
native-winpthreads-configure: \
    ${NATIVE_DIR}/winpthreads/obj/.config.marker

${NATIVE_DIR}/winpthreads/obj/.config.marker: \
    ${BUILD_DIR}/gcc/obj/.bootstrap.install.marker \
    ${NATIVE_DIR}/winpthreads/obj/.mkdir.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile mingw-w64 winpthreads
########################################
native-winpthreads-compile: \
    ${NATIVE_DIR}/winpthreads/obj/.compile.marker

${NATIVE_DIR}/winpthreads/obj/.compile.marker: \
    ${NATIVE_DIR}/winpthreads/obj/.config.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install mingw-w64 winpthreads
########################################
native-winpthreads-install: \
    ${NATIVE_DIR}/winpthreads/obj/.install.marker

${NATIVE_DIR}/winpthreads/obj/.install.marker: \
    ${NATIVE_DIR}/winpthreads/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Compile libgcc
########################################

native-gcc-libgcc-compile: \
    ${NATIVE_DIR}/gcc/obj/.libgcc.compile.marker

${NATIVE_DIR}/gcc/obj/.libgcc.compile.marker: \
    ${NATIVE_DIR}/mingw/obj/.install.marker \
    ${NATIVE_DIR}${LIBGCC_WINPTHREAD_DEP_${USE_WINPTHREADS}}
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -C $(dir $@) all-target-libgcc
	@touch $@

########################################
# Install libgcc
########################################
native-gcc-libgcc-install: \
    ${NATIVE_DIR}/gcc/obj/.libgcc.install.marker

${NATIVE_DIR}/gcc/obj/.libgcc.install.marker: \
    ${NATIVE_DIR}/gcc/obj/.libgcc.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -C $(dir $@) install-target-libgcc
	@touch $@

########################################
# Prep pthreads-win32 from cvs
########################################
native-pthreads-prep: \
    ${NATIVE_DIR}/pthreads/.pthreads.prep

${NATIVE_DIR}/pthreads/.pthreads.prep: \
    ${NATIVE_DIR}/root/.root.init.marker \
    src/patches/.patches.pull.marker \
    src/pthreads/.pthreads.download.marker
	cp -prf src/pthreads ${NATIVE_DIR}/
	cp -p src/patches/pthreads_win32/w64sup.patch $(dir $@)
	cd $(dir $@) && patch -Np1 -i w64sup.patch
	cp -p $(dir $@)/config.h $(dir $@)pthreads_win32_config.h
	cp -p $(dir $@)/GNUmakefile $(dir $@)GNUmakefile.ori
	sed -e 's/HAVE_CONFIG_H/1/' \
	  -e 's/config.h/pthreads_win32_config.h/' \
	  < $(dir $@)/pthread.h >$(dir $@)pthread.h.out
	mv $(dir $@)/pthread.h.out $(dir $@)pthread.h
	@touch $@

########################################
# Build pthreads-win32 from cvs
########################################
native-pthreads-build: \
    ${NATIVE_DIR}/pthreads/.pthreads.build.${ENABLE_MULTILIB}

${NATIVE_DIR}/pthreads/.pthreads.build.Y: \
    ${NATIVE_DIR}/pthreads/.pthreads.build.x86_64-w64-mingw32 \
    ${NATIVE_DIR}/pthreads/.pthreads.build.i686-w64-mingw32
	@touch $@

${NATIVE_DIR}/pthreads/.pthreads.build.N: \
    ${NATIVE_DIR}/pthreads/.pthreads.build.${TARGET_ARCH}
	@touch $@

${NATIVE_DIR}/pthreads/.pthreads.build.x86_64-w64-mingw32: \
    ${NATIVE_DIR}/pthreads/.pthreads.prep \
    ${NATIVE_DIR}/mingw/obj/.install.marker \
    ${NATIVE_DIR}/gcc/obj/.libgcc.install.marker
	sed -e 's/dlltool$$/& -m i386:x86-64/' \
	  -e 's/gcc$$/& -m64/' \
	  -e 's/g++$$/& -m64/' \
	  -e 's/windres$$/& -F pe-x86-64/' \
	  -e 's/pthreadGC\$$(DLL_VER)/&-w64/g' \
	  -e 's/pthreadGCE\$$(DLL_VER)/&-w64/g' \
	  < $(dir $@)GNUmakefile.ori > $(dir $@)GNUmakefile
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -C $(dir $@) CROSS=${TARGET_ARCH}- $(PTHREADS_MAKE_ARGS)
	@touch $@

${NATIVE_DIR}/pthreads/.pthreads.build.i686-w64-mingw32: \
    ${NATIVE_DIR}/pthreads/.pthreads.prep \
    ${NATIVE_DIR}/mingw/obj/.install.marker \
    ${NATIVE_DIR}/gcc/obj/.libgcc.install.marker
	sed -e 's/dlltool$$/& -m i386/' \
	  -e 's/gcc$$/& -m32/' \
	  -e 's/g++$$/& -m32/' \
	  -e 's/windres$$/& -F pe-i386/' \
	  -e 's/pthreadGC\$$(DLL_VER)/&-w32/g' \
	  -e 's/pthreadGCE\$$(DLL_VER)/&-w32/g' \
	  < $(dir $@)GNUmakefile.ori > $(dir $@)GNUmakefile
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -C $(dir $@) CROSS=${TARGET_ARCH}- $(PTHREADS_MAKE_ARGS)
	@touch $@

########################################
# Install pthreads-win32 from cvs
########################################
ifeq (${TARGET_ARCH}, x86_64-w64-mingw32)
  NATIVE_PTHREAD_DLL := pthreadGC2-w64.dll
else
  NATIVE_PTHREAD_DLL := pthreadGC2-w32.dll
endif

native-pthreads-install: \
    ${NATIVE_DIR}/pthreads/.pthreads.install.${ENABLE_MULTILIB}

${NATIVE_DIR}/pthreads/.pthreads.install.common: \
    ${NATIVE_DIR}/pthreads/.pthreads.prep
	cp -p ${NATIVE_DIR}/pthreads/pthread.h \
	  ${NATIVE_DIR}/pthreads/sched.h \
	  ${NATIVE_DIR}/pthreads/semaphore.h \
	  ${NATIVE_DIR}/pthreads/pthreads_win32_config.h \
	  ${NATIVE_DIR}/root/${TARGET_ARCH}/include
	cp -p ${NATIVE_DIR}/pthreads/${NATIVE_PTHREAD_DLL} \
	  ${NATIVE_DIR}/root/${TARGET_ARCH}/lib/libpthread.a
	@touch $@

${NATIVE_DIR}/pthreads/.pthreads.install.Y: \
    ${NATIVE_DIR}/pthreads/.pthreads.build.Y \
    ${NATIVE_DIR}/pthreads/.pthreads.install.common \
    ${NATIVE_DIR}/pthreads/.pthreads.install.x86_64-w64-mingw32 \
    ${NATIVE_DIR}/pthreads/.pthreads.install.i686-w64-mingw32
	@touch $@

${NATIVE_DIR}/pthreads/.pthreads.install.N: \
    ${NATIVE_DIR}/pthreads/.pthreads.build.N \
    ${NATIVE_DIR}/pthreads/.pthreads.install.common \
    ${NATIVE_DIR}/pthreads/.pthreads.install.${TARGET_ARCH}
	@touch $@

${NATIVE_DIR}/pthreads/.pthreads.install.x86_64-w64-mingw32: \
    ${NATIVE_DIR}/pthreads/.pthreads.build.x86_64-w64-mingw32
	cp -p ${NATIVE_DIR}/pthreads/pthreadGC2-w64.dll \
	  ${NATIVE_DIR}/root/bin
	cp -fp ${NATIVE_DIR}/pthreads/pthreadGC2-w64.dll \
	  ${NATIVE_DIR}/root/${TARGET_ARCH}/lib64/libpthread.a
	@touch $@

${NATIVE_DIR}/pthreads/.pthreads.install.i686-w64-mingw32: \
    ${NATIVE_DIR}/pthreads/.pthreads.build.i686-w64-mingw32
	cp -p ${NATIVE_DIR}/pthreads/pthreadGC2-w32.dll \
	  ${NATIVE_DIR}/root/bin
	cp -fp ${NATIVE_DIR}/pthreads/pthreadGC2-w32.dll \
	  ${NATIVE_DIR}/root/${TARGET_ARCH}/lib32/libpthread.a
	@touch $@

########################################
# Compile full GCC
########################################
native-gcc-compile: \
    ${NATIVE_DIR}/gcc/obj/.compile.marker \
    ${NATIVE_DIR}/mingw/obj/.install.marker

${NATIVE_DIR}/gcc/obj/.compile.marker: \
    ${NATIVE_DIR}/gcc/obj/.config.marker \
    ${NATIVE_DIR}/mingw/obj/.install.marker \
	${NATIVE_DIR}${GCC_WINPTHREAD_DEP_${USE_WINPTHREADS}}
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Install full GCC
########################################
native-gcc-install: \
    ${NATIVE_DIR}/gcc/obj/.install.marker

${NATIVE_DIR}/gcc/obj/.install.marker: \
    ${NATIVE_DIR}/gcc/obj/.compile.marker
	PATH=$(realpath ${BUILD_DIR}/root/bin):$$PATH \
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} $@

########################################
# Create release tarball
########################################
native-release-archive: \
    native-${BIN_ARCHIVE}

native-${BIN_ARCHIVE}: \
    ${NATIVE_DIR}/gcc/obj/.install.marker
	$(MAKE) -f $(lastword ${MAKEFILE_LIST}) \
	     HOST_ARCH=${TARGET_ARCH} \
	     TARGET_ARCH=${TARGET_ARCH} \
	     BUILD_DIR=${NATIVE_DIR} pre-pack
	cd ${NATIVE_DIR}/root && \
	zip -r -9 ${CURDIR}/$(patsubst %.tar.bz2,%.zip,$@) \
	     . -x .*.marker *.*.marker


endif # native_dir != build_dir

################################################################################
# Helper targets
################################################################################

%/.mkdir.marker:
	-mkdir -p $(dir $@)
	@touch -t 197001020101 $@

################################################################################
# Host Tools Check (Check for required tools)
################################################################################
host-tools-check-helper = \
	@echo -n "Checking for${1}" \
	&& ($(call host-tools-check-helper-alternator,${2},${3}) \
	(echo -ne "\n[ Error $$? - Checked " && $(call host-tools-check-helper-alternator-error,${2}))) \
	&& echo -e "[OK]"

host-tools-check-helper-alternator = \
	$(foreach ex,${1},($(ex) $(or ${2},--version) &> /dev/null) ||)

host-tools-check-helper-alternator-error = \
	$(foreach ex,${1},echo -n "$(ex) " && ) \
	echo "]" && \
	false

host-tools-check-helper-gcc-list := gcc cc
host-tools-check-helper-cpp-list := g++ c++
host-tools-check-helper-wget-list := wget curl

host-tools-check::
	@echo Checking host tools
	@echo Note that the minimum required versions are not checked.
	$(call host-tools-check-helper, Concurrent Versions System, cvs)
	$(call host-tools-check-helper, Subversion, svn)
	$(call host-tools-check-helper, GNU Compiler Collection (gcc), $(host-tools-check-helper-gcc-list))
	$(call host-tools-check-helper, GNU Compiler Collection (g++), $(host-tools-check-helper-cpp-list))
	$(call host-tools-check-helper, GNU sed, sed)
	$(call host-tools-check-helper, GNU Awk, gawk)
	$(call host-tools-check-helper, patch, patch)
	$(call host-tools-check-helper, GNU tar, tar)
	$(call host-tools-check-helper, bzip2, bzip2,--help)
	$(call host-tools-check-helper, gzip, gzip)
	$(call host-tools-check-helper, wget or curl, $(host-tools-check-helper-wget-list))
	$(call host-tools-check-helper, flex, flex)
	$(call host-tools-check-helper, GNU bison, bison)
	$(call host-tools-check-helper, GNU gperf, gperf)
	$(call host-tools-check-helper, GNU texinfo (makeinfo), makeinfo)
	$(call host-tools-check-helper, Perl, perl)
	@echo All needed host tools seem to work fine!

help::
	@echo Available targets:
	@echo -e $(foreach t,all ${TARGETS} $@,\\t${t}\\n)

# build only the cross-compiler by default
all:: \
  ${BIN_ARCHIVE}

TARGETS := \
  host-tools-check \
  patch-pull \
  binutils-pull \
  gcc-pull \
  gmp-download \
  gmp-extract \
  mpfr-download \
  mpfr-extract \
  mpc-download \
  mpc-extract \
  ppl-download \
  ppl-extract \
  cloog-download \
  cloog-extract \
  mingw-pull \
  src-archive \
  src-extract \
  binutils-configure \
  binutils-compile \
  binutils-install \
  gmp-configure \
  gmp-compile \
  gmp-install \
  mpfr-configure \
  mpfr-compile \
  mpfr-install \
  mpc-configure \
  mpc-compile \
  mpc-install \
  ppl-configure \
  ppl-compile \
  ppl-install \
  cloog-configure \
  cloog-compile \
  cloog-install \
  gcc-configure \
  gcc-bootstrap-compile \
  gcc-bootstrap-install \
  headers-configure \
  headers-install \
  crt-configure \
  crt-compile \
  crt-install \
  gcc-compile \
  gcc-install \
  release-archive \
  native-binutils-configure \
  native-binutils-compile \
  native-binutils-install \
  native-gmp-configure \
  native-gmp-compile \
  native-gmp-install \
  native-mpfr-configure \
  native-mpfr-compile \
  native-mpfr-install \
  native-mpc-configure \
  native-mpc-compile \
  native-mpc-install \
  native-ppl-configure \
  native-ppl-compile \
  native-ppl-install \
  native-cloog-configure \
  native-cloog-compile \
  native-cloog-install \
  native-gcc-configure \
  native-headers-configure \
  native-headers-install \
  native-crt-configure \
  native-crt-compile \
  native-crt-install \
  native-gcc-compile \
  native-gcc-install \
  native-release-archive \
  pthreads-download \
  pthreads-prep \
  pthreads-build \
  pthreads-install \
  winpthreads-configure \
  winpthreads-download \
  winpthreads-compile \
  winpthreads-install \
  native-winpthreads-configure \
  native-winpthreads-compile \
  native-winpthreads-install \
  gcc-libgcc-compile \
  gcc-libgcc-install \
  native-pthreads-prep \
  native-pthreads-build \
  native-pthreads-install \
  native-gcc-libgcc-compile \
  native-gcc-libgcc-install \
  isl-configure \
  isl-download \
  isl-compile \
  isl-install \
  osl-configure \
  osl-download \
  osl-compile \
  osl-install \
  piplib-configure \
  piplib-download \
  piplib-compile \
  piplib-install \
  native-isl-configure \
  native-isl-compile \
  native-isl-install \
  native-osl-configure \
  native-osl-compile \
  native-osl-install \
  native-piplib-configure \
  native-piplib-compile \
  native-piplib-install \
  pre-pack


.PHONY: \
  all \
  ${TARGETS} \
  help
