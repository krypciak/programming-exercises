#!/bin/bash
comp() {
    clear
    echo "compiling..."
    g++ a.cpp -o a -Wall -DTEST -g -fsanitize=address,undefined,leak,float-divide-by-zero,float-cast-overflow && echo "------" && ./a
}

export -f comp

ls -1 a.cpp | entr sh -c comp
