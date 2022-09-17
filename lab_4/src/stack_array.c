#include <stdio.h>
#include <time.h>
#include "../inc/stack_array.h"

// функция для инициализации стека
void init_stack_array(stack_array_s *stack)
{
    stack->ps = NULL;
}

// функция для добавления элемента на вершину стека
int push_stack_array(stack_array_s *stack, int elem)
{
    // стек заполнен
    if (stack->arr + MAX_ARRAY_SIZE - 1 == stack->ps)
        return STACK_OVERFLOW;
    // стек пустой
    if (NULL == stack->ps)
        stack->ps = stack->arr; 
    else
        (stack->ps)++;

    *(stack->ps) = elem;
    return OK;
}

// функция для извлечения элемента с вершины стека
int pop_stack_array(stack_array_s *stack, int *elem)
{
    // стек пустой
    if (NULL == stack->ps)
        return EMPTY_STACK;

    *elem = *(stack->ps);
    // в стеке был один элемент
    if (stack->ps == stack->arr)
        (stack->ps) = NULL;
    else
        (stack->ps)--;

    return OK;
}

// функция для печати текущего состояния стека
void print_cur_state_st_arr(stack_array_s *stack)
{
    int elems;
    // стек пустой
    if (NULL == stack->ps)
        elems = 0;
    else
        elems = stack->ps - stack->arr + 1;

    printf("В стеке %d элементов, максимально возможно %d\n", elems, MAX_ARRAY_SIZE);
    // в стеке есть элементы
    if (elems)
    {
        int *cur = stack->ps;

        printf("Начиная с вершины:\n");
        // просмотр всех элементов стека, начиная с вершины
        while (cur >= stack->arr)
        {
            printf("Адрес элемента: %p, значение: %d\n", (void*)cur, *cur);
            cur--;
        }
    }
}

// функция для вывода времени выполнения операций push, pop и памяти, выделяемой под стек
void print_work_results_st_arr(int cnt)
{
    stack_array_s stack;
    clock_t start; // время до
    int push_time = 0, pop_time = 0, elem, rep = 1000;
    // инициализация стека
    init_stack_array(&stack);
    
    for (int j = 0; j < rep; j++)
    {
        // время выполнения push
        start = clock();

        for (int i = 0; i < cnt; i++)
            push_stack_array(&stack, i);
        
        push_time += clock() - start;
        // время выполнения pop
        start = clock();

        for (int i = 0; i < cnt; i++)
            pop_stack_array(&stack, &elem);
    
        pop_time += clock() - start;
    }

    // память под стек
    int mem = MAX_ARRAY_SIZE * sizeof(int) + sizeof(int*);

    printf("|%20s ", "array");
    printf("|%20d ", cnt);
    printf("|%27f ", (float)push_time / rep);
    printf("|%27f ", (float)pop_time / rep);
    printf("|%d\n\n", mem);
}

// функция для печати серии чисел
void print_series_st_arr(stack_array_s *ser, int cnt)
{
    int elem;
    // в серии хотя бы 2 элемента
    if (cnt > 1)
    {
        while (OK == pop_stack_array(ser, &elem))
            printf("%d ", elem);

        printf("\n");
    }
    else
        pop_stack_array(ser, &elem);
}

// функция для печати убывающих серий чисел из стека в обратном порядке
int print_series_reverse_st_arr(stack_array_s *stack)
{
    int elem, prev_elem, cnt = 1;
    // извлечение элемента с вершины стека
    if (EMPTY_STACK == pop_stack_array(stack, &elem))
        return EMPTY_STACK;

    stack_array_s ser, copy;
    // стек под серию чисел
    init_stack_array(&ser);
    push_stack_array(&ser, elem);
    // стек - перевернутая копия исходного
    init_stack_array(&copy);
    push_stack_array(&copy, elem);

    // пока исходный стек не опустеет
    while (OK == pop_stack_array(stack, &prev_elem))
    {
        push_stack_array(&copy, prev_elem);
        // сейчас идет убывающая серия
        if (prev_elem > elem)
        {
            push_stack_array(&ser, prev_elem);
            cnt++;
        }
        else
        {
            print_series_st_arr(&ser, cnt);
            // начинается проверка новой серии
            push_stack_array(&ser, prev_elem);
            cnt = 1;
        }

        elem = prev_elem;
    }

    print_series_st_arr(&ser, cnt);
    // восстановление исходного стека
    while (OK == pop_stack_array(&copy, &elem))
        push_stack_array(stack, elem);

    return OK;
}
