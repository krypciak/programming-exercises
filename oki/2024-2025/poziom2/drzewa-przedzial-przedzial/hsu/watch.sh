#!/bin/bash
comp() {
    clear
    echo compiling...
    g++ a.cpp -o a.e -std=c++23 -DTEST -g -Wall -Wextra -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo ------- && ./a.e && echo .
}
export -f comp
ls a.cpp | entr -r sh -c comp
