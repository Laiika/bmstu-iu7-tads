#include <stdio.h>
#include "../inc/stack_array.h"
#include "../inc/stack_list.h"
#include "../inc/return_codes.h"

int main(void)
{
    setbuf(stdout, NULL);
    stack_array_s st_arr;
    stack_list_s st_list;
    int command = 1, rc = OK, elem;
    char ch;
    // инициализация стека в виде массива
    init_stack_array(&st_arr);
    // инициализация стека в виде списка
    init_stack_list(&st_list);

    // выполняем команды из меню
    while (command)
    {
        printf("\nВозможные действия (введите номер нужной команды):\n");
        printf("0. Завершить работу\n");
        printf("1. Добавить элемент в стек (массив)\n");
        printf("2. Добавить элемент в стек (список)\n");
        printf("3. Удалить элемент из стека (массив)\n");
        printf("4. Удалить элемент из стека (список)\n");
        printf("5. Посмотреть текущее состояние стека (массив)\n");
        printf("6. Посмотреть текущее состояние стека (список)\n");
        printf("7. Вывести замеры времени и памяти для двух реализаций стека\n");
        printf("8. Вывести убывающие серии чисел из стека в обратном порядке (массив)\n");
        printf("9. Вывести убывающие серии чисел из стека в обратном порядке (список)\n");

        if (1 != scanf("%d", &command))
            continue;

        switch (command)
        {
            case 0:
                break;
            case 1:
                printf("Введите целое число: ");
                if (1 != scanf("%d", &elem))
                {
                    scanf("%c", &ch);
                    while ('\n' != ch)
                        scanf("%c", &ch);
                    printf("Ошибка ввода\n");
                }
                else if (STACK_OVERFLOW == (rc = push_stack_array(&st_arr, elem)))
                    printf("Стек уже заполнен\n");
                else
                    printf("Добавлен\n");
                break;
            case 2:
                printf("Введите целое число: ");
                if (1 != scanf("%d", &elem))
                {
                    scanf("%c", &ch);
                    while ('\n' != ch)
                        scanf("%c", &ch);
                    printf("Ошибка ввода\n");
                }
                else if (STACK_OVERFLOW == (rc = push_stack_list(&st_list, elem)))
                    printf("Стек уже заполнен\n");
                else if (MEMORY_ERROR == rc)
                    printf("Ошибка выделения памяти\n");
                else
                    printf("Добавлен\n");
                break;
            case 3:
                if (EMPTY_STACK == (rc = pop_stack_array(&st_arr, &elem)))
                    printf("Стек пустой\n");
                else
                    printf("%d\n", elem);
                break;
            case 4:
                if (EMPTY_STACK == (rc = pop_stack_list(&st_list, &elem)))
                    printf("Стек пустой\n");
                else if (MEMORY_ERROR == rc)
                    printf("Ошибка выделения памяти\n");
                else
                    printf("%d\n", elem);
                break;
            case 5:
                print_cur_state_st_arr(&st_arr);
                break;
            case 6:
                print_cur_state_st_list(&st_list);
                break;
            case 7:
                // вывод заголовков таблицы
                printf("|%20s ", " ");
                printf("|%20s ", "number of elements");
                printf("|%27s ", "push time, in clock cycles");
                printf("|%27s ", "pop time, in clock cycles");
                printf("|memory, in bytes\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                print_work_results_st_arr(10);
                if (MEMORY_ERROR == print_work_results_st_list(10))
                    printf("Ошибка выделения памяти при работе со стеком в виде списка\n");
                print_work_results_st_arr(100);
                if (MEMORY_ERROR == print_work_results_st_list(100))
                    printf("Ошибка выделения памяти при работе со стеком в виде списка\n");
                print_work_results_st_arr(1000);
                if (MEMORY_ERROR == print_work_results_st_list(1000))
                    printf("Ошибка выделения памяти при работе со стеком в виде списка\n");
                print_work_results_st_arr(10000);
                if (MEMORY_ERROR == print_work_results_st_list(10000))
                    printf("Ошибка выделения памяти при работе со стеком в виде списка\n");
                break;
            case 8:
                if (EMPTY_STACK == print_series_reverse_st_arr(&st_arr))
                    printf("Стек пустой\n");
                break;
            case 9:
                if (EMPTY_STACK == (rc = print_series_reverse_st_list(&st_list)))
                    printf("Стек пустой\n");
                else if (MEMORY_ERROR == rc)
                    printf("Ошибка выделения памяти\n");
                break;
            default:
                printf("Нет команды с введенным номером\n");
        }
    }
    // надо освободить память из под списка
    free_stack_list(&st_list);
}
