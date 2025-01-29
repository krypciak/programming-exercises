#!/bin/sh
ls -1 a.cpp | entr sh -c 'clear; echo compiling...; g++ -Wall -fsanitize=leak,undefined,float-divide-by-zero,float-cast-overflow -g a.cpp -o a.e; echo -----------------; ./a.e'
