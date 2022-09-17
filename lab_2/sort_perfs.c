#include "perf.h"
#include "perfs.h"

// функция, меняющая местами два записи о спектаклеях
void swap_perfs(performance_s *first, performance_s *second)
{
    performance_s temp = *first;
    *first = *second;
    *second = temp;
}

// функция для быстрой сортировки массива спектаклей по минимальной цене билета
void qsort_perfs(performance_s *const arr, int b, int e)
{
    int l = b, r = e;
    short mid = arr[(l + r) / 2].price_range[0]; 

    while (l <= r)
    {
        while (arr[l].price_range[0] < mid)
            l++;

        while (arr[r].price_range[0] > mid)
            r--;

        if (l <= r)
            swap_perfs(&(arr[l++]), &(arr[r--]));
    }
    if (b < r)
        qsort_perfs(arr, b, r);

    if (e > l)
        qsort_perfs(arr, l, e);
} 

// функция для обычной сортировки массива спектаклей по минимальной цене билета
void bubble_sort_perfs(performance_s *const arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
            if (arr[j].price_range[0] > arr[j + 1].price_range[0])
                swap_perfs(&(arr[j]), &(arr[j + 1]));
    }
}

// функция для замера времени работы обычной сортировки спектаклей
float bubble_perfs_time(FILE *file, performance_s *const arr, int size)
{
    clock_t start, end; // время до и после сортировки
    int perf_bubble = 0;

    for (int i = 0; i < 1500; i++)
    {
        read_perfs(file, arr, &size); // читаем исходную таблицу
        // замеряем время обычной сортировки спектаклей
        start = clock();
        bubble_sort_perfs(arr, size);
        end = clock();
        perf_bubble += (end - start);
        rewind(file);
    }

    return (float)perf_bubble / 1500;
}

// функция для замера времени работы быстрой сортировки спектаклей
float qsort_perfs_time(FILE *file, performance_s *const arr, int size)
{
    clock_t start, end; // время до и после сортировки
    int perf_qsort = 0;

    for (int i = 0; i < 1500; i++)
    {
        read_perfs(file, arr, &size); // читаем исходную таблицу
        // замеряем время быстрой сортировки спектаклей
        start = clock();
        qsort_perfs(arr, 0, size - 1);
        end = clock();
        perf_qsort += (end - start);
        rewind(file);
    }

    return (float)perf_qsort / 1500;
}
