#include "../inc/read_matrix_file.h"

// функция для чтения обычной матрицы из файла
int read_matrix_file(FILE *file, matrix_s *mtr, int rows, int cols, int not_zero)
{
    mtr->rows = rows;
    mtr->columns = cols;
    mtr->not_zero = not_zero;

    // выделение памяти под матрицу
    mtr->matrix = allocate_matrix(mtr->rows, mtr->columns);

    if (NULL == mtr->matrix)
        return MEMORY_ERROR;

    // ввод индексов строк, столбцов и значений элементов
    for (int k = 0; k < mtr->not_zero; k++)
    {
        int i, j, elem;

        if (3 != fscanf(file, "%d %d %d", &i, &j, &elem) || i < 0 || j < 0 || i >= rows || j >= cols || elem == 0)
        {
            free_matrix(mtr->matrix, mtr->rows);
            return INPUT_ERROR;
        }

        (mtr->matrix)[i][j] = elem;
    }

    return OK;
}

// функция для чтения обычного вектор-столбца из файла
int read_vector_file(FILE *file, matrix_s *vector, int rows, int not_zero)
{
    vector->rows = rows;
    vector->columns = 1;
    vector->not_zero = not_zero;

    // выделение памяти под вектор
    vector->matrix = allocate_matrix(vector->rows, vector->columns);

    if (NULL == vector->matrix)
        return MEMORY_ERROR;

    // ввод строк и значений элементов
    for (int k = 0; k < vector->not_zero; k++)
    {
        int i, elem;

        if (2 != fscanf(file, "%d %d", &i, &elem) || i < 0 || i >= rows || elem == 0)
        {
            free_matrix(vector->matrix, vector->rows);
            return INPUT_ERROR;
        }

        (vector->matrix)[i][0] = elem;
    }

    return OK;
}

// функция для чтения матрицы и вектора из файла
int read_from_file(FILE *file, matrix_s *mtr, matrix_s *vector, int rows, int cols, int nz_m, int nz_v)
{
    int rc;

    // чтение матрицы
    if (OK != (rc = read_matrix_file(file, mtr, rows, cols, nz_m)))
        return rc;
    // чтение вектор-столбца
    if (OK != (rc = read_vector_file(file, vector, mtr->columns, nz_v)))
        free_matrix(mtr->matrix, mtr->rows);

    return rc;
}
