#!/bin/bash
# Usage: ./run_test.sh <cpp_file> <variadic_args> <vitta_args>
#   cpp_file: the C++ file to be compiled by gcc
#       - note, it will not write anything to disk
#
# Example uses:
#   $ ./run_test.sh tests/test_aggregate.cpp
set -eoux pipefail

if [ $# -ne 1 ]; then
    echo "Usage: ./run_test.sh <cpp_file>"
    echo "  cpp_file: the C++ file to be compiled by gcc"
    echo "      - note, it will not write anything to disk"
    exit
fi

FILE=$1

g++               \
    -c            \
    -fsyntax-only \
    -std=c++11    \
    -Iinclude     \
    $FILE         \
    `# done`

