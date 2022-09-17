#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/queue_list.h"

// функция для инициализации очереди
void init_queue_list(queue_list_s *queue)
{
    queue->start = NULL;
    queue->end = NULL;
    queue->cnt = 0;
    queue->free_nodes = NULL;
    queue->free_nodes_end = NULL;
    queue->free_cnt = 0;
}

// функция для освобождения памяти из под очереди
void free_queue_list(queue_list_s *queue)
{
    node_s *next;
    // освобождение памяти из под очереди
    for (next = queue->start; queue->start; queue->start = next)
    {
        next = queue->start->next;
        free(queue->start);
    }

    free_node_s *next2;
    // освобождение памяти из под списка адресов
    for (next2 = queue->free_nodes; queue->free_nodes; queue->free_nodes = next2)
    {
        next2 = queue->free_nodes->next;
        free(queue->free_nodes);
    }
}

// функция для добавления элемента в конец очереди
int push_queue_list(queue_list_s *queue, int elem)
{
    // создание нового элемента
    node_s *new_node = NULL;
    new_node = calloc(1, sizeof(node_s));

    if (!new_node)
        return MEMORY_ERROR;
    
    new_node->val = elem;
    new_node->next = NULL;

    // в очереди еще нет элементов
    if (0 == queue->cnt)
        queue->start = new_node;
    else
        queue->end->next = new_node;

    // добавление элемента в конец очереди
    queue->end = new_node;
    (queue->cnt)++;
    
    return OK;
}

// функция для удаления элемента из начала очереди
int pop_queue_list(queue_list_s *queue, int *elem)
{
    // очередь пустая
    if (0 == queue->cnt)
        return EMPTY_QUEUE;

    // создание нового элемента списка адресов
    free_node_s *new_free_node = NULL;
    new_free_node = calloc(1, sizeof(free_node_s));

    if (!new_free_node)
        return MEMORY_ERROR;

    new_free_node->adr = queue->start;
    new_free_node->next = NULL; 

    // в списке адресов еще нет элементов
    if (0 == queue->free_cnt)
        queue->free_nodes = new_free_node;
    else
        queue->free_nodes_end->next = new_free_node;

    // добавление элемента в конец списка адресов
    queue->free_nodes_end = new_free_node;
    (queue->free_cnt)++;

    *elem = queue->start->val;
    // перемещение указателя начала очереди к следующему элементу
    node_s *new_node = queue->start->next;
    free(queue->start);
    queue->start = new_node;
    (queue->cnt)--;

    return OK;
}

// функция печати текущего состояния очереди
void print_cur_state_q_list(queue_list_s *queue)
{
    printf("В очереди %d элементов\n", queue->cnt);
    // в очереди есть элементы
    if (queue->cnt)
    {
        // вывод всех элементов очереди
        for (node_s *cur = queue->start; cur; cur = cur->next)
            printf("Адрес элемента: %p, значение: %d\n", (void*)cur, cur->val);
    }

    printf("Освобождено %d областей памяти\n", queue->free_cnt);
    // вывод адресов освобожденной памяти
    for (free_node_s *cur = queue->free_nodes; cur; cur = cur->next)
        printf("Адрес освобожденной области памяти: %p\n", (void*)cur->adr);
}

// функция для вывода времени выполнения операций push, pop и памяти, выделяемой под очередь
int print_work_results_q_list(int cnt)
{
    queue_list_s queue;
    clock_t start; // время до
    clock_t push_time = 0, pop_time = 0;
    int elem, rep = 1000, mem;

    for (int j = 0; j < rep; j++)
    {
        // инициализация очереди
        init_queue_list(&queue);

        // время выполнения push
        start = clock();

        for (int i = 0; i < cnt; i++)
        {
            if (MEMORY_ERROR == push_queue_list(&queue, i))
            {
                free_queue_list(&queue);
                return MEMORY_ERROR;
            }
        }

        push_time += clock() - start;
        // время выполнения pop
        start = clock();

        for (int i = 0; i < cnt; i++)
        {
            if (MEMORY_ERROR == pop_queue_list(&queue, &elem))
            {
                free_queue_list(&queue);
                return MEMORY_ERROR;
            }
        }

        pop_time += clock() - start;
        // память под очередь
        mem = 2 * sizeof(node_s*) + cnt * sizeof(node_s);
        free_queue_list(&queue);
    }

    printf("|%20s ", "list");
    printf("|%20d ", cnt);
    printf("|%27f ", (float)push_time / rep);
    printf("|%27f ", (float)pop_time / rep);
    printf("|%d\n\n", mem);
    return OK;
}

// функция для обработки очереди заявок двух типов
int service_queue_list(int t1_s, int t1_end, int t2_s, int t2_end, int t3_s, int t3_end, clock_t *time, int *max_cnt)
{
    clock_t start = clock();
    *max_cnt = 0;
    queue_list_s queue;
    init_queue_list(&queue);
    node_s *adrs[30]; // массив адресов элементов очереди при добавлении (первые 30)
    int size = 0;

    printf("t1 - [%d; %d], t2 - [%d; %d], t3 - [%d; %d]\n\n", t1_s, t1_end, t2_s, t2_end, t3_s, t3_end);

    double t_in = (float)rand() / RAND_MAX * (t1_end - t1_s) + t1_s; // время поступления заявки
    double t_out = (float)rand() / RAND_MAX * (t3_end - t3_s) + t3_s; // время выхода после обработки
    int cnt1_in = 0, cnt1_process = 0; // количество поступивших и обработанных заявок 1го типа
    int sum_len_queue = 0, del = 0; // для вычисления средней длины очереди
    double aver_t = 0; // среднее время пребывания заявки в очереди
    double time_in_all1 = t_in; // суммарное время поступления всех заявок 1го типа
    double time_process_all1 = 0; // суммарное время обработки всех заявок 1го типа
    double time_process_all2 = t_out; // суммарное время обработки заявки 2го типа
    int type = 2; // начали с обработки заявки 2го типа
    int cnt2_process = 1; // количество обращений заявки 2го типа
    // среднее время прихода заявки 1го типа и обработки заявок 1го и 2го типа
    double aver_t_in = ((double)t1_end + t1_s) / 2;
    double aver_t_proc1 = ((double)t2_end + t2_s) / 2, aver_t_proc2 = ((double)t3_end + t3_s) / 2;

    // пока не обработана 1000 заявок 1го типа
    while (cnt1_process < 1000)
    {
        if (t_in < t_out)
        {
            // поступление заявки 1го типа в конец очереди
            if (MEMORY_ERROR == push_queue_list(&queue, 1))
            {
                free_queue_list(&queue);
                return MEMORY_ERROR;
            }

            if (size < 30)
                adrs[size++] = queue.end;

            if (*max_cnt < queue.cnt)
                *max_cnt = queue.cnt;

            t_out -= t_in;
            cnt1_in++;

            if (0 != queue.cnt)
                del++;

            sum_len_queue += queue.cnt;
            // время поступления новой заявки 1го типа
            t_in = (float)rand() / RAND_MAX * (t1_end - t1_s) + t1_s;

            if (cnt1_in < 1000)
                time_in_all1 += t_in;
        }
        else
        {
            // обработка закончилась
            t_in -= t_out;
            // закончили обработку заявки 2го типа
            if (2 == type)
            {
                // добавление заявки 2го типа в очередь
                if (queue.cnt < 4)
                {
                    if (MEMORY_ERROR == push_queue_list(&queue, 2))
                    {
                        free_queue_list(&queue);
                        return MEMORY_ERROR;
                    }
                }
                else
                {
                    node_s *cur = queue.start;

                    for (int i = 0; i < 3; i++)
                        cur = cur->next;

                    cur->val = 2;

                    if (MEMORY_ERROR == push_queue_list(&queue, 1))
                    {
                        free_queue_list(&queue);
                        return MEMORY_ERROR;
                    }
                }

                if (size < 30)
                    adrs[size++] = queue.end;
            }
            else // закончили обработку заявки 1го типа
            {
                if (0 < queue.cnt - 1)
                {
                    sum_len_queue += queue.cnt - 1;
                    del++;
                }

                if (cnt1_process > 0 && 0 == cnt1_process % 100)
                {
                    printf ("Текущая длина очереди %d, средняя длина %d\n", queue.cnt, sum_len_queue / del);
                    printf("Количество вошедших заявок 1го типа %d, обработанных заявок 1го типа %d\n", cnt1_in, cnt1_process);
                    printf("Количество обращений заявки 2го типа %d\n", cnt2_process);
                    aver_t = (sum_len_queue / del / 3) * (3 * aver_t_proc1 + aver_t_proc2) + (sum_len_queue / del % 3) * aver_t_proc1;
                    printf("Среднее время пребывания заявок в очереди %f\n\n", aver_t);
                }
            }       

            // после обработки из головы очереди извлекается новая заявки и идет на обработку
            if (MEMORY_ERROR == pop_queue_list(&queue, &type))
            {
                free_queue_list(&queue);
                return MEMORY_ERROR;
            }

            // на обработку сейчас отправилась заявка 1го типа
            if (1 == type)
            {
                cnt1_process++;
                t_out = (float)rand() / RAND_MAX * (t2_end - t2_s) + t2_s;
                time_process_all1 += t_out;
            }
            else
            {
                cnt2_process++;
                t_out = (float)rand() / RAND_MAX * (t3_end - t3_s) + t3_s;
                time_process_all2 += t_out;
            }
        }
    }
    // расчетные и фактические времена моделирования по входу и выходу
    double model_t_in = 1000 * aver_t_in; 
    double model_t_out = cnt1_process * aver_t_proc1 + cnt2_process * aver_t_proc2, fact_t_out = time_process_all1 + time_process_all2;
    // определение расчетного и фактического времени моделирования
    double model_time = model_t_in > model_t_out ? model_t_in : model_t_out;
    double fact_time = time_in_all1 > fact_t_out ? time_in_all1 : fact_t_out;
    printf("Расчетное время моделирования %f, фактическое %f\n", model_time, fact_time);
    printf("Время простоя аппарата %f\n", time_in_all1 - fact_t_out);
    printf("Количество вошедших заявок 1го типа %d, обработанных заявок 1го типа %d\n", cnt1_in, cnt1_process);
    printf("Количество обращений заявки 2го типа %d\n\n", cnt2_process);
    // определение погрешности
    double d = fabs(fact_time - model_time) / model_time * 100;
    printf("Погрешность составляет 100%% * |%f - %f| / %f = %f%%\n\n", fact_time, model_time, model_time, d);
    *time = clock() - start;

    int i;
    printf("Введите 1, чтобы посмотреть адреса элементов очереди при удалении и добавлении элементов (первые 30), \n");
    printf("иначе 0\n");
    scanf("%d", &i);
    // вывод адерос элементов при добавлении и удалении
    if (1 == i)
    {
        free_node_s *cur = queue.free_nodes;

        for (int j = 0; cur && j < size; cur = cur->next, j++)
        {
            printf("Адрес при добавлении %p     ", (void*)adrs[j]);
            printf("Адрес освобожденной области памяти при удалении: %p\n", (void*)cur->adr);
        }

        printf("\n");
    }

    free_queue_list(&queue);
    return OK;
}
