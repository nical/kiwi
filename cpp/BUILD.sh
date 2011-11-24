#!/bin/sh

if [ -d "build" ]
then
  echo " "
else
  mkdir build;
  mkdir build/test
  mkdir build/test/core
fi


cd ./build

make -j4 && cp -f src/kiwi/libkiwicpp.a ..

cd ..


