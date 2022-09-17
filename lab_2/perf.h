#ifndef _PERF_H_
#define _PERF_H_

#include <stdio.h>
#include "errors.h"

// максимальные размеры строк
#define THEATRE_NAME_LEN 15
#define PERF_NAME_LEN 15
#define DIR_NAME_LEN 15
#define COMPOSER_NAME_LEN 15
#define COUNTRY_NAME_LEN 15

// коды возврата
#define OK 0

// перечисление типов спектакля
typedef enum {CHILD = 1, ADULT, MUSIC} perf_type_num_e;
// перечисление для определения типа детского спектакля
typedef enum {FAIRY_TALE = 1, CHILD_PLAY} child_perf_type_e;
// перечисление для определения типа взрослого спектакля
typedef enum {ADULT_PLAY = 1, DRAMA, COMEDY} adult_perf_e;

// структура для определения детского типа спектакля
struct child_perf
{
    short age; // возраст
    child_perf_type_e type; // тип
};
typedef struct child_perf child_perf_s;

// структура для определения музыкального типа спектакля
struct musical_perf
{
    char composer[COMPOSER_NAME_LEN + 1]; // композитор
    char country[COUNTRY_NAME_LEN + 1]; // страна
    short min_age; // минимальный возраст
    short duration; // продолжительность
};
typedef struct musical_perf musical_perf_s;

// объединение для определения содержимого типа спектакля
union type_content
{
    child_perf_s child; // детский
    adult_perf_e adult; // взрослый
    musical_perf_s music; // музыкальный
};
typedef union type_content type_content_u;

// структура для определения типа спектакля
struct perf_type
{
    perf_type_num_e num; // номер типа
    type_content_u cont; // содержимое типа
};
typedef struct perf_type perf_type_s;

// структура для определения одного спектакля в конкретном театре
struct performance
{
    char theatre_name[THEATRE_NAME_LEN + 1]; // театр
    char performance_name[PERF_NAME_LEN + 1]; // название спектакля
    char director[DIR_NAME_LEN + 1]; // режиссер
    short price_range[2]; // диапазон цены билета
    perf_type_s type; // тип спектакля
};
typedef struct performance performance_s;

int read_perf_file(FILE *file, performance_s *cur);
int read_perf_console(performance_s *cur);

#endif
