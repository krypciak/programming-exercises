#!/bin/bash
set -e
clear
echo compiling...
g++ a.cpp -o a.e -std=c++20 -g -DTEST -Wall -Wextra -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow
echo ------
./a.e
echo .
