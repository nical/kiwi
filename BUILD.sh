#!/bin/sh
echo ""
echo "** build"
make -j4 -C ../objdir-kiwi  2>&1 | prettybuild 

./TEST.sh