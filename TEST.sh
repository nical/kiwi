#!/bin/sh

cd ./build/test

./core/FactoryTest  &&
./core/NodeTest &&
./generic/ArrayContainerTest && 
./generic/MultiArrayContainerTest && 
./generic/PointTest &&
./generic/ValueContainerTest &&
./image/CairoImageContainerTest &&
./text/TextContainerTest

echo '\n\n--end of the test suite (success)--\n\n'
