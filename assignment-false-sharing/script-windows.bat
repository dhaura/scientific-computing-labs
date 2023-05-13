@echo off

REM Define an array of arguments
set args=1 2 4 8 16 32 64 128
set iterations=1000000000

REM Run sequential progrram
gregoryLeibnizV1.exe %iterations% >> results/results-v1.txt

REM Loop through the arguments and run the program with each one
for %%a in (%args%) do (
    gregoryLeibnizV2.exe %iterations% %%a >> results/results-v2.txt
    gregoryLeibnizV3.exe %iterations% %%a >> results/results-v3.txt
)
