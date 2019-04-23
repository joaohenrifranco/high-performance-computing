#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS_COUNT 10
#define ROWS_COUNT 10

int main() {
  static int matrix[ROWS_COUNT][COLS_COUNT];
  static int vector[COLS_COUNT];
  static int result[ROWS_COUNT];
  int i, j;

  struct timespec start_time, finish_time;
  double elapsed_time;

  srand(time(NULL));

  printf("Initializing...\n");

  for (i = 0; i < ROWS_COUNT; i++) {
    for (j = 0; j < COLS_COUNT; j++) {
      matrix[i][j] = rand();
    }
  }

  for (i = 0; i < ROWS_COUNT; i++) {
    result[i] = 0;
  }

  for (i = 0; i < COLS_COUNT; i++) {
    vector[i] = rand();
  }

  printf("Loop: row-col\nComputing...\n");

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  for (i = 0; i < ROWS_COUNT; i++) {
    for (j = 0; j < COLS_COUNT; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &finish_time);

  printf("Finished!\n");

  elapsed_time = (finish_time.tv_sec - start_time.tv_sec);
  elapsed_time += (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

  printf("Total time row-col: %lfs\n", elapsed_time);

  for (i = 0; i < ROWS_COUNT; i++) {
    result[i] = 0;
  }

  printf("Loop: col-row\nComputing...\n");

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  for (i = 0; i < COLS_COUNT; i++) {
    for (j = 0; j < ROWS_COUNT; j++) {
      result[j] += matrix[j][i] * vector[i];
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &finish_time);

  printf("Finished!\n");

  elapsed_time = (finish_time.tv_sec - start_time.tv_sec);
  elapsed_time += (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

  printf("Total time col-row: %lfs\n", elapsed_time);
}
