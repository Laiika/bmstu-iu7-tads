#include "perf.h"
#include "perfs.h"

// функция для печати записи о спектакле в файл
void print_perf_file(FILE *file, performance_s perf)
{
    fprintf(file, "%s\n", perf.theatre_name);
    fprintf(file, "%s\n", perf.performance_name);
    fprintf(file, "%s\n", perf.director);
    fprintf(file, "%d\n", perf.price_range[0]);
    fprintf(file, "%d\n", perf.price_range[1]);
    fprintf(file, "%d\n", perf.type.num);

    if (CHILD == perf.type.num)
    {
        fprintf(file, "%d\n", perf.type.cont.child.age);
        fprintf(file, "%d", perf.type.cont.child.type);
    }
    else if (ADULT == perf.type.num)
        fprintf(file, "%d", perf.type.cont.adult);
    else
    {
        fprintf(file, "%s\n", perf.type.cont.music.composer);
        fprintf(file, "%s\n", perf.type.cont.music.country);
        fprintf(file, "%d\n", perf.type.cont.music.min_age);
        fprintf(file, "%d", perf.type.cont.music.duration);
    }
}

// функция для добавления записи о спектакле в конец файла и массива
int add_perf(char *file_name, performance_s *const arr, int *const size)
{
    if (ARRAY_SIZE == *size)
        return FULL_ARRAY;
    else
    {
        int rc;
        performance_s cur;

        if (OK != (rc = read_perf_console(&cur))) // читаем запись из консоли
            return rc;  
        else
        {
            // добавляем в массив
            arr[*size] = cur;
            (*size)++;

            FILE *file = fopen(file_name, "a");
            // добавляем в файл
            if (*size > 0)
                fprintf(file, "\n");

            print_perf_file(file, cur);
            fclose(file);
        }
    }    
    
    return OK;
}

// функция для удаления записи о спектакле из массива и файла
int delete_perf(char *file_name, performance_s *const arr, int *const size)
{
    int i; // индекс удаляемой записи

    printf("Введите индекс удаляемой записи: ");
    
    if (1 != scanf("%d", &i) || i < 0 || i >= *size)
        return READ_ERROR;
    else
    {
        // удаляем из массива
        for (int j = i; j < (*size) - 1; j++)
            arr[j] = arr[j + 1];

        (*size)--;

        FILE *file = fopen(file_name, "w");

        // перезаписываем файл без этой записи
        for (int j = 0; j < *size; j++)
        {
            print_perf_file(file, arr[j]);

            if ((*size) - 1 != j)
                fprintf(file, "\n");
        }

        fclose(file);
    }  

    return OK;
}
