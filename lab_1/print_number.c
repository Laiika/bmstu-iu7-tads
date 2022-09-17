#include "funcs.h"

// функция для вывода результата в экспоненциальной форме
void print_number(char sign, short *mantissa, short start, short end, long exp)
{
    printf("%c0.", sign);

    for (short i = start; i <= end; i++)
        printf("%d", mantissa[i]);

    printf(" E ");

    printf("%ld\n", exp);
}
