#!/bin/bash
PF=`pwd`
TGT=x86_64-pc-mingw32
opt=$1 && shift
gmpver=gmp-4.2.1
gmp=ftp://ftp.gnu.org/gnu/gmp/${gmpver}.tar.bz2
mpfrver=mpfr-2.2.1
mpfr=http://www.mpfr.org/mpfr-current/${mpfrver}.tar.bz2

[ -h mingw ] || ln -s $TGT mingw

for i in $TGT build build/binutils build/binutils/build64 build/gcc-svn build/gcc-svn/build64 build/mingw build/mingw/build64; do
  [ -d $i ] && echo $i preexisting || mkdir $i
done

cd build

echo "Downloading binutils.." && cd binutils
cvs -Qz 9 -d :pserver:anoncvs@sourceware.org:/cvs/src co binutils

echo "Downloading gcc.." && cd ../gcc-svn
svn -q checkout svn://gcc.gnu.org/svn/gcc/trunk gcc

echo "Downloading additional required libraries for gcc.."
cd gcc
for i in gmp mpfr; do
  ver=${i}ver
  [ -d $i ] && echo $i preexisting || ( wget -qO- ${!i} | tar xjf - && mv ${!ver} $i )
done
cd ..

echo "Downloading crt and headers.." && cd ../mingw
svn -q co https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/trunk .
[ -d $PF/$TGT/include ] && echo $PF/$TGT/include already exists || mv mingw-w64-headers/include $PF/$TGT

echo "Root setup complete."


[[ $opt != "build" ]] && exit

echo "Compiling binutils.." && cd ../binutils/build64
../src/configure --prefix=$PF --with-sysroot=$PF --disable-nls --target=$TGT $* > /dev/null && make > /dev/null
make install > /dev/null

echo "Compiling bootstrap gcc.." && cd ../../gcc-svn/build64
../gcc/configure --prefix=$PF --with-sysroot=$PF --target=$TGT --disable-nls $* > /dev/null && make all-gcc > /dev/null
make install-gcc > /dev/null

echo "Compiling crt.." && cd ../../mingw/mingw-w64-crt
make prefix=$PF > /dev/null
cp -pv CRT_fp10.o CRT_fp8.o binmode.o txtmode.o crtbegin.o crtend.o crt1.o crt2.o dllcrt1.o dllcrt2.o $PF/$TGT/lib
for i in `find . -name "*.a"`; do
  cp -pv $i $PF/$TGT/lib
done

echo "Compiling full gcc.." && cd ../../gcc-svn/build64
make > /dev/null
make install > /dev/null

cd $PF
echo "\nDone."
