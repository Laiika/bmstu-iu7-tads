#include "../inc/mem_matrix.h"

// функция для выделения памяти под матрицу
int **allocate_matrix(int n, int m)
{
    int **ptrs, *data;

    // выделение памяти под массив указателей на строки матрицы
    ptrs = malloc((n + 1) * sizeof(int*));

    if (!ptrs)
        return NULL;

    // выделение памяти под саму матрицу
    data = calloc(sizeof(int), n * m);

    if (!data)
    {
        free(ptrs);
        return NULL;
    }

    for (int i = 0; i < n; i++)
        ptrs[i] = data + i * m;

    ptrs[n] = data;
    return ptrs;
}

// функция для выделения памяти под разреженную матрицу
int allocate_sparce_matrix(sparse_matrix_s *sp_mtr, int rows, int not_zero)
{
    // выделение памяти под массив значений ненулевых элементов
    sp_mtr->a = calloc(sizeof(int), not_zero);

    if (!(sp_mtr->a))
        return MEMORY_ERROR;

    // выделение памяти под массив индексов столбцов ненулевых элементов
    sp_mtr->ja = calloc(sizeof(int), not_zero);

    if (!(sp_mtr->ja))
    {
        free(sp_mtr->a);
        return MEMORY_ERROR;
    }

    // выделение памяти под массив индексов в a и ja, с которых начинается i-ая строка
    sp_mtr->ia = calloc(sizeof(int), rows + 1);

    if (!(sp_mtr->ia))
    {
        free(sp_mtr->a);
        free(sp_mtr->ja);
        return MEMORY_ERROR;
    }
    
    return OK;
}

// функция для освобождения памяти из под матрицы
void free_matrix(int **ptrs, int n)
{
    free(ptrs[n]);

    free(ptrs);
}

// функция для освобождения памяти из под разреженной матрицы
void free_sparce_matrix(sparse_matrix_s *mtr)
{
    free(mtr->a);
    free(mtr->ja);
    free(mtr->ia);
}
