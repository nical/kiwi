#!/bin/sh



#############################################
# Test if a build directory already exist.  #
# If it's true, then remove it recursively. #
#############################################
if [ -d "build" ]
then
  rm -rf build/*
else
  mkdir build;
fi


###########################
# Build and install kiwi. #
###########################
cd build
mkdir test &&
mkdir test/core
mkdir test/mpl
mkdir test/generic
mkdir test/text
mkdir test/image
mkdir test/utils
mkdir test/audio
cmake .. &&
make -j4 &&
cd .. &&
ln -s build/src/software/kiwi kiwi

