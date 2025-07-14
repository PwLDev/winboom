#!/bin/bash

# clean previous builds
rm -rf build32 build64
mkdir build32 build64

# build for x64
cmake -B build64 -S . -DCMAKE_TOOLCHAIN_FILE=toolchain-win64.cmake
cmake --build build64

# build for x86
cmake -B build32 -S . -DCMAKE_TOOLCHAIN_FILE=toolchain-win32.cmake
cmake --build build32

# organise the binaries in a dist folder
mkdir dist
mv build32/winboom.exe dist/winboom32.exe
mv build64/winboom.exe dist/winboom64.exe