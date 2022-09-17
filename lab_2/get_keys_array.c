#include "key.h"
#include "perf.h"

// функция для создания массива ключей по исходному массиву спектаклей
void get_keys_array(performance_s *arr, perf_min_price_s *keys, int size)
{
    // наполнение массива ключей
    for (int i = 0; i < size; i++)
    {
        perf_min_price_s key;

        key.index = i;
        key.min_price = arr[i].price_range[0];
        keys[i] = key;
    }
}
