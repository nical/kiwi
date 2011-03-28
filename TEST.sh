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



cd ./build/test

if [ "$mpl" = "yes" ]
then
./mpl/TypeListTest &&
./mpl/TupleTest ||
exit
fi

if [ "$generic" = "yes" ]
then
./generic/ArrayContainerTest && 
./generic/StructuredArrayContainerTest && 
./generic/PointTest &&
./generic/NumberContainerTest &&
./generic/PointVectorContainerTest &&
./generic/RectangleContainerTest ||
exit
fi

if [ "$core" = "yes" ]
then
./core/FactoryTest  &&
#./core/NodeTest &&
./core/StaticNodeTest &&
./core/FilterTest ||
exit
fi

if [ "$utils" = "yes" ]
then
#./utils/ClassInfoTest &&
./utils/ConnectorTest &&
./utils/UnorderedArrayTest &&
./utils/typesTest &&
./utils/randomTest ||
exit
fi

if [ "$image" = "yes" ]
then
./image/CairoImageContainerTest &&
./image/MixedImageTest &&
./image/CopyImageTest &&
./image/LinearGradientContainerTest &&
./image/ChannelOffsetFilterTest &&
./image/ImageContainerTest ||
exit
fi

if [ "$text" = "yes" ]
then
#./text/PlainTextContainerTest &&
./text/PlainTextLoaderTest ||
exit
fi

echo '\n\n end of the test suite--\n\n'
