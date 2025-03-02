#/bin/bash
comp() {
    clear
    echo compiling...
    python3 a.py <ex0.in && echo .
    echo "--------"
    echo "expected:"
    cat ex0.out
}
export -f comp
ls a.py | entr sh -c comp
