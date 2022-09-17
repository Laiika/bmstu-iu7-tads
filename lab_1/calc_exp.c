#include "funcs.h"

// функция для вычисления экспоненты результата
int calc_exp(long *exp, long exp1, long exp2, short *mantissa, short *start)
{
    if (MAX_DIGITS_NUM * 2 == *start && 0 == mantissa[*start]) // мантисса равна 0
    {
        *exp = 0;
        return OK;
    }

    *exp = exp1 + exp2;

    // пока в мантиссе идут незначащие нули
    while (0 == mantissa[*start] && *start < (MAX_DIGITS_NUM * 2 + 1))
    {
        (*start)++;
        (*exp)--;
    }

    if (MAX_EXP < *exp)
        return EXP_TOO_LARGE;

    if (MIN_EXP > *exp)
        return EXP_TOO_MIN;

    return OK;
}
