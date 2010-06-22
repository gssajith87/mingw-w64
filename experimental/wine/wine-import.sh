#!/bin/bash

set -e

WINE_DIR=$1

if test -z $WINE_DIR; then
    echo "Usage: wine-impot.sh wine_dir"
    exit 1
fi

# headers
for f in corerror.h mscat.h winhttp.h; do
    cp $WINE_DIR/include/$f include
done

# IDLs
for f in fusion mscoree optary wincodec xmllite; do
    cp $WINE_DIR/include/$f.idl idl
    cp $WINE_DIR/include/$f.h include
done

# DirectX headers
for f in d3d10effect.h d3d10misc.h d3d10shader.h xinput.h; do
    cp $WINE_DIR/include/$f direct-x/include
done

# DirectX IDLs
for f in d3d10 dxgi dxgitype; do
    cp $WINE_DIR/include/$f.idl direct-x/include
    cp $WINE_DIR/include/$f.h direct-x/include
done

