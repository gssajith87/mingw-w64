#!/bin/bash

set -e

WINE_DIR=$1

if test -z $WINE_DIR; then
    echo "Usage: wine-impot.sh wine_dir"
    exit 1
fi

import_header() {
    if test -z "$(grep WINELIB_NAME_AW\\\|DECL_WINELIB_TYPE_AW $WINE_DIR/include/$1)"; then
        cp $WINE_DIR/include/$1 $2
    else
        echo '#include <_mingw_unicode.h>' >$2/$1
        cat $WINE_DIR/include/$1 >>$2/$1
        sed -i 's/\bWINELIB_NAME_AW\b/__MINGW_NAME_AW/g' $2/$1
        sed -i 's/\bDECL_WINELIB_TYPE_AW\b/__MINGW_TYPEDEF_AW/g' $2/$1
    fi
    sed -i 's/\bBOOL\b/WINBOOL/g' $2/$1
}

# headers
for f in corerror.h mscat.h winhttp.h winineti.h; do
    import_header $f include
done

# IDLs
for f in fusion mscoree optary wincodec xmllite; do
    cp $WINE_DIR/include/$f.idl idl
    import_header $f.h include
done

# DirectX headers
for f in d3d10effect.h d3d10misc.h d3d10shader.h xinput.h; do
    import_header $f direct-x/include
done

# DirectX IDLs
for f in d3d10 dxgi dxgitype; do
    cp $WINE_DIR/include/$f.idl direct-x/include
    import_header $f.h direct-x/include
done

