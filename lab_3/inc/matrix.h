#ifndef _MATRIX_H_
#define _MATRIX_H_

// структура для определения обычной матрицы
struct matrix
{
    int rows; // число строк матрицы
    int columns; // число столбцов матрицы
    int not_zero; // число ненулевых элементов
    int **matrix; // сама матрица
};
typedef struct matrix matrix_s;

// структура для определения разреженной матрицы
struct sparse_matrix
{
    int rows; // число строк матрицы
    int columns; // число столбцов матрицы
    int not_zero; // число ненулевых элементов
    int *a; // массив ненулевых элементов матрицы
    int *ja; // массив индексов столбцов ненулевых элементов
    int *ia; // массив индексов в a и ja, с которых начинается i-ая строка
};
typedef struct sparse_matrix sparse_matrix_s;

#endif
