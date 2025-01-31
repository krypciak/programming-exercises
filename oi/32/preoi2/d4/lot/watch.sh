#!/bin/bash
comp() {
	clear
	echo compiling...
	g++ a.cpp -o a.e -std=c++23 -Wall -Wextra -g -DTEST -fsanitize=address,leak,undefined,float-cast-overflow,float-divide-by-zero && echo ------- && ./a.e && echo .
}
export -f comp
comp $1
