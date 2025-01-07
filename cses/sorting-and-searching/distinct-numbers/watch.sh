#/bin/bash
comp() {
	clear
	echo compiling...
	g++ a.cpp -o a -Wall -DTEST -std=c++23 -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo ------ && ./a
}
export -f comp
ls -1 a.cpp | entr sh -c comp

