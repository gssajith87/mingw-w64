#!/bin/bash -e
TGT=x86_64-pc-mingw32
PF=`pwd`/root
BD=`pwd`/build
DIRS="$PF $PF/$TGT $BD $BD/binutils $BD/binutils/build-$TGT $BD/gcc-svn $BD/gcc-svn/build-$TGT $BD/mingw $BD/mingw/build-$TGT"
EXE=
build="false"
usecvs="true"
update="true"
makedist="false"
gmpver=gmp-4.2.2
gmp=ftp://ftp.gnu.org/gnu/gmp/${gmpver}.tar.bz2
mpfrver=mpfr-2.3.0
mpfr=http://www.mpfr.org/mpfr-current/${mpfrver}.tar.bz2

while opt=$1 && shift; do
  case "$opt" in
    "--help" )
      cat << EOF
    This build script will setup an entire buildroot environment consisting of binutils, gcc (and the
    required gmp / mpfr), and the mingw-w64 crt.  It will download all major dependencies, create
    the directory structure, and will optionally build the binaries as well.  The syntax is quite simple:

      $0 [ --help ] [ --build ] [ --noexe ] [ --nocvs ] [ --noupdate ]
      
    --help	Causes all other arguments to be ignored and results in the display of
		this text.

    --noexe 	For systems where executable files do not have ".exe" at the end.  The build
		system is not fully automatic yet, so this is a temporary thing which will be 
		deprecated and removed once the autotools build system is complete.

    --nocvs 	When cvs is otherwise unavailable, items that require cvs have alternate means by which to
		acquire the source code.  For instance, binutils offers a daily snapshot archive.  Non-cvs
		downloads will not be as up to date as the cvs repository, and as such this is provided
		only as a fallback.

    --noupdate  Inhibit downloading or updating the source code repositories.  This can greatly speed up
                rebuilds when you want to get by the 'svn up' of gcc quickly.

    --build	Continue past the downloading stage and begin building.  First it builds binutils,
		and then a bootstrap compiler.  Both binutils and gcc use the same basic options,
		with gcc requiring an additional argument to specify the desired languages.  Third 
		in the build process is the crt, which is installed into (buildroot)/x86_64-pc-mingw32/lib.
		The mingw symlink will hopefully go away in future versions.  With the crt installed,
		the full gcc toolchain can be build and installed, and this script takes care of it.

		Without providing the --build option, all components are downloaded and the headers are
		installed in the basic directory structure.  Running the command multiple times will update
		everything to the latest versions.  Using the --build command repeatedly will update any
		source files that have changed, and reinstall fresh copies of the sysroot.
    
		Keep in mind that this is all very temporary, and is provided as a convenience.  Please
		direct all inquiries to the sourceforge project at:
		https://sourceforge.net/projects/mingw-w64/

    --makedist  This will tar up the root directory for purposes of distribution.
    
EOF
    exit
    ;;

    "--build" )
      build="true"
      ;;

    "--noexe" )
      EXE="EXEEXT="
      ;;

    "--nocvs" )
      usecvs="false"
      ;;

    "--noupdate" )
      update="false"
      ;;

    "--makedist" )
      makedist="true"
      ;;

    "--help" )
  esac
done

if [[ $update == "true" ]]; then
  echo "Creating directory tree:"
  echo "$PF -- sysroot directory tree"
  echo "$BD -- build directory tree"
  echo ""

  for i in $DIRS; do
    [ -d $i ] && echo "Warning: $i preexisting, skipping directory creation" || mkdir $i
  done
  [ -h mingw ] || ln -s $TGT $PF/mingw

  echo "Downloading binutils.." && cd $BD/binutils
  if [[ $usecvs == "true" ]]; then
    cvs -Qz 9 -d :pserver:anoncvs@sourceware.org:/cvs/src co binutils
  else
    wget -qO- ftp://sourceware.org/pub/binutils/snapshots/binutils.tar.bz2 | tar xjf - && mv binutils-* src
  fi

  echo "Downloading gcc.." && cd $BD/gcc-svn
  svn -q checkout svn://gcc.gnu.org/svn/gcc/trunk gcc

  echo "Downloading additional required libraries for gcc.." && cd gcc
  for i in gmp mpfr; do
    ver=${i}ver
    [ -d $i ] && echo "Warning: $i preexisting, skipping download" || ( wget -qO- ${!i} | tar xjf - && mv ${!ver} $i )
  done
  cd ..

  echo "Downloading crt and headers.." && cd $BD/mingw
  svn -q co https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/trunk .
  dest=$PF/$TGT/include
  [ -d $dest ] && echo $dest already exists || ( mv mingw-w64-headers/include $dest && find $dest -name ".svn" | xargs rm -rf )

  echo "Root setup complete."
fi

if [[ $build == "true" ]]; then
  echo "Compiling binutils.." && cd $BD/binutils/$TGT
  ../src/configure --prefix=$PF --with-sysroot=$PF --target=$TGT > /dev/null && make > /dev/null || exit
  make install > /dev/null || exit

  echo "Compiling bootstrap gcc.." && cd $BD/gcc-svn/$TGT
  ../gcc/configure --prefix=$PF --with-sysroot=$PF --target=$TGT  > /dev/null && make all-gcc > /dev/null || exit
  make install-gcc > /dev/null || exit

  echo "Compiling crt.." && cd $BD/mingw/mingw-w64-crt
  make prefix=$PF $EXE > /dev/null || exit
  echo "Installing crt.."
  cp -pv CRT_fp10.o CRT_fp8.o binmode.o txtmode.o crtbegin.o crtend.o crt1.o crt2.o dllcrt1.o dllcrt2.o $PF/$TGT/lib || exit
  echo "Installing libs.."
  for i in `find . -name "*.a"`; do 
    cp -p $i $PF/$TGT/lib || exit
  done

  echo "Compiling full gcc.." && cd $BD/gcc-svn/$TGT
  make > /dev/null || exit
  make install > /dev/null || exit

  cd $PF
  echo "Done building."
fi

if [[ $makedist == "true" ]]; then
  cd $PF/..
  tar cjf mingw-w64-bin-`uname`-`$PF/bin/$TGT-gcc --version | head -1 | awk '{print $4}'`.tar.bz2 --owner root --group root $PF
fi
