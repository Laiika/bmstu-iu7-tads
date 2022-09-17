#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#define NOT_FOUND -1

// структура для определения элемента хеш-таблицы
struct ht_elem
{
    int val; // значение элемента
    int busy; // занят ли элемент таблицы
};
typedef struct ht_elem ht_elem_s;

// структура для определения хеш-таблицы
struct hash_table
{
    int size; // максимальный размер таблицы
    int cur_size; // текущий размер таблицы
    ht_elem_s *arr; // массив с элементами таблицы
};
typedef struct hash_table hash_table_s;

hash_table_s *hash_table_init(int size);
void hash_table_resize(hash_table_s *ht, int new_size);
hash_table_s *hash_table_restruct(hash_table_s *ht, int (*hash_func)(int, int));
void hash_table_free(hash_table_s *ht);
int simple_hash_func(int num, int size);
int complex_hash_func(int num, int size);
int hash_table_insert(hash_table_s *ht, int val, int (*hash_func)(int, int));
int hash_table_find(hash_table_s *ht, int val, int (*hash_func)(int, int));
void hash_table_print(hash_table_s *ht);
void hash_table_print_insert_results();

#endif
