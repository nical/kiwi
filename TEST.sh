#!/bin/sh

generic="yes"; core="yes"; image="yes"; text="yes"; utils="yes"; mpl="yes"

echo '\nTest suite - target: '$1'\n\n'

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



cd ./test

scons -j4 || exit
echo '\n\n'

if [ "$mpl" = "yes" ]
then
./mpl/TypeListTest &&
./mpl/TupleTest &&
./mpl/MakeContainerTest ||
exit
fi

if [ "$generic" = "yes" ]
then
echo 'no test for target: generic\n' ||
exit
fi

if [ "$core" = "yes" ]
then
./core/PortTest ||
exit
fi

if [ "$utils" = "yes" ]
then
./utils/DebugStreamTest ||
exit
fi

if [ "$image" = "yes" ]
then
echo 'no test for target: image' ||
exit
fi

if [ "$text" = "yes" ]
then
echo 'no test for target: text' ||
exit
fi

echo '\n\n end of the test suite--\n'
