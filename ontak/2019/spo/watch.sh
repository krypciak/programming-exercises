#!/bin/bash

comp() {
	clear
	echo "compiling..."
	g++ a.cpp -o a.e -Wall -DTEST -g -std=c++23 -fsanitize=address,undefined,leak,float-divide-by-zero,float-cast-overflow && echo "------" && ./a.e
}
export -f comp
ls -1 a.cpp | entr sh -c comp
