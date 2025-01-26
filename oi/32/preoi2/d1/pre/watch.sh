#!/bin/bash
function comp() {
	clear
	echo compiling...
	g++ a.cpp -o a -Wall -Wextra -std=c++23 -DTEST -g -fsanitize=address,leak,undefined,float-cast-overflow,float-divide-by-zero && echo ------ && ./a && echo .
}
export -f comp
ls a.cpp | entr bash -c comp
