#ifndef _PERFS_H_
#define _PERFS_H_

#include <stdio.h>
#include <time.h>
#include "key.h"
#include "errors.h"

// максимальный размер массива
#define ARRAY_SIZE 50

int read_perfs(FILE *file, performance_s *const arr, int *const size);
int add_perf(char *file_name, performance_s *const arr, int *const size);
int delete_perf(char *file_name, performance_s *const arr, int *const size);
int search(performance_s *arr, const int size);
void qsort_perfs(performance_s *const arr, int b, int e);
void bubble_sort_perfs(performance_s *const arr, int size);
float bubble_perfs_time(FILE *file, performance_s *const arr, int size);
float qsort_perfs_time(FILE *file, performance_s *const arr, int size);
void print_perfs_table(performance_s *const arr, int size);
void print_perfs_table_keys(performance_s *const arr, perf_min_price_s *const keys, int size);

#endif
