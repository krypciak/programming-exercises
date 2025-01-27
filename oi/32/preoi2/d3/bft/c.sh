#!/bin/bash
comp() {
	clear
	echo compiling...
	g++ a.cpp -o a -DTEST -Wall -Wextra -std=c++23 -g -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo ------ && ./a && echo .
}
export -f comp
comp 
