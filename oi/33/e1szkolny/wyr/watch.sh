#!/bin/bash
comp() {
	clear
	echo compiling...
	g++ a.cpp -o a.e -std=c++23 -DTEST -g -Wextra -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow -Wall && echo ------ && ./a.e && echo .
}
export -f comp
ls a.cpp | entr sh -c comp
