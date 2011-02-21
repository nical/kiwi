#!/bin/sh

cd ./build/test

./core/FactoryTest  &&
./core/NodeTest &&
./generic/ArrayContainerTest && 
./generic/StructuredArrayContainerTest && 
./generic/PointTest &&
./generic/ValueContainerTest &&
./generic/PointVectorContainerTest &&
./text/PlainTextContainerTest &&
./utils/ConnectorTest &&
./utils/UnorderedArrayTest &&
./utils/typesTest &&
./utils/randomTest &&
./image/CairoImageContainerTest &&
./image/ImageContainerTest &&
./image/MixedImageTest &&
./image/CopyImageTest &&
./image/ChannelOffsetFilterTest &&
./core/FilterTest &&

echo '\n\n--end of the test suite--\n\n'
