#!/bin/bash
set -e

export MEM_LIMIT=256M
TIME_LIMIT=6000
max_time=0
max_time_test=""
exe_file="$(mktemp --suffix .e)"
g++ a.cpp -o "$exe_file" -std=c++23 -O2
for f in $(find . -type f -name "*.in"); do
    echo -n $f
    time="$(oiejq "$exe_file" < "$f"  2>&1 1>/dev/null | grep "Time" | awk '{print $2}' | head --bytes -3)"
    echo " " $time
    if [ "$time" -gt "$max_time" ]; then
        max_time="$time"
        max_time_test="$f"
    fi
    if [ "$time" -ge "$TIME_LIMIT" ]; then
        echo "time exceeded!" $f $time
        exit 1
    fi
done
echo "all passed, max time: $max_time on $max_time_test"
rm -f "$exe_file"

