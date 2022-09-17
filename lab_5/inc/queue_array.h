#ifndef _QUEUE_ARRAY_H_
#define _QUEUE_ARRAY_H_

#include <time.h>
#include "return_codes.h"

#define MAX_ARRAY_SIZE 10000 // максимальный размер массива

// структура для определения очереди в виде массива
struct queue_array
{
    int arr[MAX_ARRAY_SIZE]; // массив
    int *start; // указатель на начало очереди
    int *end; // указатель на конец очереди (за последний элемент)
    int cnt; // количество элементов в очереди
};
typedef struct queue_array queue_array_s;

void init_queue_array(queue_array_s *queue);
int push_queue_array(queue_array_s *queue, int elem);
int pop_queue_array(queue_array_s *queue, int *elem);
void print_cur_state_q_arr(queue_array_s *queue);
void print_work_results_q_arr(int cnt);
int service_queue_array(int t1_s, int t1_end, int t2_s, int t2_end, int t3_s, int t3_end, clock_t *time);

#endif
