ls -1 a.cpp | entr sh -c "clear; echo compiling... && g++ a.cpp -o a.e -Wall -g -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow && echo '----------------' && ./a.e"
