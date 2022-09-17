#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <stdio.h>

// коды возврата
#define OK 0
#define INPUT_ERROR -1
#define EXP_TOO_LARGE -2
#define EXP_TOO_MIN -3

// границы допустимых значений данных
#define MAX_MANTISSA_LEN 31
#define MAX_DIGITS_NUM 30
#define MIN_EXP -99999
#define MAX_EXP 99999

// структура для определения действительного числа в экспоненциальной форме
struct number
{
    char m_sign; // знак мантиссы
    char mantissa[MAX_MANTISSA_LEN + 1]; // мантисса числа
    long exp; // порядок числа
};

int read_number(struct number *num);
void normalize_number(struct number *num, short *mantissa, short *size);
short mult_numbers(short *nums1, short size1, short *nums2, short size2, short *result);
int calc_exp(long *exp, long exp1, long exp2, short *mantissa, short *start);
short round_mantissa(short *mantissa, short start);
void print_number(char sign, short *mantissa, short start, short end, long exp);

#endif
