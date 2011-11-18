#!/bin/sh


cd ./build

make -j4 && cp -f src/kiwi/libkiwicpp.a ..

cd ..


