#!/bin/bash
set -e
clear
echo compiling...
g++ a.cpp -o a.e -Wall -Wextra -std=c++23 -DTEST -g -fsanitize=address,leak,float-cast-overflow,float-divide-by-zero
echo ------
./a.e
echo .
