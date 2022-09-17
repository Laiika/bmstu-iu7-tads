#include "perf.h"
#include "perfs.h"
#include "key.h"

// функция для печати записи о спектакле в общую таблицу
void print_perf(performance_s perf)
{
    printf("|%-15s ", perf.theatre_name);
    printf("|%-15s ", perf.performance_name);
    printf("|%-15s ", perf.director);
    printf("|%-6d - %6d ", perf.price_range[0], perf.price_range[1]);

    if (CHILD == perf.type.num)
    {
        printf("|%-15s ", "child");
        printf("|%-15d ", perf.type.cont.child.age);

        if (FAIRY_TALE == perf.type.cont.child.type)
            printf("|%-15s ", "fairy tale");
        else
            printf("|%-15s ", "play");

        printf("|%-15s ", "-");
        printf("|%-15s ", "-");
        printf("|%-15s ", "-");
        printf("|%-s\n", "-");
    }
    else if (ADULT == perf.type.num)
    {
        printf("|%-15s ", "adult");
        printf("|%-15s ", "-");

        if (ADULT_PLAY == perf.type.cont.adult)
            printf("|%-15s ", "play");
        else if (DRAMA == perf.type.cont.adult)
            printf("|%-15s ", "drama");
        else
            printf("|%-15s ", "comedy");

        printf("|%-15s ", "-");
        printf("|%-15s ", "-");
        printf("|%-15s ", "-");
        printf("|%-s\n", "-");
    }
    else
    {
        printf("|%-15s ", "musical");
        printf("|%-15s ", "-");
        printf("|%-15s ", "-");
        printf("|%-15s ", perf.type.cont.music.composer);
        printf("|%-15s ", perf.type.cont.music.country);
        printf("|%-15d ", perf.type.cont.music.min_age);
        printf("|%-d\n", perf.type.cont.music.duration);
    }
}

// функция для печати записей из массива в консоль в виде таблицы
void print_perfs_table(performance_s *const arr, int size)
{
    // вывод заголовков таблицы
    printf("|%-15s ", "theatre");
    printf("|%-15s ", "performance");
    printf("|%-15s ", "director");
    printf("|%-15s ", "price range");
    printf("|%-15s ", "type");
    printf("|%-15s ", "child age");
    printf("|%-15s", "child/adult type");;
    printf("|%-15s ", "composer");
    printf("|%-15s ", "country");
    printf("|%-15s ", "musical min age");
    printf("|duration\n");
    printf("------------------------------------------------------------------------------------------------");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < size; i++)
        print_perf(arr[i]);
}

// функция для печати записей из массива спктаклей в консоль в виде таблицы по массиву ключей
void print_perfs_table_keys(performance_s *const arr, perf_min_price_s *const keys, int size)
{
    // вывод заголовков таблицы
    printf("|%-15s ", "theatre");
    printf("|%-15s ", "performance");
    printf("|%-15s ", "director");
    printf("|%-15s ", "price range");
    printf("|%-15s ", "type");
    printf("|%-15s ", "child age");
    printf("|%-15s", "child/adult type");;
    printf("|%-15s ", "composer");
    printf("|%-15s ", "country");
    printf("|%-15s ", "musical min age");
    printf("|duration\n");
    printf("------------------------------------------------------------------------------------------------");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < size; i++)
        print_perf(arr[keys[i].index]);
}
