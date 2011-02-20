#!/bin/sh

cd ./build/test

./core/FactoryTest  &&
./core/NodeTest &&
./generic/ArrayContainerTest && 
./generic/StructuredArrayContainerTest && 
./generic/PointTest &&
./generic/ValueContainerTest &&
./generic/PointVectorContainerTest &&
./image/CairoImageContainerTest &&
./text/PlainTextContainerTest &&
./utils/ConnectorTest &&
./utils/UnorderedArrayTest &&
./utils/typesTest &&
./utils/randomTest &&
./image/ImageContainerTest &&
./image/MixedImageTest &&
./image/CopyImageTest &&
./core/FilterTest &&

echo '\n\n--end of the test suite--\n\n'
