#!/bin/sh


########################################################
# Test if a symbolic link to executable already exist. #
# If it's true, then remove it.                        #
########################################################
if [ -L "kiwi" ];
then
  rm kiwi;
fi


#############################################
# Test if a build directory already exist.  #
# If it's true, then remove it recursively. #
#############################################
if [ -d "build" ];
then
  rm -rf build/*;
else
  mkdir build;
fi


###########################
# Build and install kiwi. #
###########################
cd build;
mkdir test &&
mkdir test/core;
mkdir test/generic;
mkdir test/text;
mkdir test/image;
cmake .. &&
make -j4 &&
cd .. &&
ln -s build/src/software/kiwi kiwi;

