#!/bin/sh
set -e
g++ -Wall -DTEST -g a.cpp -o a
gdb --interpreter=dap --nh --quiet --ex "set print pretty on" ./a
