#include "funcs.h"

// функция для вычисления экспоненты результата
short round_mantissa(short *mantissa, short start)
{
    short end = start + MAX_DIGITS_NUM; // индекс конца мантиссы

    if (end < MAX_DIGITS_NUM * 2 + 1 && mantissa[end] >= 5) // в мантиссе больше 30 цифр и будет перенос из 31
    {
        for (int i = end; i > 0; i--, end--)
            if (mantissa[i - 1] + 1 < 10) // увеличиваем старший на 1
            {
                mantissa[i - 1]++;
                mantissa[i] = 0;
                break;
            }
            else // в старшем 9, переносим дальше
                mantissa[i] = 0;

        if (end <= start)
            return start;

        return end - 1;
    }
    else if (end < MAX_DIGITS_NUM * 2 + 1) // переноса из 31ого нет
        return end - 1;
    
    return MAX_DIGITS_NUM * 2;  // в мантиссе менне 30 цифр
}
