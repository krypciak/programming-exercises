#!/bin/sh
ls -1 a.cpp kaslib.h | entr sh -c 'clear; echo compiling...; g++ -Wall -O3 -static -std=c++20 -g a.cpp -o a.e; echo done'
