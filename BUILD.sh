#!/bin/sh


if [ -d "build" ];
then
	echo "--build directory already crated" 
	if [ -f "build/Makefile" ];
	then
		echo "--Makefile already generated" 
		cd build;
		make -j4 &&
		cd ..
	else
	  ./REBUILD.sh
	fi
else
	./REBUILD.sh
fi








