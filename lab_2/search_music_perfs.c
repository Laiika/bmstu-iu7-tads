#include "perf.h"
#include "perfs.h"

// функция для печати записи о музыкальном спектакле в консоль
void print_music_console(performance_s perf)
{
    printf("|%-15s ", perf.theatre_name);
    printf("|%-15s ", perf.performance_name);
    printf("|%-15s ", perf.director);
    printf("|%-6d - %6d ", perf.price_range[0], perf.price_range[1]);
    printf("|%-15s ", "musical");
    printf("|%-15s ", perf.type.cont.music.composer);
    printf("|%-15s ", perf.type.cont.music.country);
    printf("|%-15d ", perf.type.cont.music.min_age);
    printf("|%-d\n", perf.type.cont.music.duration);
}

// функция для вывода всех музыкальных спектаклей для детей указанного возраста с продолжительностью меньше указанной
int search(performance_s *arr, const int size)
{
    short age; // минимальный возраст
    short duration; // продолжительность

    printf("Введите возраст и продолжительность: ");
    // чтение возраста
    if (1 != scanf("%hd", &age) || age < 0 || age > 18)
        return READ_ERROR;
    // чтение продолжительности
    if (1 != scanf("%hd", &duration) || duration < 0)
        return READ_ERROR;
    // вывод заголовков таблицы
    printf("|%-15s ", "theatre");
    printf("|%-15s ", "performance");
    printf("|%-15s ", "director");
    printf("|%-15s ", "price range");
    printf("|%-15s ", "type");
    printf("|%-15s ", "composer");
    printf("|%-15s ", "country");
    printf("|%-15s ", "min age");
    printf("|duration\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // поиск по массиву
    for (int i = 0; i < size; i++)
        if (MUSIC == arr[i].type.num && arr[i].type.cont.music.min_age <= age && arr[i].type.cont.music.duration < duration)
            print_music_console(arr[i]);

    return OK;
}
