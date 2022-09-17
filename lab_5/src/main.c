#include <stdio.h>
#include <time.h>
#include "../inc/queue_array.h"
#include "../inc/queue_list.h"
#include "../inc/return_codes.h"

int main(void)
{
    setbuf(stdout, NULL);
    queue_array_s q_arr;
    queue_list_s q_list;
    int command = 1, rc = OK, elem, list_max_cnt = 0;
    int t1_s = 0, t1_end = 5, t2_s = 0, t2_end = 4, t3_s = 0, t3_end = 4;
    clock_t list_work_t = 0, array_work_t = 0;
    char ch;
    // инициализация очереди в виде массива
    init_queue_array(&q_arr);
    // инициализация очереди в виде списка
    init_queue_list(&q_list);

    // выполняем команды из меню
    while (command)
    {
        printf("\nВозможные действия (введите номер нужной команды):\n");
        printf("0. Завершить работу\n");
        printf("1. Добавить элемент в очередь (массив)\n");
        printf("2. Добавить элемент в очередь (список)\n");
        printf("3. Удалить элемент из очереди (массив)\n");
        printf("4. Удалить элемент из очереди (список)\n");
        printf("5. Посмотреть текущее состояние очереди (массив)\n");
        printf("6. Посмотреть текущее состояние очереди (список)\n");
        printf("7. Вывести замеры времени и памяти для двух реализаций очереди\n");
        printf("8. Смоделировать процесс обслуживания первых 1000 заявок 1-го типа (массив)\n");
        printf("9. Смоделировать процесс обслуживания первых 1000 заявок 1-го типа (список)\n");
        printf("10. Изменить диапазоны времен прихода и обработки\n");

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
                else if (QUEUE_OVERFLOW == (rc = push_queue_array(&q_arr, elem)))
                    printf("Очередь уже заполнена\n");
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
                else if (MEMORY_ERROR == (rc = push_queue_list(&q_list, elem)))
                    printf("Ошибка выделения памяти\n");
                else
                    printf("Добавлен\n");
                break;
            case 3:
                if (EMPTY_QUEUE == (rc = pop_queue_array(&q_arr, &elem)))
                    printf("Очередь пустая\n");
                else
                    printf("%d\n", elem);
                break;
            case 4:
                if (EMPTY_QUEUE == (rc = pop_queue_list(&q_list, &elem)))
                    printf("Очередь пустая\n");
                else if (MEMORY_ERROR == rc)
                    printf("Ошибка выделения памяти\n");
                else
                    printf("%d\n", elem);
                break;
            case 5:
                print_cur_state_q_arr(&q_arr);
                break;
            case 6:
                print_cur_state_q_list(&q_list);
                break;
            case 7:
                // вывод заголовков таблицы
                printf("|%20s ", " ");
                printf("|%20s ", "number of elements");
                printf("|%27s ", "push time, in clock cycles");
                printf("|%27s ", "pop time, in clock cycles");
                printf("|memory, in bytes\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                print_work_results_q_arr(10);
                if (MEMORY_ERROR == print_work_results_q_list(10))
                    printf("Ошибка выделения памяти при работе с очередью в виде списка\n");
                print_work_results_q_arr(100);
                if (MEMORY_ERROR == print_work_results_q_list(100))
                    printf("Ошибка выделения памяти при работе с очередью в виде списка\n");
                print_work_results_q_arr(1000);
                if (MEMORY_ERROR == print_work_results_q_list(1000))
                    printf("Ошибка выделения памяти при работе с очередью в виде списка\n");
                print_work_results_q_arr(10000);
                if (MEMORY_ERROR == print_work_results_q_list(10000))
                    printf("Ошибка выделения памяти при работе с очередью в виде списка\n");
                printf("Время работы с заявками (массив) %ld, память под очередь %lld\n", array_work_t, MAX_ARRAY_SIZE * sizeof(int) + 2 * sizeof(int*));
                printf("Время работы с заявками (лист) %ld, память под очередь %lld\n", list_work_t, list_max_cnt * sizeof(node_s) + 2 * sizeof(node_s*));
                printf("Время - в тактах, память - в байтах\n");
                break;
            case 8:
                if (QUEUE_OVERFLOW == (rc = service_queue_array(t1_s, t1_end, t2_s, t2_end, t3_s, t3_end, &array_work_t)))
                    printf("Переполнение массива\n");
                break;
            case 9:
                if (MEMORY_ERROR == (rc = service_queue_list(t1_s, t1_end, t2_s, t2_end, t3_s, t3_end, &list_work_t, &list_max_cnt)))
                    printf("Ошибка выделения памяти\n");
                break;
            case 10:
                printf("Введите диапазоны для времени прихода заявки 1го типа и времен обработки заявок 1го и 2го типов\n");
                if (6 != scanf("%d %d %d %d %d %d", &t1_s, &t1_end, &t2_s, &t2_end, &t3_s, &t3_end) || t1_s < 0 || t1_end < 0 || 
                t2_s < 0 || t2_end < 0 || t3_s < 0 || t3_end < 0 || t1_s >= t1_end || t2_s >= t2_end || t3_s >= t3_end)
                {
                    scanf("%c", &ch);
                    while ('\n' != ch)
                        scanf("%c", &ch);
                    printf("Ошибка ввода\n");
                    t1_s = 0;
                    t1_end = 5;
                    t2_s = 0;
                    t2_end = 4; 
                    t3_s = 0; 
                    t3_end = 4;
                }
                break;
            default:
                printf("Нет команды с введенным номером\n");
        }
    }
    // надо освободить память из под списка
    free_queue_list(&q_list);
}
