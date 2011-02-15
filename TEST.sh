#!/bin/sh

cd ./build/test

./core/FactoryTest  &&
./core/NodeTest &&
./generic/ArrayContainerTest && 
./generic/StructuredArrayContainerTest && 
./generic/PointTest &&
./generic/ValueContainerTest &&
./image/CairoImageContainerTest &&
./text/PlainTextContainerTest &&
./utils/ConnectorTest &&
./utils/UnorderedArrayTest &&
./utils/typesTest &&
./utils/randomTest &&
./image/ImageContainerTest &&
./image/MixedImageTest &&
./core/FilterTest &&

echo '\n\n--end of the test suite--\n\n'
