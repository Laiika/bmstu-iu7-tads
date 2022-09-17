#include <string.h>
#include "perf.h"

// функция для чтения названия
int read_name(FILE *file, char *const str, const int max_size, const int size)
{
    if (!fgets(str, size, file)) 
        return READ_ERROR;
        
    char ch;
    int len = strlen(str);
    // длина названия максимальна и дальше не символ переноса
    if (max_size == len && (1 != fscanf(file, "%c", &ch) || '\n' != ch))
        return READ_ERROR;

    if ('\n' == str[len - 1])
        str[len - 1] = '\0';

    return OK;
}

// функция для чтения информации о детском спектакле
int read_child_type(FILE *file, child_perf_s *child)
{
    // читаем возраст
    if (1 != fscanf(file, "%hd", &(child->age)) || child->age < 0 || child->age > 18)
        return READ_ERROR;

    int type;
    // читаем тип детского спектакля
    if (1 != fscanf(file, "%d", &type) || (FAIRY_TALE != type && CHILD_PLAY != type))
        return READ_ERROR;

    child->type = type;

    return OK;
}

// функция для чтения информации о взрослом спектакле
int read_adult_type(FILE *file, adult_perf_e *adult)
{
    int type;
    // читаем тип взрослого спектакля
    if (1 != fscanf(file, "%d", &type) || (ADULT_PLAY != type && DRAMA != type && COMEDY != type))
        return READ_ERROR;

    *adult = type;

    return OK;
}

// функция для чтения информации о музыкальном спектакле
int read_music_type(FILE *file, musical_perf_s *music)
{
    char ch;
    
    if (1 != fscanf(file, "%c", &ch) || ('\n' != ch))
        return READ_ERROR;
    // читаем имя композитора
    if (OK != read_name(file, music->composer, COMPOSER_NAME_LEN, sizeof(music->composer)))
        return READ_ERROR;
    // читаем название страны
    if (OK != read_name(file, music->country, COUNTRY_NAME_LEN, sizeof(music->country)))
        return READ_ERROR;
    // читаем минимальный возраст
    if (1 != fscanf(file, "%hd", &(music->min_age)) || music->min_age < 0)
        return READ_ERROR;
    // читаем продолжительность спектакля
    if (1 != fscanf(file, "%hd", &(music->duration)) || music->duration <= 0)
        return READ_ERROR;

    return OK;
}

// функция для чтения типа спектакля
int read_perf_type(FILE *file, performance_s *cur)
{
    int type;
    // читаем тип спектакля (соответствующий номер)
    if (1 != fscanf(file, "%d", &type) || (CHILD != type && ADULT != type && MUSIC != type))
        return READ_ERROR;

    (cur->type).num = type;

    if (CHILD == (cur->type).num) // тип детский
    {
        if (OK != read_child_type(file, &((cur->type).cont.child)))
            return READ_ERROR;
    }
    else if (ADULT == (cur->type).num) // тип взрослый
    {
        if (OK != read_adult_type(file, &((cur->type).cont.adult)))
            return READ_ERROR;
    }
    else // тип музыкальный
        if (OK != read_music_type(file, &((cur->type).cont.music)))
            return READ_ERROR;

    return OK;
}

// функция для считывания спектакля из файла
int read_perf_file(FILE *file, performance_s *cur)
{
    // читаем название театра
    if (OK != read_name(file, cur->theatre_name, THEATRE_NAME_LEN, sizeof(cur->theatre_name)))
        return READ_ERROR;
    // читаем название спектякля
    if (OK != read_name(file, cur->performance_name, PERF_NAME_LEN, sizeof(cur->performance_name)))
        return READ_ERROR;
    // читаем имя режиссера
    if (OK != read_name(file, cur->director, DIR_NAME_LEN, sizeof(cur->director)))
        return READ_ERROR;
    // читаем минимальную цену билета
    if (1 != fscanf(file, "%hd", &(cur->price_range[0])) || cur->price_range[0] < 0)
        return READ_ERROR;
    // читаем максимальную цену билета
    if (1 != fscanf(file, "%hd", &(cur->price_range[1])) || cur->price_range[1] < 0 || cur->price_range[1] < cur->price_range[0])
        return READ_ERROR;
    // читаем тип спектакля
    if (OK != read_perf_type(file, cur))
        return READ_ERROR;

    char ch;
    // после записи проверяем символ переноса строки
    if (1 != fscanf(file, "%c", &ch))
    {
        if (feof(file))
            return EOF;
        
        return READ_ERROR;
    }
    else if ('\n' != ch)
        return READ_ERROR;

    return OK;
}

// функция для считывания спектакля из консоли
int read_perf_console(performance_s *cur)
{
    printf("Введите название театра: ");
    // читаем название театра
    if (OK != read_name(stdin, cur->theatre_name, THEATRE_NAME_LEN, sizeof(cur->theatre_name)))
        return READ_ERROR;
    
    printf("Введите название спектакля: ");
    // читаем название спектякля
    if (OK != read_name(stdin, cur->performance_name, PERF_NAME_LEN, sizeof(cur->performance_name)))
        return READ_ERROR;

    printf("Введите имя режиссера: ");
    // читаем имя режиссера
    if (OK != read_name(stdin, cur->director, DIR_NAME_LEN, sizeof(cur->director)))
        return READ_ERROR;
    
    printf("Введите минимальную цену билета: ");
    // читаем минимальную цену билета
    if (1 != fscanf(stdin, "%hd", &(cur->price_range[0])) || cur->price_range[0] < 0)
        return READ_ERROR;

    printf("Введите максимальную цену билета: ");
    // читаем максимальную цену билета
    if (1 != fscanf(stdin, "%hd", &(cur->price_range[1])) || cur->price_range[1] < 0 || cur->price_range[1] < cur->price_range[0])
        return READ_ERROR;

    printf("Для детского типа спектакля вводится возраст и тип: 1 - сказка, 2 - пьеса\n");
    printf("Для взрослого типа спектакля вводится тип: 1 - пьеса, 2 - драма, 3 - комедия\n");
    printf("Для музыкального типа спектакля вводится композитор, страна, минимальный возраст, продолжительность\n");
    printf("Каждый пункт вводится в отдельной строке\n");
    printf("Введите тип спектакля: 1 - детский, 2 - взрослый, 3 - музыкальный: ");
    // читаем тип спектакля
    if (OK != read_perf_type(stdin, cur))
        return READ_ERROR;

    return OK;
}
