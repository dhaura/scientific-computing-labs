#!/bin/bash

# Define an array of arguments
args=(1 2 4 8 16 32 64 128)
iterations=1000000000

# Run sequential progrram
./gregoryLeibnizV1 "$iterations" >> results/results-v1.txt

# Loop through the arguments and run the program with each one
for arg in "${args[@]}"
do
    ./gregoryLeibnizV2 "$iterations" "$arg" >> results/results-v2.txt
    ./gregoryLeibnizV3 "$iterations" "$arg" >> results/results-v3.txt
done