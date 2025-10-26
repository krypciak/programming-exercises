#!/bin/bash
set -e

export MEM_LIMIT=256M
TIME_LIMIT=1000
max_time=0
max_time_test=""
g++ a.cpp -o b.e -std=c++23 -O2
for f in **.in; do
    time="$(oiejq ./b.e < "$f"  2>&1 1>/dev/null | grep "Time" | awk '{print $2}' | head --bytes -3)"
    echo $f $time
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
rm -f ./b.e

