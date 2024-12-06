comp() {
    clear
    echo compiling... && g++ a.cpp -Wall -o a -g -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo ------- && ./a
}
export -f comp
ls -1 a.cpp | entr sh -c comp
