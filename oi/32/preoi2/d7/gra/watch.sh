#!/bin/bash
set -e
clear
echo compiling...
g++ a.cpp -o a.e -std=c++23 -Wall -Wextra -g -fsanitize=address,leak,undefined,float-cast-overflow,float-divide-by-zero -DTEST
echo ----
./a.e
echo .

