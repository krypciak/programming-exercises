ls -1 a.cpp | entr sh -c 'clear; echo compiling... && g++ a.cpp -o a -Wall -O3 && echo ---------------'
