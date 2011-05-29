#!/bin/sh


cd ./src/kiwi/


if [ "$1" = "install" ]
then
echo 'Will now build and install the Kiwi library\n'
sudo scons -j4 install
else
echo 'Will now build the Kiwi library\n'
scons -j4
fi

cd ../../
