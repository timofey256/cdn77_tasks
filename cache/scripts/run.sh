#!/bin/bash

gcc -fPIC -c -o square.o square.c

gcc -shared -Wl,-soname,libsquare.so -o libsquare.so square.o

export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

luajit script.lua
