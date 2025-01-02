#/bin/bash

comp() {
    clear
    echo "compiling..."
    g++ a.cpp -o a -Wall -DDEBUG -std=c++23 -g -fsanitize=address,undefined,leak,float-divide-by-zero,float-cast-overflow && echo "-----" && ./a
}

export -f comp

ls -1 a.cpp | entr sh -c comp
