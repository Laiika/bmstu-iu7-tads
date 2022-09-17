#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "../inc/return_codes.h"
#include "../inc/tree.h"
#include "../inc/hash_table.h"

#define MAX_FILE_NAME 30

// функция для чтения имени файла
int read_file_name(char *const str, const int size)
{
    if (!fgets(str, size, stdin))
        return STRING_INPUT_ERROR;

    int ch, len = strlen(str);

    if ((len == MAX_FILE_NAME) && ((ch = getchar()) != '\n' && ch != EOF))
        return STRING_INPUT_ERROR;

    if (str[0] == '\n')
        return STRING_INPUT_ERROR;

    if (str[len - 1] == '\n')
        str[len - 1] = '\0';

    return OK;
}

// функция для посчета количества чисел в файле
int get_nums_cnt(FILE *file)
{
    int cnt = 0, num;

    while (1 == fscanf(file, "%d", &num))
        cnt++;

    rewind(file);
    return cnt;
}

// функция для освобождения памяти из под структур
void free_structures(tree_node_s **bst, tree_node_s **avl, hash_table_s **ht)
{
    tree_free_all(*bst);
    *bst = tree_init();
    tree_free_all(*avl);
    *avl = tree_init();
    hash_table_free(*ht);
    *ht = NULL;
}

// функция для вывода времени добавления в файл, памяти и количества сравнений
void file_print_insert_results()
{
    FILE *f;
    clock_t start; // время до
    clock_t time = 0;
    int cmps = 0,  mem;
    
    f = fopen("test.txt", "w");
    fclose(f);
    // время выполнения
    start = clock();

    for (int i = 0; i < 500; i++)
    {
        f = fopen("test.txt", "a");
        fprintf(f, "%d\n", i);
        fclose(f);
    }
        
    time += clock() - start;
    // память под файл
    mem = 500 * sizeof("10\n");

    printf("|%20s ", "file");
    printf("|%27f ", (float)time / 500);
    printf("|%27d ", mem);
    printf("|%f\n\n", (float)cmps / 500);
}

int main(void)
{
    setbuf(stdout, NULL);
    char name[MAX_FILE_NAME + 1];  // имя исходного файла
    FILE *in = NULL, *out = NULL;
    tree_node_s *bst = tree_init(), *bst_node;  // ддп
    tree_node_s *avl = tree_init(), *avl_node;  // авл дерево
    hash_table_s *ht = NULL, *ht2 = NULL;  // хеш-таблица
    int num, num2, cnt, command = 1, h, cmps, max_cmps = 4, rc;
    int (*hash_func)(int, int) = simple_hash_func;
    char ch;

    // выполняем команды из меню
    while (command)
    {
        printf("\nВозможные действия (введите номер нужной команды):\n");
        printf("0. Завершить работу\n");
        printf("1. Ввести имя исходного файла\n");
        printf("2. Вывести ДДП\n");
        printf("3. Вывести АВЛ дерево\n");
        printf("4. Вывести хеш-таблицу\n");
        printf("5. Добавить целое число в деревья, таблицу и файл\n");
        printf("6. Задать максимальное число сравнений для хеш-таблицы\n");
        printf("7. Сравнить время добавления, объем памяти и количество сравнений при использовании 4-х структур данных\n");

        if (1 != scanf("%d", &command))
            continue;

        switch (command)
        {
            case 0:
                break;
            case 1:
                scanf("%c", &ch);
                if (OK == read_file_name(name, sizeof(name))) // чтение имени исходного файла
                {
                    if (NULL != (in = fopen(name, "r"))) 
                    {
                        // очистка деревьев и хеш-таблицы
                        free_structures(&bst, &avl, &ht);
                        cnt = get_nums_cnt(in);

                        if (cnt > 0)
                            ht = hash_table_init(2 * cnt);
                        // читаем по одному числу из файла
                        while (ht && cnt && 1 == fscanf(in, "%d", &num))
                        {
                            // добавление в двоичное дерево поиска
                            bst_node = tree_node_create(num);
                            if (bst_node)
                                bst = tree_insert(bst, bst_node, &num2);
                            else
                            {
                                free_structures(&bst, &avl, &ht);
                                printf("Ошибка выделения памяти\n");
                                break;
                            }
                            // добавление в авл дерево
                            avl_node = tree_node_create(num);
                            h = 0;
                            if (avl_node)
                                avl = balanced_tree_insert(avl, avl_node, &h, &num2);
                            else
                            {
                                free_structures(&bst, &avl, &ht);
                                printf("Ошибка выделения памяти\n");
                                break;
                            }
                            // добавление в хеш-таблицу
                            if (NOT_FOUND == (cmps = hash_table_insert(ht, num, hash_func)))
                            {
                                free_structures(&bst, &avl, &ht);
                                printf("Не получилось добавить элемент в хеш-таблицу\n");
                                break;
                            }
                        }

                        if (!feof(in))
                        {
                            free_structures(&bst, &avl, &ht);
                            printf("Ошибка чтения из файла\n");
                        }
                        else if (cnt <= 0)
                            printf("Файл не содержит целых чисел\n");
                        else if (!ht)
                            printf("Ошибка выделения памяти\n");
                        else
                            printf("Выполнено\n");

                        fclose(in);
                    }
                    else
                        printf("Ошибка открытия файла\n");
                }
                else
                    printf("Ошибка ввода\n");
                break;
            case 2:
                if (bst && NULL != (out = fopen("bst.gv", "w"))) // открытие файла на запись ддп
                {
                    tree_export_to_dot(out, bst);
                    fclose(out);
                    system("dot -Tpng bst.gv -o bst.png");
                }
                else 
                    printf("Дерево не создано\n");
                break;
            case 3:
                if (avl && NULL != (out = fopen("avl.gv", "w"))) // открытие файла на запись авл дерева
                {
                    tree_export_to_dot(out, avl);
                    fclose(out);
                    system("dot -Tpng avl.gv -o avl.png");
                }
                else 
                    printf("Дерево не создано\n");
                break;
            case 4:
                if (ht)
                {
                    hash_table_print(ht);
                    printf("%d\n", ht->size);
                }
                else 
                    printf("Таблица не создана\n");
                break;
            case 5:
                printf("Введите целое число: ");
                if (1 != scanf("%d", &num)) // ошибка ввода числа
                {
                    scanf("%c", &ch);
                    while ('\n' != ch)
                        scanf("%c", &ch);
                    printf("Ошибка ввода\n");
                }
                else if (!ht || NULL == (in = fopen(name, "a")))
                    printf("Входной файл не указан\n");
                else if (!tree_find(bst, num)) // введенного числа еще нет
                {
                    rc = OK;
                    if (ht->cur_size == ht->size)  // хеш-таблица полностью занята
                    {
                        hash_table_resize(ht, ht->size * 2);

                        if (ht->cur_size == ht->size)
                        {
                            rc = MEMORY_ERROR;
                            printf("Ошибка выделения памяти\n");
                        }
                    }

                    if (OK == rc)
                    {
                        // добавление числа в ддп
                        bst_node = tree_node_create(num);
                        if (bst_node)
                        {
                            // добавление числа в авл дерево
                            avl_node = tree_node_create(num);
                            h = 0;

                            if (avl_node)
                            {
                                // добавление числа в хеш-таблицу
                                if (NOT_FOUND != (cmps = hash_table_insert(ht, num, hash_func)))
                                {
                                    bst = tree_insert(bst, bst_node, &num2);
                                    avl = balanced_tree_insert(avl, avl_node, &h, &num2);
                                    fprintf(in, "%d\n", num);  // добавление числа в файл
                                }
                                else
                                {
                                    tree_node_free(bst_node);
                                    tree_node_free(avl_node);
                                    printf("Ошибка добавления в хеш-таблицу\n"); 
                                }
                            }
                            else
                            {
                                tree_node_free(bst_node);
                                printf("Ошибка выделения памяти\n"); 
                            }
                        }
                        else
                            printf("Ошибка выделения памяти\n");   
                    }

                    fclose(in);
                }   
                else
                {
                    printf("Такое число уже есть\n");    
                    fclose(in);
                } 
                break;
            case 6:
                if (ht)
                {
                    printf("Введите положительное целое число: ");
                    if (1 != scanf("%d", &num) || num <= 0) // ошибка ввода числа
                    {
                        scanf("%c", &ch);
                        while ('\n' != ch)
                            scanf("%c", &ch);
                        printf("Ошибка ввода\n");
                    }
                    else
                        max_cmps = num;  // максимальное количество сравнений
                }
                else 
                    printf("Таблица не создана\n");
                break;
            case 7:
                printf("Приведены значения памяти при добавлении 500 чисел\n");
                // вывод заголовков таблицы
                printf("|%20s ", "structure");
                printf("|%27s ", "time, in clock cycles");
                printf("|%27s ", "memory, in bytes");
                printf("|number of comparisons\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                bst_print_insert_results();
                avl_print_insert_results();
                hash_table_print_insert_results();
                file_print_insert_results();
                break;
            default:
                printf("Нет команды с введенным номером\n");
        }

        // количество сравнений в хеш-таблице больше указанного
        if (ht && (max_cmps < cmps || NOT_FOUND == cmps) && hash_func == simple_hash_func)
        { 
            printf("Количество сравнений в хеш-таблице превышено, попытка реструктуризировать хеш-таблицу\n");
            // реструктуризация хеш-таблицы
            ht2 = hash_table_restruct(ht, complex_hash_func);

            if (ht2)
            {
                ht = ht2;
                hash_func = complex_hash_func;
                printf("Удалось реструктуризировать хеш-таблицу\n");
            }
            else
                printf("Не удалось реструктуризировать хеш-таблицу\n");
        }
    }

    tree_free_all(bst);
    tree_free_all(avl);
    hash_table_free(ht);
}
