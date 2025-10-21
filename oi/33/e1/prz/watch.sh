#!/bin/bash
comp() {
	clear
	echo compiling...
	# -g -Wextra -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow
	g++ a.cpp -o a.e -std=c++23 -DTEST -O2 -Wall && echo ------ && ./a.e && echo .
}
export -f comp
ls a.cpp | entr sh -c comp
