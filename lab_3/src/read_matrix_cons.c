#include "../inc/read_matrix_cons.h"

// функция для чтения обычной матрицы с клавиатуры
int read_matrix_console(matrix_s *mtr, int rows, int cols, int not_zero)
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
        printf("Введите индекс строки, столбца и значение элемента матрицы: ");

        if (3 != scanf("%d %d %d", &i, &j, &elem) || i < 0 || j < 0 || i >= rows || j >= cols || elem == 0)
        {
            free_matrix(mtr->matrix, mtr->rows);
            return INPUT_ERROR;
        }

        (mtr->matrix)[i][j] = elem;
    }

    return OK;
}

// функция для чтения обычного вектор-столбца с клавиатуры
int read_vector_console(matrix_s *vector, int rows, int not_zero)
{
    vector->rows = rows;
    vector->columns = 1;
    vector->not_zero = not_zero;

    // выделение памяти под вектор
    vector->matrix = allocate_matrix(vector->rows, vector->columns);

    if (NULL == vector->matrix)
        return MEMORY_ERROR;

    // ввод индексов строк и значений элементов
    for (int k = 0; k < vector->not_zero; k++)
    {
        int i, elem;
        printf("Введите индекс строки и значение элемента вектора-столбца: ");

        if (2 != scanf("%d %d", &i, &elem) || i < 0 || i >= rows || elem == 0)
        {
            free_matrix(vector->matrix, vector->rows);
            return INPUT_ERROR;
        }

        (vector->matrix)[i][0] = elem;
    }

    return OK;
}

// функция для чтения матрицы и вектора с клавиатуры
int read_from_cons(matrix_s *mtr, matrix_s *vector, int rows, int cols, int nz_m, int nz_v)
{
    int rc;

    // чтение матрицы
    if (OK != (rc = read_matrix_console(mtr, rows, cols, nz_m)))
        return rc;
    // чтение вектор-столбца
    if (OK != (rc = read_vector_console(vector, mtr->columns, nz_v)))
        free_matrix(mtr->matrix, mtr->rows);

    return rc;
}
