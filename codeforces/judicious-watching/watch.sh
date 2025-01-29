#!/bin/bash

comp() {
    clear
    echo "compiling..."
    g++ -std=c++23 -Wall a.cpp -o a.e -g -fsanitize=address,undefined,leak,float-divide-by-zero,float-cast-overflow -DDEBUG && echo "--------------" && ./a.e
}
export -f comp

ls -1 a.cpp | entr sh -c comp
