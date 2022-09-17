#include "../inc/create_rand_matrix.h"

// функция для создания матрицы со случайными числами
int create_rand_matrix(matrix_s *mtr, int rows, int cols, int not_zero)
{
    mtr->rows = rows;
    mtr->columns = cols;
    mtr->not_zero = not_zero;

    // выделение памяти под матрицу
    mtr->matrix = allocate_matrix(mtr->rows, mtr->columns);

    if (NULL == mtr->matrix)
        return MEMORY_ERROR;

    // заполнение матрицы заданным количеством ненулевых элементов подряд
    for (int k = 0; k < mtr->not_zero; k++)
    {
        int elem = 1 + rand() % 100;

        (mtr->matrix)[k / (mtr->columns)][k % (mtr->columns)] = elem;
    }

    // разброс ненулевых элементов по матрице
    for (int k = 0; k < mtr->not_zero; k = k + 2)
    {
        int i = k / (mtr->columns), j = k % (mtr->columns), temp;

        temp = (mtr->matrix)[(mtr->rows) - i - 1][(mtr->columns) - j - 1];
        (mtr->matrix)[(mtr->rows) - i - 1][(mtr->columns) - j - 1] = (mtr->matrix)[i][j];
        (mtr->matrix)[i][j] = temp;
    }

    return OK;
}

// функция для создания вектора со случайными числами
int create_rand_vector(matrix_s *vector, int rows, int not_zero)
{
    vector->rows = rows;
    vector->columns = 1;
    vector->not_zero = not_zero;

    // выделение памяти под вектор
    vector->matrix = allocate_matrix(rows, vector->columns);

    if (NULL == vector->matrix)
        return MEMORY_ERROR;

    // заполнение вектора заданным количеством ненулевых элементов подряд
    for (int k = 0; k < vector->not_zero; k++)
    {
        int elem = 1 + rand() % 100;

        (vector->matrix)[k / (vector->columns)][0] = elem;
    }

    // разброс ненулевых элементов по вектору
    for (int k = 0; k < vector->not_zero; k = k + 2)
    {
        int i = k / (vector->columns), temp;

        temp = (vector->matrix)[(vector->rows) - i - 1][0];
        (vector->matrix)[(vector->rows) - i - 1][0] = (vector->matrix)[i][0];
        (vector->matrix)[i][0] = temp;
    }

    return OK;
}

// функция для создания матрицы и вектора со случайными числами
int create_with_random(matrix_s *mtr, matrix_s *vector, int rows, int cols, int nz_m, int nz_v)
{
    int rc;

    // чтение матрицы
    if (OK != (rc = create_rand_matrix(mtr, rows, cols, nz_m)))
        return rc;
    // чтение вектор-столбца
    if (OK != (rc = create_rand_vector(vector, mtr->columns, nz_v)))
        free_matrix(mtr->matrix, mtr->rows);

    return rc;
}
