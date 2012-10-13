#!/bin/sh
echo "-- initialize"
mkdir ../objdir-kiwi && cd ../objdir-kiwi && cmake ../kiwi/ && cd ../kiwi/ && echo "-- done" || echo "-- failed"
