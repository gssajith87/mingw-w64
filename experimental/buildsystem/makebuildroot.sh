#!/bin/bash
PF=`pwd`
TGT=x86_64-pc-mingw32

[ -h mingw ] || ln -s $TGT mingw

for i in $TGT build build/binutils build/binutils/build64 build/gcc-svn build/gcc-svn/build64 build/kai; do
  [ -d $i ] && echo $i already exists || mkdir $i
done

cd build

echo "Downloading binutils.." && cd binutils
cvs -Qz 9 -d :pserver:anoncvs@sourceware.org:/cvs/src co binutils

echo "Downloading gcc.." && cd ../gcc-svn
svn -q checkout svn://gcc.gnu.org/svn/gcc/trunk gcc

echo "Downloading crt.." && cd ../kai
wget -Nq http://downloads.sourceforge.net/mingw/mingw-w64-crt-20070802.tar.bz2
echo "Downloading headers.."
wget -Nq http://downloads.sourceforge.net/mingw/mingw-w64-headers-20070802.tar.bz2
echo "Extracting.."
for i in *bz2; do
  tar xf $i
done
[ -d $PF/$TGT/include ] && echo $PF/$TGT/include already exists || mv include $PF/$TGT

echo "Root setup complete."


[ $1 != "build" ] && exit
shift

echo "Compiling binutils.." && cd ../binutils/build64
../src/configure --prefix=$PF --with-sysroot=$PF --disable-nls --target=$TGT $* > /dev/null && make > /dev/null
make install > /dev/null

echo "Compiling bootstrap gcc.." && cd ../../gcc-svn/build64
../gcc/configure --prefix=$PF --with-sysroot=$PF --target=$TGT --disable-nls --enable-languages=c $* > /dev/null && make all-gcc > /dev/null
make install-gcc > /dev/null

echo "Compiling crt.." && cd ../../kai/mwcrt_noat
make prefix=$PF > /dev/null
cp CRT_fp10.o CRT_fp8.o binmode.o txtmode.o crtbegin.o crtend.o crt1.o crt2.o dllcrt1.o dllcrt2.o /tmp/myroot/$TGT/lib
for i in `find . -name "*.a"`; do
  cp -v $i /tmp/myroot/$TGT/lib
done

echo "Compiling full gcc.. " && cd ../../gcc-svn/build64
make > /dev/null
make install > /dev/null

cd $PF
echo "\nDone."
