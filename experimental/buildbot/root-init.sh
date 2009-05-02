#!/bin/bash -x

[ -d build ] || mkdir build
[ -d build/root ] || mkdir build/root
[ -d "build/root/$TGT" ] || mkdir "build/root/$TGT"

case $(uname -s) in
	MINGW*)
		if [ ! -e build/root/mingw ] ; then
			junction build/root/mingw "build/root/$TGT" || exit 1
		fi
	;;
	*)
		if [ ! -h build/root/mingw ] ; then
			ln -s "$TGT" build/root/mingw || exit 1
		fi
	;;
esac

