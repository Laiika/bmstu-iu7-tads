#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/hash_table.h"

// функция для инициализации хеш-таблицы
hash_table_s *hash_table_init(int size)
{
    hash_table_s *ht = malloc(sizeof(hash_table_s));

    if (!ht)
        return ht;

    ht->arr = calloc(size, sizeof(ht_elem_s));

    if (!(ht->arr))
    {
        free(ht);
        return NULL;
    }

    ht->size = size;
    ht->cur_size = 0;
    return ht;
}

// функция для изменения размера хеш-таблицы
void hash_table_resize(hash_table_s *ht, int new_size)
{
    ht_elem_s *arr = realloc(ht->arr, sizeof(ht_elem_s) * new_size);

    if (arr)
    {
        ht->arr = arr;

        for (int i = ht->size; i < new_size; i++)
            ht->arr[i].busy = 0;

        ht->size = new_size;
    }
}

// функция для реструктуризации хеш-таблицы
hash_table_s *hash_table_restruct(hash_table_s *ht, int (*hash_func)(int, int))
{
    hash_table_s *new_ht = hash_table_init(ht->size);

    if (new_ht)
    {
        for (int i = 0; i < ht->size; i++)
            if (ht->arr[i].busy)
                if (NOT_FOUND == hash_table_insert(new_ht, ht->arr[i].val, hash_func))
                {
                    hash_table_free(new_ht);
                    return NULL;
                }

        hash_table_free(ht);
    }

    return new_ht;
}

// функция для освобождения памяти из под хеш-таблицы
void hash_table_free(hash_table_s *ht)
{
    if (!ht)
        return;

    free(ht->arr);
    free(ht);
}

// простая хеш-функция
int simple_hash_func(int num, int size)
{
    return num % size;
}

// сложная хеш-функция
int complex_hash_func(int num, int size)
{
    double a = (sqrt(5) - 1) / 2;

    return floor(size * fmod(abs(num) * a, 1));
}

// функция для добавления элемента в хеш-таблицу
int hash_table_insert(hash_table_s *ht, int val, int (*hash_func)(int, int))
{
    int cmps = 1, ind = hash_func(val, ht->size), i = ind;
    // поиск в таблице пустого места для нового элемента или такого же числа
    while (ind < ht->size && ht->arr[ind].busy && ht->arr[ind].val != val)
    {
        ind++;
        cmps++;
    }
    // дошли до конца массива
    if (ind >= ht->size)
    {
        ind = 0;
        // поиск в таблице пустого места для нового элемента или такого же числа
        while (ind < i && ht->arr[ind].busy && ht->arr[ind].val != val)
        {
            ind++;
            cmps++;
        }
        // прошли весь массив
        if (ind >= i)
            return NOT_FOUND;
    }
    // нашлось пустое место
    if (0 == ht->arr[ind].busy)
    {
        ht->arr[ind].val = val;
        ht->arr[ind].busy = 1;
        ht->cur_size++;
    }
    
    return cmps;
}

// функция для удаления числа из хеш-таблице
int hash_table_delete(hash_table_s *ht, int val, int (*hash_func)(int, int))
{
    int ind = hash_func(val, ht->size), cmps = 1, i = ind;
    // поиск числа в хеш-таблице
    for (; ind < ht->size; ind++)
    {
        if (ht->arr[ind].busy && ht->arr[ind].val == val)
        {
            ht->arr[ind].busy = 0;
            break;
        }

        cmps++;
    }
    // дошли до конца массива
    if (ind >= ht->size)
    {
        ind = 0;
        // поиск в таблице
        for (; ind < i; ind++)
        {
            if (ht->arr[ind].busy && ht->arr[ind].val == val)
            {
                ht->arr[ind].busy = 0;
                break;
            }

            cmps++;
        }
        // прошли весь массив
        if (ind >= i)
            return NOT_FOUND;
    }

    return cmps;
}

// функция для поиска числа в хеш-таблице
int hash_table_find(hash_table_s *ht, int val, int (*hash_func)(int, int))
{
    int ind = hash_func(val, ht->size), cmps = 1, i = ind;
    // поиск числа в хеш-таблице
    for (; ind < ht->size; ind++)
    {
        if (ht->arr[ind].busy && ht->arr[ind].val == val)
            break;

        cmps++;
    }
    // дошли до конца массива
    if (ind >= ht->size)
    {
        ind = 0;
        // поиск в таблице
        for (; ind < i; ind++)
        {
            if (ht->arr[ind].busy && ht->arr[ind].val == val)
                break;

            cmps++;
        }
        // прошли весь массив
        if (ind >= i)
            return NOT_FOUND;
    }

    return cmps;
}

// функция для печати хеш-таблицы
void hash_table_print(hash_table_s *ht)
{
    printf("|    index   |   value    |\n");

    for (int i = 0; i < ht->size; i++)
    {
        if (ht->arr[i].busy)
            printf("\n|%10d  |%10d  |\n", i, ht->arr[i].val);
    }
}

// функция для вывода времени добавления в хеш-таблицу, памяти и количества сравнений
void hash_table_print_insert_results()
{
    hash_table_s *ht;
    clock_t start; // время до
    clock_t time = 0;
    int cmps = 0, rep = 1000, mem;
    
    for (int j = 0; j < rep; j++)
    {
        ht = hash_table_init(1000);

        if (ht)
        {
            // время выполнения
            start = clock();

            for (int i = 0; i < 500; i++)
                cmps += hash_table_insert(ht, i, complex_hash_func);
        
            time += clock() - start;
            // память под хеш-таблицу
            mem = ht->size * sizeof(ht_elem_s);
            hash_table_free(ht);
        }
    }

    printf("|%20s ", "hash_table");
    printf("|%27f ", (float)time / rep);
    printf("|%27d ", mem);
    printf("|%f\n\n", (float)cmps / (rep * 500));
}
