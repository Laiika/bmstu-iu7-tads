#include "perf.h"
#include "perfs.h"

// функция для считывания спектаклей из файла в массив
int read_perfs(FILE *file, performance_s *const arr, int *const size)
{
    *size = 0;
    performance_s cur;
    int rc;

    while ((*size) < ARRAY_SIZE && OK == (rc = read_perf_file(file, &cur)))
    {
        arr[*size] = cur;
        (*size)++;
    }

    if (EOF == rc)
    {
        arr[*size] = cur;
        (*size)++;
        rc = OK;
    }

    return rc;
}
