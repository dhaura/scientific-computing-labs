#!/bin/bash

# Define an array of arguments
args=(10 100 500 1000 5000 10000)

# Loop through the arguments and run the program with each one
for arg in "${args[@]}"
do
    ./matMulFloat "$arg" "20" >> results/float/results-float-n-"$arg".txt
    ./matMulInt "$arg" "20" >> results/int/results-int-n-"$arg".txt
done
