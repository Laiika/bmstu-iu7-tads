#include "../inc/convert_matrix.h"

// функция для формирования разреженной матрицы по обычной
int convert_matrix(sparse_matrix_s *sp_mtr, matrix_s mtr)
{
    // выделение памяти под разреженную матрицу
    if (OK != allocate_sparce_matrix(sp_mtr, mtr.rows, mtr.not_zero))
        return MEMORY_ERROR;

    int ind = 0;

    for (int i = 0; i < mtr.rows; i++)
    {
        (sp_mtr->ia)[i] = ind; // индекс начала строки в массивах a и ja

        for (int j = 0; j < mtr.columns; j++)
        {
            if (0 != (mtr.matrix)[i][j]) // встретился ненулевой элемент
            {
                (sp_mtr->a)[ind] = (mtr.matrix)[i][j];
                (sp_mtr->ja)[ind] = j;
                ind++;
            }
        }
    }

    (sp_mtr->ia)[mtr.rows] = ind;
    sp_mtr->rows = mtr.rows;
    sp_mtr->columns = mtr.columns;
    sp_mtr->not_zero = mtr.not_zero;

    return OK;
}
