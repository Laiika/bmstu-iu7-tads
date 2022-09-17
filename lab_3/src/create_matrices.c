#include "../inc/create_matrices.h"

#define MAX_FILE_NAME 20

// функция для чтения имени файла
int read_file_name(char *const str, const int max_size, const int size)
{
    if (!fgets(str, size, stdin)) 
        return INPUT_ERROR;
        
    char ch = '\0';
    int len = strlen(str);
    // длина названия максимальна и дальше не символ переноса
    if (max_size == len && (1 != scanf("%c", &ch) || '\n' != ch))
    {
        while ('\n' != ch)
            scanf("%c", &ch);

        return INPUT_ERROR;
    }

    if ('\n' == str[len - 1])
        str[len - 1] = '\0';

    return OK;
}

// функция для чтения размеров матрицы и количества ненулевых элементов матрицы и вектора
int read_sizes(FILE *file, int *rows, int *cols, int *nz_m, int *nz_v)
{
    // ввод размеров матрицы, количества ненулевых элементов в матрице и векторе
    if (4 != fscanf(file, "%d %d %d %d", rows, cols, nz_m, nz_v))
        return INPUT_ERROR;

    if (*rows <= 0 || *cols <= 0 || *nz_m <= 0 || (*nz_m) > (*rows) * (*cols) || *nz_v <= 0 || *nz_v > *cols)
        return INPUT_ERROR;

    return OK;
}

// функция для заполнения матрицы и вектора выбранным способом
int create_matrices(int type, matrix_s *mtr, matrix_s *vector, sparse_matrix_s *sp_mtr, sparse_matrix_s *sp_vector, int *fr)
{
    matrix_s temp_m, temp_v; // временные обычные матрица и вектор
    sparse_matrix_s temp_sp_m, temp_sp_v; // временные разреженные матрица и вектор
    FILE *file;
    char str[MAX_FILE_NAME + 1], ch;
    int rc = OK, rows, cols, nz_m, nz_v;

    if (1 == type) // чтение матрицы и вектора с клавиатуры
    {
        printf("Введите размеры матрицы, количество ненулевых элементов в матрице и векторе-столбце: ");
        // чтение размеров матрицы и количества ненулевых элементов матрицы и вектора
        if (OK != (rc = read_sizes(stdin, &rows, &cols, &nz_m, &nz_v)))
            return rc;
        // чтение матрицы и вектора
        if (OK != (rc = read_from_cons(&temp_m, &temp_v, rows, cols, nz_m, nz_v)))
            return rc;
    }
    else if (2 == type) // чтение матрицы и вектора из файла
    {
        printf("Введите название файла (не более 20 символов): ");
        scanf("%c", &ch);
        // чтение имени файла
        if (OK != (rc = read_file_name(str, MAX_FILE_NAME, sizeof(str))))
            return rc;
        // открытие файла на чтение
        if (NULL == (file = fopen(str, "r")))
            return FILE_ERROR;
        // чтение размеров матрицы и количества ненулевых элементов матрицы и вектора
        if (OK == (rc = read_sizes(file, &rows, &cols, &nz_m, &nz_v)))  
            // чтение матрицы и вектора из файла
            rc = read_from_file(file, &temp_m, &temp_v, rows, cols, nz_m, nz_v);

        fclose(file);
        
        if (OK != rc)
            return rc;
    }
    else // заполнение случайными числами по заданным размерам
    { 
        printf("Введите размеры матрицы, количество ненулевых элементов в матрице и векторе-столбце: ");
        // чтение размеров матрицы и количества ненулевых элементов матрицы и вектора
        if (OK != (rc = read_sizes(stdin, &rows, &cols, &nz_m, &nz_v)))
            return rc;
        // заполнение матрицы и вектора случайными числами
        if (OK != (rc = create_with_random(&temp_m, &temp_v, rows, cols, nz_m, nz_v)))
            return rc;
    }

    // создание разреженной матрицы по обычной
    if (OK != (rc = convert_matrix(&temp_sp_m, temp_m)))
    {
        free_matrix(temp_m.matrix, temp_m.rows);
        free_matrix(temp_v.matrix, temp_v.rows);
        return rc;
    }
    // создание разреженного вектора по обычному
    if (OK != (rc = convert_matrix(&temp_sp_v, temp_v)))
    {
        free_matrix(temp_m.matrix, temp_m.rows);
        free_matrix(temp_v.matrix, temp_v.rows);
        free_sparce_matrix(&temp_sp_m);
        return rc;
    }

    if (1 == (*fr)) // исходные матрицы были заполнены
    {
        free_matrix(mtr->matrix, mtr->rows);
        free_matrix(vector->matrix, vector->rows);
        free_sparce_matrix(sp_mtr);
        free_sparce_matrix(sp_vector);
    }
    // копируем матрицы
    *mtr = temp_m;
    *vector = temp_v;
    *sp_mtr = temp_sp_m;
    *sp_vector = temp_sp_v;

    *fr = 1; // заполнили матрицы и вектора
    return OK;
}
