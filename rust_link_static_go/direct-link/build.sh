#!/bin/bash

make -C ../../libmatrix_go
cp -R ../../libmatrix_go/build .

echo ""
echo "================================="
echo "Build linux executable"
echo "================================="
echo ""
cross build --target x86_64-unknown-linux-gnu

echo ""
echo "========================================="
echo "Build the workaround library for windows"
echo "========================================="
echo ""
x86_64-w64-mingw32-gcc-posix -c windows_workaround.c -o workaround.o
x86_64-w64-mingw32-ar rcs libworkaround.a workaround.o
mv libworkaround.a build/win/x64/libworkaround.a
rm workaround.o
echo "workaround library built"

echo ""
echo "================================="
echo "Build windows executable"
echo "================================="
echo ""
cross build --target x86_64-pc-windows-gnu

echo ""
echo "================================="
echo "Finished building"
echo "================================="
echo ""

# cross build --target i686-unknown-linux-gnu
# cross build --target i686-pc-windows-gnu
