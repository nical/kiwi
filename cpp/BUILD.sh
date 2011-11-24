#!/bin/sh
echo "-- Kiwi build"
if [ -d "build" ]
then
  echo " "
else
  echo "-- Creating build directories"
  mkdir build;
  mkdir build/test
  mkdir build/test/core
  cd build
  cmake ..
  cd ..
fi


cd ./build
echo "-- Invoking make"
make -j4 && cp -f src/kiwi/libkiwicpp.a ..

cd ..


