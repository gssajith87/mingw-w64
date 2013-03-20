#!/bin/bash -e
#Set this to your host!!
HST=x86_64-pc-linux
TGT=x86_64-w64-mingw32
BITS=64

#Option defaults
build="false"
usecvs="true"
update="true"
makedist="false"
gccrev="HEAD"
out=/dev/null

#Third party packages
gmpver=gmp-5.1.1
gmp=ftp://ftp.gnu.org/gnu/gmp/${gmpver}.tar.bz2
mpfrver=mpfr-3.0.0
mpfr=http://www.mpfr.org/mpfr-current/${mpfrver}.tar.bz2
mpcver=mpc-0.8.2
mpc=http://www.multiprecision.org/mpc/download/${mpcver}.tar.gz

while opt=$1 && shift; do
  case "$opt" in
    "--help" )
      cat << EOF
    This build script will setup an entire buildroot environment consisting of binutils, gcc (and the
    required gmp / mpfr), and the mingw-w64 crt.  It will download all major dependencies, create
    the directory structure, and will optionally build the binaries as well.  The syntax is [Ed. note: 
    in all honesty, it used to be a lot simpler...] quite simple:

      $0 [ --help ] [ --nocvs ] [ --noupdate ] [ --build ] [ --makedist ] [ --gccrev N ] [ --jobs N ]
      
    --help	Causes all other arguments to be ignored and results in the display of
		this text.

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
    
    --gccrev N  Specify a particular gcc revision to pull.  Since gcc is an oft-changing product, it may be 
                desirable to pull a version that is not HEAD, for instance if the trunk breaks or if testing
                older versions.  Whatever number is specified for N will be grabbed from svn.  Only numbers
                will work in this field, and the default if not specified is "HEAD".

    --jobs N    Specify the number of jobs to submit to make.  This translates into the -j number supplied
                to make for each built project.  Not specifying N is the same as not specifying --jobs at all.

    --32bit     Builds a 32 bit toolchain (using mingw-w64 sources)

EOF
    exit
    ;;

    "--build" )
      build="true"
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

    "--gccrev" )
      if [[ "$1" != --* ]]; then
        if [ ! $1 -gt 0 ] ; then
          echo "Bad GCC revision: $1" >&2
          exit 1
        fi
        gccrev=$1
      fi
      shift
      ;;

    "--jobs" )
      if [[ "$1" != --* ]]; then
        if [ ! $1 -gt 0 ] ; then
          echo "Bad job count: $1" >&2
          exit 1
        fi
        j="-j $1"
      fi
      shift
      ;;

   "--32bit" )
      TGT=i686-pc-mingw32
      BITS=32
      ;;
  esac
done

RT=root-$HST-$BITS
PF=`pwd`/$RT
BD=`pwd`/build
DIRS="$PF $PF/$TGT $BD $BD/binutils $BD/binutils/build-$HST-$BITS $BD/gcc-svn
      $BD/gcc-svn/build-$HST-$BITS $BD/mingw $BD/mingw/build-$HST-$BITS"
baseopts="--prefix=$PF --with-sysroot=$PF --target=$TGT"

if [[ $update == "true" ]]; then
  echo "Creating directory tree:"
  echo "$PF -- sysroot directory tree"
  echo "$BD -- build directory tree"
  echo ""

  for i in $DIRS; do
    [ -d $i ] && echo "Warning: $i preexisting, skipping directory creation" || mkdir $i
  done
  [ -h $PF/mingw ] || ln -s $TGT $PF/mingw

  echo "Downloading binutils.." && cd $BD/binutils
  if [[ $usecvs == "true" ]]; then
    cvs -Qz 9 -d :pserver:anoncvs@sourceware.org:/cvs/src co binutils
  else
    wget -qO- ftp://sourceware.org/pub/binutils/snapshots/binutils.tar.bz2 | tar xjf - && mv binutils-* src
  fi

  echo "Downloading gcc.." && cd $BD/gcc-svn
  svn -q checkout svn://gcc.gnu.org/svn/gcc/trunk gcc -r $gccrev

  echo "Downloading additional required libraries for gcc.." && cd gcc
  for i in gmp mpfr mpc; do
    ver=${i}ver
    [ -d $i ] && echo "Warning: $i preexisting, skipping download" || ( wget -qO- ${!i} | tar xjf - && mv ${!ver} $i )
  done
  cd ..

  echo "Downloading crt and headers.." && cd $BD/mingw
  svn -q co https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/trunk .
  dest=$PF/$TGT/include
  [ -d $dest ] && echo $dest already exists || ( cp -prf mingw-w64-headers/include $dest && find $dest -name ".svn" | xargs rm -rf )

  echo "Root setup complete."
fi

if [[ $build == "true" ]]; then
  echo "Compiling binutils.." && cd $BD/binutils/build-$HST-$BITS
  ../src/configure $baseopts > $out && make -s $j > $out && make install > $out || exit 1

  echo "Compiling bootstrap gcc.." && cd $BD/gcc-svn/build-$HST-$BITS
  ../gcc/configure $baseopts --enable-fully-dynamic-string --disable-multilib > $out && make -s $j all-gcc > $out && make install-gcc > $out || exit 1
  export PATH=$PF/bin:$PATH

  echo "Compiling crt.." && cd $BD/mingw/build-$HST-$BITS
  _configure_args="--prefix=$PF --with-sysroot=$PF --host=$TGT"
  if [[ "$BITS" == "32" ]] ; then
    _configure_args="$_configure_args --enable-lib32 --disable-lib64"
  fi
  ../mingw-w64-crt/configure $_configure_args > $out && make -s $j > $out && make install > $out || exit 1

  echo "Compiling full gcc.." && cd $BD/gcc-svn/build-$HST-$BITS
  make -s $j > $out && make install > $out || exit 1

  cd $PF
  echo "Done building."
fi

if [[ $makedist == "true" ]]; then
  cd $PF
  tarname=mingw-w$BITS-bin_`uname`_`$PF/bin/$TGT-gcc --version | head -1 | awk '{print $4}'`.tar.bz2
  tar cjf ../$tarname --owner 0 --group 0 * || exit 1
  echo "Distribution: $tarname"
  cd ..
fi
