#ifndef _STACK_LIST_H_
#define _STACK_LIST_H_

#include "return_codes.h"

#define MAX_LIST_SIZE 10000 // максимальный размер стека

// структура для определения элемента стека
struct node
{
    int val; // значение элемента
    struct node *prev; // указатель на предыдущий элемент
};
typedef struct node node_s;

// структура для определения элемента в списке адресов освобожденной памяти
struct free_node
{
    node_s *adr; // адрес освобожденной памяти
    struct free_node *prev; // указатель на предыдущий элемент
};
typedef struct free_node free_node_s;

// структура для определения стека в виде списка
struct stack_list
{
    node_s *ps; // указатель стека
    int cnt; // количество элементов в стеке
    free_node_s *free_nodes; // список адресов освобождаемой памяти
    int free_cnt; // количество адресов освобожденной памяти
};
typedef struct stack_list stack_list_s;

void init_stack_list(stack_list_s *stack);
int push_stack_list(stack_list_s *stack, int elem);
int pop_stack_list(stack_list_s *stack, int *elem);
void print_cur_state_st_list(stack_list_s *stack);
int print_work_results_st_list(int cnt);
int print_series_reverse_st_list(stack_list_s *stack);
void free_stack_list(stack_list_s *stack);

#endif
