@echo off

REM Define an array of arguments
set args=10 100 500 1000

REM Loop through the arguments and run the program with each one
for %%a in (%args%) do (
    matMulFloat.exe %%a 10 >> results/float/results-float-n-%%a.txt
    matMulInt.exe %%a 10 >> results/int/results-int-n-%%a.txt
)
