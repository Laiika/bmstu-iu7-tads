#include "perf.h"
#include "perfs.h"
#include "key.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    FILE *file = NULL;

    // файл не указан
    if (2 != argc)
    {
        printf("Не указан файл\n");
        return ARGC_ERROR;
    }

    if (NULL == (file = fopen(argv[1], "r")))
    {
        printf("Не удалось открыть указанный файл\n");
        return FILE_ERROR;
    }

    performance_s arr[ARRAY_SIZE]; // массив спектаклей
    int rc, size;

    if (OK != (rc = read_perfs(file, arr, &size)))
    {
        printf("Не удалось считать записи из файла\n");
        fclose(file);  
        return rc;
    }
    fclose(file);

    perf_min_price_s keys[ARRAY_SIZE]; // массив ключей
    char ch;
    int command = 1;
    // выполняем команды из меню
    while (command)
    {
        printf("\nВозможные действия (введите номер нужной команды):\n");
        printf("0. Завершить работу\n");
        printf("1. Добавить запись о спектакле в таблицу\n");
        printf("2. Удалить запись о спектакле из таблицы\n");
        printf("3. Вывести список всех музыкальных спектаклей для детей указанного возраста с продолжительностью меньше указанной\n");
        printf("4. Вывести отсортированную таблицу ключей при несортированной исходной таблице\n");
        printf("5. Вывести упорядоченную исходную таблицу\n");
        printf("6. Вывести исходную таблицу в упорядоченном виде, используя упорядоченную таблицу ключей\n");
        printf("7. Вывести результаты использования различных алгоритмов сортировок\n");
        printf("8. Вывести исходную таблицу\n");

        if (1 != scanf("%d", &command))
            continue;

        switch (command)
        {
            case 0:
                break;
            case 1:
                scanf("%c", &ch);
                if (FULL_ARRAY == (rc = add_perf(argv[1], arr, &size)))
                    printf("Таблица уже заполнена\n");
                else if (OK != rc)
                    printf("Ошибка ввода\n");
                scanf("%c", &ch);
                break;
            case 2:
                if (OK != delete_perf(argv[1], arr, &size))
                    printf("Ошибка ввода\n");
                scanf("%c", &ch);
                break;
            case 3:
                if (OK != (rc = search(arr, size)))
                    printf("Ошибка ввода\n");
                scanf("%c", &ch);
                break;
            case 4:
                file = fopen(argv[1], "r");
                read_perfs(file, arr, &size); // читаем исходную таблицу
                fclose(file);
                get_keys_array(arr, keys, size); // получаем таблицу ключей на основе исходной
                qsort_keys(keys, 0, size - 1); // сортируем таблицу ключей
                print_keys_table(keys, size); // печатаем таблицу ключей после сортировки
                break;
            case 5:
                qsort_perfs(arr, 0, size - 1);
                print_perfs_table(arr, size); // печатаем таблицу спектаклей после сортировки
                break;
            case 6:
                file = fopen(argv[1], "r");
                read_perfs(file, arr, &size); // читаем исходную таблицу
                fclose(file);
                get_keys_array(arr, keys, size); // получаем таблицу ключей на основе исходной
                qsort_keys(keys, 0, size - 1); // сортируем таблицу ключей
                print_perfs_table_keys(arr, keys, size); // печатаем таблицу спектаклей по таблице ключей
                break;
            case 7:
                file = fopen(argv[1], "r");
                printf("Время пузырьковой сортировки исходной таблицы: %f\n", bubble_perfs_time(file, arr, size));
                printf("Время быстрой сортировки исходной таблицы: %f\n", qsort_perfs_time(file, arr, size));
                read_perfs(file, arr, &size); // читаем исходную таблицу
                get_keys_array(arr, keys, size); // получаем таблицу ключей на основе исходной
                fclose(file);
                printf("Время пузырьковой сортировки таблицы ключей: %f\n",bubble_keys_time(arr, keys, size));
                printf("Время быстрой сортировки таблицы ключей: %f\n", qsort_keys_time(arr, keys, size));
                break;
            case 8:
                file = fopen(argv[1], "r");
                read_perfs(file, arr, &size); // читаем исходную таблицу
                fclose(file);
                print_perfs_table(arr, size); // печатаем исходную таблицу
                break;
            default:
                printf("Нет команды с введенным номером\n");
        }
    }
  
    return OK;
}
