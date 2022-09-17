#include "../inc/mem_matrix.h"
#include "../inc/create_matrices.h"
#include "../inc/print_matrix.h"
#include "../inc/mult_matrices.h"
#include "../inc/cmp_mult_results.h"

int main(void)
{
    setbuf(stdout, NULL);
    matrix_s mtr, vector, res; // обычные матрицы
    sparse_matrix_s sp_mtr, sp_vector, sp_res; // разреженные матрицы
    int fr = 0, fm = 0, command = 1, rc = OK;

    // выполняем команды из меню
    while (command)
    {
        printf("\nВозможные действия (введите номер нужной команды):\n");
        printf("0. Завершить работу\n");
        printf("1. Ввести матрицу и вектор-столбец с клавиатуры\n");
        printf("2. Считать матрицу и вектор-столбец из файла\n");
        printf("3. Заполнить матрицу и вектор-столбец случайными числами\n");
        printf("4. Произвести умножение двумя способами\n");
        printf("5. Вывести результаты умножения двумя способами\n");
        printf("6. Вывести результаты сравнения двух способов умножения\n");
        printf("7. Вывести матрицу и вектор-столбец в обычном виде\n");
        printf("8. Вывести матрицу и вектор-столбец в разреженном виде\n");

        if (1 != scanf("%d", &command))
            continue;

        switch (command)
        {
            case 0:
                break;
            case 1:
                if (INPUT_ERROR == (rc = create_matrices(1, &mtr, &vector, &sp_mtr, &sp_vector, &fr)))
                    printf("Ошибка чтения\n");
                else if (MEMORY_ERROR == rc)
                    printf("Ошибка выделения памяти\n");
                break;
            case 2:
                if (INPUT_ERROR == (rc = create_matrices(2, &mtr, &vector, &sp_mtr, &sp_vector, &fr)))
                    printf("Ошибка чтения\n");
                else if (MEMORY_ERROR == rc)
                    printf("Ошибка выделения памяти\n");
                else if (FILE_ERROR == rc)
                    printf("Не удалось открыть указанный файл\n");
                break;
            case 3:
                if (INPUT_ERROR == (rc = create_matrices(3, &mtr, &vector, &sp_mtr, &sp_vector, &fr)))
                    printf("Ошибка чтения\n");
                else if (MEMORY_ERROR == rc)
                    printf("Ошибка выделения памяти\n");
                break;
            case 4:
                if (1 == fr) // матрица и вектор заполнены
                {
                    if (1 == fm) // уже умножали
                    {
                        free_matrix(res.matrix, res.rows);
                        free_sparce_matrix(&sp_res);
                        fm = 0;
                    }
                    // обычное умножение
                    if (OK != (rc = mult_mtrs(&res, mtr, vector)))
                        printf("Ошибка выделения памяти\n");
                    // умножение в разреженном формате
                    else if (MEMORY_ERROR == (rc = mult_sp_mtrs(&sp_res, sp_mtr, sp_vector)))
                    {
                        printf("Ошибка выделения памяти\n");
                        free_matrix(res.matrix, res.rows);
                    }
                    else if (EMPTY_MATRIX == rc)
                    {
                        printf("Матрица получилась нулевой\n");
                        free_matrix(res.matrix, res.rows);
                    }
                    else
                        fm = 1; // умножение удалось в обоих случаях
                }
                else
                    printf("Заполните матрицу и вектор-столбец\n");
                break;
            case 5:
                if (1 == fm) // умножение было выполнено
                {
                    printf("Результат обычного умножения:\n");
                    print_matrix(res);
                    printf("Результат в разреженном виде:\n");
                    print_sp_matrix(sp_res);
                }
                else
                    printf("Выполните умножение\n");
                break;
            case 6:
                cmp_mult_results();
                break;
            case 7:
                if (1 == fr) // матрица и вектор были заполнены
                {
                    printf("Матрица\n");
                    print_matrix(mtr);
                    printf("Вектор-столбец\n");
                    print_matrix(vector);
                }
                else
                    printf("Матрица и вектор-столбец не заполнены\n");
                break;
            case 8:
                if (1 == fr) // матрица и вектор были заполнены
                {
                    printf("Матрица\n");
                    print_sp_matrix(sp_mtr);
                    printf("Вектор-столбец\n");
                    print_sp_matrix(sp_vector);
                }
                else
                    printf("Матрица и вектор-столбец не заполнены\n");
                break;
            default:
                printf("Нет команды с введенным номером\n");
        }
    }

    if (1 == fr) // матрица и вектор были заполнены
    {
        free_matrix(mtr.matrix, mtr.rows);
        free_matrix(vector.matrix, vector.rows);
        free_sparce_matrix(&sp_mtr);
        free_sparce_matrix(&sp_vector);
    }

    if (1 == fm) // было умножение
    {
        free_matrix(res.matrix, res.rows);
        free_sparce_matrix(&sp_res);
    }

    return OK;
}
