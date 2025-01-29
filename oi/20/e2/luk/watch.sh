#/bin/bash
comp() {
	clear
	echo "compiling..."
	g++ a.cpp -o a.e -Wall -Wextra -std=c++23 -g -DTEST -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo ------- && ./a.e && echo .
}
export -f comp
ls a.cpp | entr sh -c comp
