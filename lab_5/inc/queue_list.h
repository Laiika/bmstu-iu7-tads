#ifndef _QUEUE_LIST_H_
#define _QUEUE_LIST_H_

#include <time.h>
#include "return_codes.h"

// структура для определения элемента списка
struct node
{
    int val; // значение элемента
    struct node *next; // указатель на следующий элемент
};
typedef struct node node_s;

// структура для определения элемента в списке адресов освобожденной памяти
struct free_node
{
    node_s *adr; // адрес освобожденной памяти
    struct free_node *next; // указатель на следующий элемент
};
typedef struct free_node free_node_s;

// структура для определения очереди в виде списка 
struct queue_list
{
    node_s *start; // указатель на начало очереди
    node_s *end; // указатель на конец очереди
    int cnt; // количество элементов в очереди
    free_node_s *free_nodes; // указатель на начало списка адресов освобождаемой памяти
    free_node_s *free_nodes_end; // указатель на конец списка адресов освобождаемой памяти
    int free_cnt; // количество адресов освобожденной памяти
};
typedef struct queue_list queue_list_s;

void init_queue_list(queue_list_s *queue);
void free_queue_list(queue_list_s *queue);
int push_queue_list(queue_list_s *queue, int elem);
int pop_queue_list(queue_list_s *queue, int *elem);
void print_cur_state_q_list(queue_list_s *queue);
int print_work_results_q_list(int cnt);
int service_queue_list(int t1_s, int t1_end, int t2_s, int t2_end, int t3_s, int t3_end, clock_t *time, int *max_cnt);

#endif
