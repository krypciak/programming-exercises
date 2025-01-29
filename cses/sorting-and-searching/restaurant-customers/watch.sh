#!/bin/bash
comp() {
	clear
	echo compiling...
	g++ a.cpp -o a.e -Wall -Wextra -g -std=c++23 -DTEST -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo ------- && ./a.e && echo .
}
export -f comp
ls -1 a.cpp | entr sh -c comp
