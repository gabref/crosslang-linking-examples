#!/bin/bash

# https://stackoverflow.com/questions/41566495/golang-how-to-cross-compile-on-linux-for-windows

is_installed() {
    dpkg -l | grep -q "$1"
}

sudo dpkg --add-architecture i386 && sudo apt-get update

if ! is_installed "libz-mingw-w64-dev"; then
    sudo apt-get install --assume-yes --no-install-recommends libz-mingw-w64-dev
fi

if ! is_installed "g++-mingw-w64-x86-64"; then
    sudo apt-get install --assume-yes --no-install-recommends g++-mingw-w64-x86-64
fi

if ! is_installed "gfortran-mingw-w64-x86-64"; then
    sudo apt-get install --assume-yes --no-install-recommends gfortran-mingw-w64-x86-64
fi
