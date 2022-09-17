#include "key.h"

// функция для печати записи из массива ключей в общую таблицу
void print_key(perf_min_price_s key)
{
    printf("|%-15d ", key.index);
    printf("|%-6d\n", key.min_price);
}

// функция для печати записей из массива ключей в консоль в виде таблицы
void print_keys_table(perf_min_price_s *const arr, int size)
{
    // вывод заголовков таблицы
    printf("|%-15s ", "perf. table ind");
    printf("|%-10s\n", "min. price");
    printf("--------------------------\n");

    for (int i = 0; i < size; i++)
        print_key(arr[i]);
}
