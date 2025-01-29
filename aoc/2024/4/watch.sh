ls -1 a.cpp | entr sh -c 'clear; g++ -fsanitize=leak,undefined,float-divide-by-zero,float-cast-overflow -Wall -Og -g a.cpp -o a.e && echo "-----" && ./a.e'
