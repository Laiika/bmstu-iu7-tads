#include "key.h"

// функция, меняющая местами две записи в массиве ключей
void swap_elems(perf_min_price_s *first, perf_min_price_s *second)
{
    perf_min_price_s temp = *first;
    *first = *second;
    *second = temp;
}

// функция для быстрой сортировки массива ключей по минимальной цене билета
void qsort_keys(perf_min_price_s *const arr, int b, int e)
{
    int l = b, r = e;
    short mid = arr[(l + r) / 2].min_price; 

    while (l <= r)
    {
        while (arr[l].min_price < mid)
            l++;

        while (arr[r].min_price > mid)
            r--;

        if (l <= r)
            swap_elems(&(arr[l++]), &(arr[r--]));
    }
    if (b < r)
        qsort_keys(arr, b, r);

    if (e > l)
        qsort_keys(arr, l, e);
} 

// функция для обычной сортировки массива ключей по минимальной цене билета
void bubble_sort_keys(perf_min_price_s *const arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
            if (arr[j].min_price > arr[j + 1].min_price)
                swap_elems(&(arr[j]), &(arr[j + 1]));
    }
}

// функция для замера времени работы обычной сортировки ключей
float bubble_keys_time(performance_s *const arr, perf_min_price_s *keys, int size)
{
    clock_t start, end; // время до и после сортировки
    int keys_bubble = 0;

    for (int i = 0; i < 1500; i++)
    {
        // замеряем время обычной сортировки 
        start = clock();
        bubble_sort_keys(keys, size);
        end = clock();
        keys_bubble += (end - start);
        get_keys_array(arr, keys, size); // получаем таблицу ключей на основе исходной
    }

    return (float)keys_bubble / 1500;
}

// функция для замера времени работы быстрой сортировки ключей
float qsort_keys_time(performance_s *const arr, perf_min_price_s *keys, int size)
{
    clock_t start, end; // время до и после сортировки
    int keys_qsort = 0;

    for (int i = 0; i < 1500; i++)
    {
        // замеряем время обычной сортировки 
        start = clock();
        qsort_keys(keys, 0, size - 1);
        end = clock();
        keys_qsort += (end - start);
        get_keys_array(arr, keys, size); // получаем таблицу ключей на основе исходной
    }

    return (float)keys_qsort / 1500;
}
