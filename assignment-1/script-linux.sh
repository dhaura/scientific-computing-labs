#!/bin/bash

# Define an array of arguments
args=(10 100 500 1000)

# Loop through the arguments and run the program with each one
for arg in "${args[@]}"
do
    echo "FLOAT n = $arg"
    MEM=`free | awk 'NR==2{print $7}'`
    echo "Available main memory: $MEM bytes"
    ./matMulFloat "$arg" "20" >> results/float/results-float-n-"$arg".txt
    
    echo "INT n = $arg"
    MEM=`free | awk 'NR==2{print $7}'`
    echo "Available main memory: $MEM bytes"
    ./matMulInt "$arg" "20" >> results/int/results-int-n-"$arg".txt
done