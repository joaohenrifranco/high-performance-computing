#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#ifndef AUTOMATED_TEST
#define COLS_COUNT 25000
#define ROWS_COUNT 25000
#endif

int main() {
  static int matrix[ROWS_COUNT][COLS_COUNT];
  static int vector[COLS_COUNT];
  static int result_s[ROWS_COUNT];
  static int result_p[ROWS_COUNT];

  int i, j;

  struct timespec start_time, finish_time;
  double elapsed_time_s, elapsed_time_p;

  srand(time(NULL));

  #ifndef AUTOMATED_TEST
  printf("Initializing...\n");
  #endif

  #pragma omp parallel for private(i, j)
  for (i = 0; i < ROWS_COUNT; i++) {
    for (j = 0; j < COLS_COUNT; j++) {
      matrix[i][j] = rand();
    }
  }

  for (i = 0; i < ROWS_COUNT; i++) {
    result_p[i] = 0;
  }

  for (i = 0; i < ROWS_COUNT; i++) {
    result_s[i] = 0;
  }

  for (i = 0; i < COLS_COUNT; i++) {
    vector[i] = rand();
  }

  #ifndef AUTOMATED_TEST
  printf("Finished!\n");
  printf("Computing parallelly...\n");
  #endif

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  #pragma omp parallel for private(i, j) reduction(+:result_p[:ROWS_COUNT])
  for (i = 0; i < ROWS_COUNT; i++) {
    for (j = 0; j < COLS_COUNT; j++) {
      result_p[i] += matrix[i][j] * vector[j];
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &finish_time);

  elapsed_time_p = (finish_time.tv_sec - start_time.tv_sec);
  elapsed_time_p += (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

  #ifndef AUTOMATED_TEST
  printf("Finished!\nTotal time paralel: %lfs\n", elapsed_time_p);
  printf("Computing serially...\n");
  #endif

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  for (i = 0; i < COLS_COUNT; i++) {
    for (j = 0; j < ROWS_COUNT; j++) {
      result_s[j] += matrix[j][i] * vector[i];
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &finish_time);

  elapsed_time_s = (finish_time.tv_sec - start_time.tv_sec);
  elapsed_time_s += (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

  #ifndef AUTOMATED_TEST
  printf("Finished!\nTotal time serial: %lfs\n", elapsed_time_s);
  printf("Checking correctness...\n");
  #endif

  for (i = 0; i < ROWS_COUNT; i++) {
    if (result_s[i] != result_p[i]) {
      printf("Bad result!");
      return 0;
    }
  }

  #ifndef AUTOMATED_TEST
  printf("Correct results!\n");
  #endif

  #ifdef AUTOMATED_TEST
  printf("%d,%lf,%lf\n", ROWS_COUNT, elapsed_time_p, elapsed_time_s);
  #endif

  return 0;
}
