#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/queue_array.h"

// функция для инициализации очереди
void init_queue_array(queue_array_s *queue)
{
    queue->start = queue->arr;
    queue->end = queue->arr;
    queue->cnt = 0;
}

// функция для перемещения указателя к следующему элементу кольцевой очереди 
void move_pos(queue_array_s *queue, int **p)
{
    // указатель уже в конце массива
    if (queue->arr + MAX_ARRAY_SIZE - 1 == *p)
        *p = queue->arr;
    else
        (*p)++;
}

// функция для добавления элемента в конец очереди
int push_queue_array(queue_array_s *queue, int elem)
{
    // очередь уже заполнена
    if (MAX_ARRAY_SIZE == queue->cnt)
        return QUEUE_OVERFLOW;

    *(queue->end) = elem;
    (queue->cnt)++;
    move_pos(queue, &(queue->end));

    return OK;
}

// функция для удаления элемента из начала очереди
int pop_queue_array(queue_array_s *queue, int *elem)
{
    // в очереди нет элементов
    if (0 == queue->cnt)
        return EMPTY_QUEUE;

    *elem = *(queue->start);
    (queue->cnt)--;
    move_pos(queue, &(queue->start));

    return OK;
}

// функция для печати текущего состояния очереди
void print_cur_state_q_arr(queue_array_s *queue)
{
    printf("В очереди %d элементов, максимально возможно %d\n", queue->cnt, MAX_ARRAY_SIZE);

    int *cur = queue->start;
    // печать всех элементов очереди
    for (int i = 0; i < queue->cnt; i++)
    {
        printf("Значение элемента: %d\n", *cur);
        move_pos(queue, &cur);
    }
}

// функция для вывода времени выполнения операций push, pop и памяти, выделяемой под очередь
void print_work_results_q_arr(int cnt)
{
    queue_array_s queue;
    clock_t start; // время до
    clock_t push_time = 0, pop_time = 0;
    int elem, rep = 1000;
    // инициализация очереди
    init_queue_array(&queue);
    
    for (int j = 0; j < rep; j++)
    {
        // время выполнения push
        start = clock();

        for (int i = 0; i < cnt; i++)
            push_queue_array(&queue, i);
        
        push_time += clock() - start;
        // время выполнения pop
        start = clock();

        for (int i = 0; i < cnt; i++)
            pop_queue_array(&queue, &elem);
    
        pop_time += clock() - start;
    }

    // память под очередь
    int mem = MAX_ARRAY_SIZE * sizeof(int) + 2 * sizeof(int*);

    printf("|%20s ", "array");
    printf("|%20d ", cnt);
    printf("|%27f ", (float)push_time / rep);
    printf("|%27f ", (float)pop_time / rep);
    printf("|%d\n\n", mem);
}

// функция для обработки очереди заявок двух типов
int service_queue_array(int t1_s, int t1_end, int t2_s, int t2_end, int t3_s, int t3_end, clock_t *time)
{
    clock_t start = clock();
    queue_array_s queue;
    init_queue_array(&queue);

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
    // среднее время прихода заявки 1го типа и обработки заявок 1го и 2 го типа
    double aver_t_in = ((double)t1_end + t1_s) / 2;
    double aver_t_proc1 = ((double)t2_end + t2_s) / 2, aver_t_proc2 = ((double)t3_end + t3_s) / 2;

    // пока не обработана 1000 заявок 1го типа
    while (cnt1_process < 1000)
    {
        if (t_in < t_out)
        {
            // поступление заявки 1го типа в конец очереди
            if (QUEUE_OVERFLOW == push_queue_array(&queue, 1))
                return QUEUE_OVERFLOW;

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
                    if (QUEUE_OVERFLOW == push_queue_array(&queue, 2))
                        return QUEUE_OVERFLOW;
                }
                else
                {
                    int *cur = queue.start;

                    for (int i = 0; i < 3; i++)
                        move_pos(&queue, &cur);

                    *(cur) = 2;

                    if (QUEUE_OVERFLOW == push_queue_array(&queue, 1))
                        return QUEUE_OVERFLOW;
                }
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
            pop_queue_array(&queue, &type);

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
    return OK;
}
