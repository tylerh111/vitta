#!/bin/bash
# Usage: ./run_test.sh <cpp_file> <variadic_args> <vitta_args>
#   cpp_file: the C++ file to be compiled by gcc
#       - note, it will not write anything to disk
#       - must be an absolute path or relative path from the tests directory
#   variadic_args: the types for the variadic type
#       - comma separated list of types
#   vitta_args: the types for vitta variadic aggregation
#       - comma separated list of types
#
# Example uses:
#   $ ./run_test.sh test_variant_aggregate.cpp "int" "std::variant<int>"
#   $ ./run_test.sh test_variant_aggregate.cpp "int,double,char" "std::variant<int,double>,char"
#
# This tests whether the aggregation class is correctly aggregating
#   a list of types. This tries to compile the cpp_file provided.
#   If there is no compiler errors, then the following types are the
#   same.
#       - std::tuple < VARIADIC_ARGS >
#       - vitta::tuple_aggregate_t < VITTA_ARGS >
#       OR
#       - std::variant < VARIADIC_ARGS >
#       - vitta::variant_aggregate_t < VITTA_ARGS >
#
# Hint, use quotes to specify your arguments. These will be removed before
#   passing arguments to compiler.
cd $(dirname $0)

if [ $# -ne 3 ]; then
    echo "Usage: ./run_test.sh <cpp_file> <variadic_args> <vitta_args>"
    echo "  cpp_file: the C++ file to be compiled by gcc"
    echo "      - note, it will not write anything to disk"
    echo "  variadic_args: the types for the variadic type"
    echo "      - comma separated list of types"
    echo "  vitta_args: the types for vitta variadic aggregation"
    echo "      - comma separated list of types"
    exit
fi

IN_FILE=$1
IN_VARIADIC_ARGS=$(echo $2 | tr -d '"')
IN_VITTA_ARGS=$(echo $3 | tr -d '"')

g++ -c -fsyntax-only -I../include \
    $IN_FILE \
    -DVARIADIC_ARGS=$IN_VARIADIC_ARGS \
    -DVITTA_ARGS=$IN_VITTA_ARGS

