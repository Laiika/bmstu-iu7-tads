#include "../inc/cmp_mult_results.h"

// функция для вывода строки в случае ошибки при замерах
void failes_meas()
{
    printf("|%-20s ", "-----");
    printf("|%-20s ", "-----");
    printf("|%-20s ", "-----");
    printf("|%-20s ", "-----");
    printf("|%-20s ", "-----");
    printf("|-----\n\n");
}

// функция для вывода результатов замеров
void success_meas(int rows, int cols, int perc, float time_us, float time_sp, int mem_us, int mem_sp)
{
    printf("|%-5d*%5d, %5d*1 ", rows, cols, cols);
    printf("|%9d%%, %7d%% ", perc, perc);
    printf("|%20f ", time_us);
    printf("|%20d ", mem_us);
    printf("|%20f ", time_sp);
    printf("|%d\n\n", mem_sp);
}

// функция для вывода таблицы со сравнением по времени и памяти двух видов умножения
void cmp_mult_results()
{
    matrix_s mtr, vector, res; // обычные матрицы
    sparse_matrix_s sp_mtr, sp_vector, sp_res; // разреженные матрицы
    
    clock_t start; // время до
    int time_us, time_sp, cnt_us, cnt_sp, mem_us, mem_sp, res_mem_us, res_mem_sp, rc = OK;

    // вывод заголовков таблицы
    printf("|%-20s ", "mtr, vector sizes");
    printf("|%-20s ", "mtr, vector fullness");
    printf("|%-20s ", "ordinary mult time");
    printf("|%-20s ", "ordinary mult memory");
    printf("|%-20s ", "sparse mult time");
    printf("|sparce mult memory\n");
    printf("----------------------------------------------------------------------");
    printf("----------------------------------------------------------------------\n");
    // цикл по размеру матрицы
    for (int i = 100; i <= 500; i = i + 100)
    {
        // цикл по заполненности ненулевыми элементами
        for (int j = i / 4; j <= i; j += i / 4)
        {
            // создание обычной матрицы и вектора
            if (OK != (rc = create_with_random(&mtr, &vector, i, i, j * i, j)))
            {
                failes_meas();
                continue;
            }
            // создание разреженной матрицы
            if (OK != convert_matrix(&sp_mtr, mtr))
            {
                free_matrix(mtr.matrix, mtr.rows);
                free_matrix(vector.matrix, vector.rows);
                failes_meas();
                continue;
            }
            // создание разреженного вектора
            if (OK != convert_matrix(&sp_vector, vector))
            {
                free_matrix(mtr.matrix, mtr.rows);
                free_matrix(vector.matrix, vector.rows);
                free_sparce_matrix(&sp_mtr);
                failes_meas();
                continue;
            }
            // замеры времени и количества повторов
            time_us = 0, time_sp = 0, cnt_us = 0, cnt_sp = 0;
            // замеры памяти
            mem_us = sizeof(int) * (mtr.rows * mtr.columns + mtr.rows + 1 + vector.rows + vector.rows + 1);
            mem_sp = sizeof(int) * (sp_mtr.not_zero * 2 + sp_mtr.rows + 1 + sp_vector.not_zero * 2 + sp_vector.rows + 1);
            // повторы умножения
            for (int k = 0; k < 100; k++)
            {
                start = clock();
                rc = mult_mtrs(&res, mtr, vector);
                // обычное умножение
                if (OK != rc)
                    continue;

                time_us += clock() - start;
                cnt_us++;

                start = clock();
                rc = mult_sp_mtrs(&sp_res, sp_mtr, sp_vector);
                // умножение в разреженном формате
                if (OK != (rc = mult_sp_mtrs(&sp_res, sp_mtr, sp_vector)))
                {
                    free_matrix(res.matrix, res.rows);
                    continue;
                }

                time_sp += clock() - start;
                cnt_sp++;

                // замеры по памяти результата
                res_mem_us = sizeof(int) * (res.rows + res.rows + 1);
                res_mem_sp = sizeof(int) * (sp_res.not_zero * 2 + sp_res.rows + 1);

                free_matrix(res.matrix, res.rows);
                free_sparce_matrix(&sp_res);
            }

            free_matrix(mtr.matrix, mtr.rows);
            free_matrix(vector.matrix, vector.rows);
            free_sparce_matrix(&sp_mtr);
            free_sparce_matrix(&sp_vector);
            // вывод результатов замеров
            success_meas(i, i, j * 100 / i, (float)time_us / cnt_us, (float)time_sp / cnt_sp, mem_us + res_mem_us, mem_sp + res_mem_sp);
        }
    }
}
