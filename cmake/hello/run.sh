#!/bin/bash

cd bin
touch ../src/CMakeLists.txt 
cmake ../src
make
./hello
cd ..
