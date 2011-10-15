#!/bin/sh

generic="yes"; core="yes"; image="yes"; text="yes"; utils="yes"; mpl="yes"

if [ "$1" = "generic" ]
then
	core="no"; image="no"; text="no"; utils="no"; mpl="no"
fi

if [ "$1" = "core" ]
then
	generic="no"; image="no"; text="no"; utils="no"; mpl="no"
fi
if [ "$1" = "image" ]
then
	core="no"; generic="no"; text="no"; utils="no"; mpl="no"
fi

if [ "$1" = "text" ]
then
	core="no"; generic="no"; image="no"; utils="no"; mpl="no"
fi

if [ "$1" = "utils" ]
then
	core="no"; generic="no"; image="no"; text="no"; mpl="no"
fi

if [ "$1" = "mpl" ]
then
	core="no"; generic="no"; image="no"; text="no"; utils="no"
fi



./BUILD.sh || exit

echo '\n'

if [ "$core" = "yes" ]
then
./build/test/core/Container_Test &&
./build/test/core/Node_Test &&
./build/test/core/Algorithm_Test ||
exit
fi

echo '--end of the test suite\n'
