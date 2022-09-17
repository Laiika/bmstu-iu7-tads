#ifndef _KEY_H_
#define _KEY_H_

#include <stdio.h>
#include <time.h>
#include "perf.h"
#include "errors.h"

// максимальный размер массива
#define ARRAY_SIZE 50

// структура для записи в таблице ключей (ключ - минимальная цена билета)
struct perf_min_price
{
    int index; // индекс записи в исходном массиве
    short min_price; // минимальная цена билета
};
typedef struct perf_min_price perf_min_price_s;

void get_keys_array(performance_s *arr, perf_min_price_s *keys, int size);
void qsort_keys(perf_min_price_s *const arr, int b, int e);
void bubble_sort_keys(perf_min_price_s *const arr, int size);
float bubble_keys_time(performance_s *const arr, perf_min_price_s *keys, int size);
float qsort_keys_time(performance_s *const arr, perf_min_price_s *keys, int size);
void print_keys_table(perf_min_price_s *const arr, int size);

#endif
