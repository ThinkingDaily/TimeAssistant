#!/bin/bash

g++ -o test.o -c test.cpp
g++ -o test_api.o -c test_api.c

# Both is ok
#ar r libtest.so test_api.o test.o 
ar r libtest.a test_api.o test.o 

go run main.go
