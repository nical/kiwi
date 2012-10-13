#!/bin/sh
echo ""
echo "** build"
cd ./build && make 2>&1 | prettybuild 
cd .. 
./TEST.sh