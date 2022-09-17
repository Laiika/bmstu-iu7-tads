#ifndef _STACK_ARRAY_H_
#define _STACK_ARRAY_H_

#include "return_codes.h"

#define MAX_ARRAY_SIZE 10000 // максимальный размер массива

// структура для определения стека в виде массива
struct stack_array
{
    int arr[MAX_ARRAY_SIZE]; // массив
    int *ps; // указатель стека
};
typedef struct stack_array stack_array_s;

void init_stack_array(stack_array_s *stack);
int push_stack_array(stack_array_s *stack, int elem);
int pop_stack_array(stack_array_s *stack, int *elem);
void print_cur_state_st_arr(stack_array_s *stack);
void print_work_results_st_arr(int cnt);
int print_series_reverse_st_arr(stack_array_s *stack);

#endif
