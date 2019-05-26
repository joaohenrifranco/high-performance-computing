#!/bin/sh
echo "Size,Paralel Time,Serial Time" > results.csv
for MATRIX_SIZE in 100 250 500 1000 2000 4000 8000 16000 32000
do
  gcc-9 -Wall -fopenmp matrix.c -D COLS_COUNT=$MATRIX_SIZE -D ROWS_COUNT=$MATRIX_SIZE -D AUTOMATED_TEST
  ./a.out >> results.csv
done
