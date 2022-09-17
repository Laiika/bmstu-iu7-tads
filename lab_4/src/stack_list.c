#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/stack_list.h"

// функция для инициализации стека
void init_stack_list(stack_list_s *stack)
{
    stack->ps = NULL;
    stack->cnt = 0;
    stack->free_cnt = 0;
    stack->free_nodes = NULL;
}

// функция для добавления элемента на вершину стека
int push_stack_list(stack_list_s *stack, int elem)
{
    // стек заполнен
    if (MAX_LIST_SIZE == stack->cnt)
        return STACK_OVERFLOW;
    // создание нового элемента
    node_s *new_node = NULL;
    new_node = calloc(1, sizeof(node_s));

    if (!new_node)
        return MEMORY_ERROR;
    
    new_node->val = elem;
    (stack->cnt)++;

    // стек был пуст
    if (NULL == stack->ps)
        new_node->prev = NULL;
    else
        new_node->prev = stack->ps;

    stack->ps = new_node;
    return OK;
}

// функция для извлечения элемента с вершины стека
int pop_stack_list(stack_list_s *stack, int *elem)
{
    // стек пустой
    if (NULL == stack->ps)
        return EMPTY_STACK;

    *elem = stack->ps->val;

    // создание нового элемента списка адресов
    free_node_s *new_free_node = NULL;
    new_free_node = calloc(1, sizeof(free_node_s));

    if (!new_free_node)
        return MEMORY_ERROR;

    new_free_node->adr = stack->ps;
    (stack->free_cnt)++;

    // список адресов был пуст
    if (NULL == stack->free_nodes)
        new_free_node->prev = NULL;
    else
        new_free_node->prev = stack->free_nodes;

    stack->free_nodes = new_free_node;

    // перемещение вершины на один элемент вниз
    node_s *new_node = stack->ps->prev;
    free(stack->ps);
    stack->ps = new_node;
    (stack->cnt)--;

    return OK;
}

// функция для печати текущего состояния стека
void print_cur_state_st_list(stack_list_s *stack)
{
    printf("В стеке %d элементов, максимально возможно %d\n", stack->cnt, MAX_LIST_SIZE);
    // в стеке есть элементы
    if (stack->cnt)
    {
        node_s *cur = stack->ps;

        printf("Начиная с вершины:\n");
        // просмотр всех элементов стека, начиная с вершины
        while (NULL != cur)
        {
            printf("Адрес элемента: %p, значение: %d\n", (void*)cur, cur->val);
            cur = cur->prev;
        }
    }

    printf("Освобождено %d областей памяти\n", stack->free_cnt);
    // вывод адресов освобожденной памяти
    free_node_s *cur = stack->free_nodes;

    while (NULL != cur)
    {
        printf("Адрес освобожденной области памяти: %p\n", (void*)cur->adr);
        cur = cur->prev;
    }
}

// функция для вывода времени выполнения операций push, pop и памяти, выделяемой под стек
int print_work_results_st_list(int cnt)
{
    stack_list_s stack;
    clock_t start; // время до
    int push_time = 0, pop_time = 0, elem, rep = 1000, mem;

    for (int j = 0; j < rep; j++)
    {
        // инициализация стека
        init_stack_list(&stack);

        // время выполнения push
        start = clock();

        for (int i = 0; i < cnt; i++)
        {
            if (MEMORY_ERROR == push_stack_list(&stack, i))
            {
                free_stack_list(&stack);
                return MEMORY_ERROR;
            }
        }

        push_time += clock() - start;
        // время выполнения pop
        start = clock();

        for (int i = 0; i < cnt; i++)
        {
            if (MEMORY_ERROR == pop_stack_list(&stack, &elem))
            {
                free_stack_list(&stack);
                return MEMORY_ERROR;
            }
        }

        pop_time += clock() - start;

        // память под стек
        mem = sizeof(node_s*) + cnt * sizeof(node_s);
        free_stack_list(&stack);
    }

    printf("|%20s ", "list");
    printf("|%20d ", cnt);
    printf("|%27f ", (float)push_time / rep);
    printf("|%27f ", (float)pop_time / rep);
    printf("|%d\n\n", mem);
    return OK;
}

// функция для печати серии чисел
int print_series_st_list(stack_list_s *ser, int cnt)
{
    int rc, elem;
    // в серии хотя бы 2 элемента
    if (cnt > 1)
    {
        while (OK == (rc = pop_stack_list(ser, &elem)))
            printf("%d ", elem);

        printf("\n");
    }
    else
        rc = pop_stack_list(ser, &elem);
    // ошибок нет, просто опустошили стек серии
    if (MEMORY_ERROR != rc)
        rc = OK;

    return rc;
}

// функция для печати убывающих серий чисел из стека в обратном порядке
int print_series_reverse_st_list(stack_list_s *stack)
{
    int elem, prev_elem, cnt = 1, rc = OK, rc2 = OK, rc3 = OK;
    // извлечение элемента с вершины стека
    if (OK != (rc = pop_stack_list(stack, &elem)))
        return rc;

    stack_list_s ser, copy;
    // стек под серию чисел
    init_stack_list(&ser);
    // стек под перевернутую копию исходного
    init_stack_list(&copy);

    if (MEMORY_ERROR == push_stack_list(&ser, elem) || MEMORY_ERROR == push_stack_list(&copy, elem))
    {
        push_stack_list(stack, elem);
        free_stack_list(&ser);
        return MEMORY_ERROR;
    }

    // пока исходный стек не опустеет
    while (OK == rc && OK == (rc = pop_stack_list(stack, &prev_elem)))
    {
        if (MEMORY_ERROR == (rc = push_stack_list(&copy, prev_elem)))
            rc3 = push_stack_list(stack, prev_elem);
        else if (prev_elem > elem) // сейчас идет убывающая серия
        {
            rc = push_stack_list(&ser, prev_elem);
            cnt++;
        }
        else if (OK == (rc = print_series_st_list(&ser, cnt)))
        {
            // начинается проверка новой серии
            free_stack_list(&ser);
            init_stack_list(&ser);
            rc = push_stack_list(&ser, prev_elem);
            cnt = 1;
        }

        elem = prev_elem;
    }
    // ошибок нет, просто опустошили стек
    if (MEMORY_ERROR != rc)
        rc = OK;

    if (OK == rc)
        rc = print_series_st_list(&ser, cnt);

    // восстановление исходного стека
    while (OK == rc3 && OK == (rc2 = pop_stack_list(&copy, &elem)))
        rc3 = push_stack_list(stack, elem);
    // ошибок нет, просто опустошили стек копии
    if (MEMORY_ERROR != rc2)
        rc2 = OK;
            
    free_stack_list(&copy);
    free_stack_list(&ser);
    return (OK == rc && OK == rc2 && OK == rc3);
}

void free_stack_list(stack_list_s *stack)
{
    node_s *cur = stack->ps;
    // освобождение памяти из под стека
    while (NULL != cur)
    {
        stack->ps = cur->prev;
        free(cur);
        cur = stack->ps;
    }

    stack->ps = NULL;

    free_node_s *node = stack->free_nodes;
    // освобождение памяти из под списка адресов
    while (NULL != node)
    {
        stack->free_nodes = node->prev;
        free(node);
        node = stack->free_nodes;
    }

    stack->free_nodes = NULL;
}
