#include "../inc/mult_matrices.h"

// функция для умножения матрицы и вектор-столбца в обычном формате
int mult_mtrs(matrix_s *res, matrix_s mtr1, matrix_s mtr2)
{
    res->rows = mtr1.rows;
    res->columns = mtr2.columns;
    res->not_zero = 0;
    // выделение памяти под результат
    res->matrix = allocate_matrix(res->rows, res->columns);

    if (NULL == res->matrix)
        return MEMORY_ERROR;

    for (int i = 0; i < res->rows; i++)
        for (int j = 0; j < res->columns; j++)
        {
            (res->matrix)[i][j] = 0;

            for (int k = 0; k < mtr1.columns; k++) // вычисление очередного элемента результата
                (res->matrix)[i][j] += ((mtr1.matrix)[i][k] * (mtr2.matrix)[k][j]);

            if (0 != (res->matrix)[i][j])
                (res->not_zero)++;
        }

    return OK;
}

// функция для умножения матрицы и вектор-столбца в разреженном формате
int mult_sp_mtrs(sparse_matrix_s *res, sparse_matrix_s mtr1, sparse_matrix_s mtr2)
{
    int not_zero = 0, ind = 0;
    int *temp = calloc(sizeof(int), mtr1.rows); // временная матрица для умножения

    if (NULL == temp)
        return MEMORY_ERROR;

    for (int i = 0; i < mtr1.rows; i++)
    {
        // проход по ненулевым элементам i-ой строки
        for (int j = (mtr1.ia)[i]; j < (mtr1.ia)[i + 1]; j++)
        {
            int col = (mtr1.ja)[j]; // получаем индекс столбца данного элемента в матрице
            int ind = (mtr2.ia)[col]; // смотрим строку с таким индексом в векторе-столбце

            // в данной строке вектор-столбца есть ненулевой элемент
            if (ind + 1 == (mtr2.ia)[col + 1])
                temp[i] += (mtr1.a)[j] * (mtr2.a)[ind];
        }

        if (0 != temp[i])
            not_zero++;
    }
    // все элементы в результате - 0
    if (0 == not_zero)
    {
        free(temp);
        return EMPTY_MATRIX;
    }
    // выделение памяти под результат
    if (OK != allocate_sparce_matrix(res, mtr1.rows, not_zero))
    {
        free(temp);
        return MEMORY_ERROR;
    }
    // заполняем матрицу результатом
    for (int i = 0; i < mtr1.rows; i++)
    {
        (res->ia)[i] = ind; // индекс начала строки в массивах a и ja

        if (0 != temp[i])
        {
            (res->a)[ind] = temp[i];
            (res->ja)[ind] = 0;
            ind++;
        }
    }

    (res->ia)[mtr1.rows] = ind;
    res->rows = mtr1.rows;
    res->columns = 1;
    res->not_zero = not_zero;

    free(temp);
    return OK;
}
