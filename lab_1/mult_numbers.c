#include "funcs.h"

// функция для перемножения двух действительных числе
short mult_numbers(short *nums1, short size1, short *nums2, short size2, short *result)
{
    short start = MAX_DIGITS_NUM * 2;  // индекс начала мантиссы в массиве

    if ((1 == size1 && 0 == nums1[0]) || (1 == size2 && 0 == nums2[0])) // один из множителей - 0
    {
        result[start] = 0;
        return start;
    }

    // умножение первого числа на второе в столбик
    for (int i = size2 - 1; i >= 0; i--)
    {
        if (0 != nums2[i])
        {
            start = MAX_DIGITS_NUM * 2 - (size2 - 1 - i);
            short over = 0, last;  // перенос в старший разряд

            for (int j = size1 - 1; j >= 0; j--)
            {
                last = result[start];
                result[start] = (last + nums2[i] * nums1[j] + over) % 10;
                over = (last + nums2[i] * nums1[j] + over) / 10;
                start--;  // переходим в старший разряд
            }

            result[start] = over;
        }
    }

    return start;
}
