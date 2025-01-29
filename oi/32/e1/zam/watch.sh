#!/bin/sh
ls -1 a.cpp | entr sh -c 'clear; echo compiling...; g++ -Wall -g a.cpp -o a.e'
