#!/bin/sh



#############################################
# Test if a build directory already exist.  #
# If it's true, then remove it recursively. #
#############################################
if [ -d "build" ]
then
  rm -rf build
fi

###########################
# Build and install kiwi. #
###########################

./BUILD.sh
