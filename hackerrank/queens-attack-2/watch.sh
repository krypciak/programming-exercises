#!/bin/bash

wat() {
    clear;
    echo "compiling..."
    g++ -std=c++23 -g a.cpp -o a.e -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo "-----------" && ./a.e < in0.txt
}

export -f wat

ls -1 a.cpp | entr sh -c wat
