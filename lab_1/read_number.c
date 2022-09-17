#include "funcs.h"

// функция для определения знака мантиссы
int read_mantissa_sign(struct number *num, int *const point, int *const m_len)
{
    char ch;

    if (1 != scanf("%c", &ch))  
        return INPUT_ERROR;

    if ('-' == ch || '+' == ch)
        num->m_sign = ch;
    else if (('0' <= ch && '9' >= ch) || '.' == ch)
    {
        num->m_sign = '+';  // если знак не указан, то по умолчанию +
        num->mantissa[*m_len] = ch;
        (*m_len)++;

        if ('.' == ch)
            (*point)++;
    }
    else
        return INPUT_ERROR;

    return OK;
}

// функция для чтения цифр мантиссы
int read_mantissa(struct number *num, int *const point, int *const m_len, char *ch)
{
    if (1 != scanf("%c", ch))  
        return INPUT_ERROR;

    // читаем посимвольно пока мантисса не кончилась и не достигнут максимум возможных символов
    while ('\n' != (*ch) && ' ' != (*ch) && (*m_len) < MAX_MANTISSA_LEN) 
    {
        if (('0' <= *ch && '9' >= *ch) || (0 == (*point) && '.' == (*ch)))
        {
            num->mantissa[*m_len] = *ch;
            (*m_len)++;

            if ('.' == (*ch))
                (*point)++;

            if (1 != scanf("%c", ch))  
                return INPUT_ERROR;
        }
        else
            return INPUT_ERROR;
    }

    return OK;
}

// функция для чтения порядка числа
int read_exp(struct number *num, char ch)
{
    if ('\n' == ch)
        num->exp = 0; // число введено не в экспоненциальной форме
    else 
    {
        if (1 != scanf("%c", &ch))  
            return INPUT_ERROR;

        if (('E' != ch && 'e' != ch) || (1 != scanf("%ld", &num->exp)))
            return INPUT_ERROR;

        if (MIN_EXP > num->exp || MAX_EXP < num->exp)
            return INPUT_ERROR;

        if (1 != scanf("%c", &ch) || '\n' != ch)  
            return INPUT_ERROR;
    }

    return OK;
}

// функция для чтения одного действительного числа
int read_number(struct number *num)
{
    int point = 0, m_len = 0, rc;
    char ch;

    // чтение знака мантиссы и проверка успешности
    if (OK != (rc = read_mantissa_sign(num, &point, &m_len)))
        return rc;

    // чтение цифр мантиссы и проверка успешности
    if (OK != (rc = read_mantissa(num, &point, &m_len, &ch)))
        return rc;

    // если превышено количество цифр в мантиссе или дальше какой-то мусор
    if (MAX_MANTISSA_LEN == m_len && (0 == point || ('\n' != ch && ' ' != ch)))
        return INPUT_ERROR;

    num->mantissa[m_len] = '\0';

    // чтение порядка числа и проверка успешности
    if (OK != (rc = read_exp(num, ch)))
        return rc;

    return OK;
}
