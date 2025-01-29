#/bin/bash
comp() {
	clear
	echo "compiling..."
	g++ -Wall a.cpp -o a.e -std=c++23 -g -DTEST -fsanitize=address,undefined,leak,float-divide-by-zero,float-cast-overflow && echo "------" && ./a.e
}
export -f comp
ls -1 a.cpp ex* | entr sh -c comp


