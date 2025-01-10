#!/bin/bash
comp() {
	clear
	echo compiling...
	g++ a.cpp -o a -Wall -Wextra -g -std=c++23 -DTEST -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo ------- && ./a && echo .
}
export -f comp
ls -1 a.cpp | entr sh -c comp
