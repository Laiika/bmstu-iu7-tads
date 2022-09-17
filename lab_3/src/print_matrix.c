#include "../inc/print_matrix.h"

// функция для печати обычной матрицы
void print_matrix(matrix_s mtr)
{
    if ((mtr.rows >= 15 && mtr.columns >= 15) || (mtr.rows > 30) || (mtr.columns > 30))
        printf("Матрица слишком крупная\n");
    else
    {
        for (int i = 0; i < mtr.rows; i++)
        {
            for (int j = 0; j < mtr.columns; j++)
                printf("%6d ", (mtr.matrix)[i][j]);

            printf("\n");
        }
    }
}

// функция для печати разреженной матрицы
void print_sp_matrix(sparse_matrix_s mtr)
{
    for (int i = 0; i < mtr.not_zero; i++)
        printf("%6d ", (mtr.a)[i]);

    printf("\n");

    for (int i = 0; i < mtr.not_zero; i++)
        printf("%6d ", (mtr.ja)[i]);

    printf("\n");

    for (int i = 0; i <= mtr.rows; i++)
        printf("%6d ", (mtr.ia)[i]);

    printf("\n");
}
