#include "funcs.h"
#include <string.h>

// функция для обработки части мантиссы до запятой
void check_before_point(struct number *num, short *mantissa, short *size, int *i, int *flag)
{
    int len = strlen(num->mantissa);

    // пока в мантиссе не встретилась точка
    for (*i = 0; *i < len && '.' != num->mantissa[*i]; (*i)++)
    {
        // встретился значащий разряд
        if ('0' != num->mantissa[*i])
            (*flag)++;

        // переводим в массив чисел
        if (0 != *flag)
        {
            mantissa[*size] = num->mantissa[*i] - '0';
            (*size)++;
            num->exp++;
        }
    }
}

// функция для обработки части мантиссы после запятой
void check_after_point(struct number *num, short *mantissa, short *size, int i, int flag)
{
    int len = strlen(num->mantissa);

    // переводим в массив чисел оставшуюся после точки часть
    for (int j = i; j < len; j++)
    {
        if ('0' != num->mantissa[j])
            flag++;

        if (0 == flag)  // пока были одни нули
            num->exp--;
        else
        {
            mantissa[*size] = num->mantissa[j] - '0';
            (*size)++;
        }
    }
}

// функция для нормализации действительного числа
void normalize_number(struct number *num, short *mantissa, short *size)
{
    int i, flag = 0;
    *size = 0;

    check_before_point(num, mantissa, size, &i, &flag);
    i++;
    check_after_point(num, mantissa, size, i, flag);

    if (0 == *size)  // мантисса равна 0
    {
        mantissa[*size] = 0;
        (*size)++;
    }
}
