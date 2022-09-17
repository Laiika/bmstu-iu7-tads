#include "funcs.h"

int main(void)
{
    setbuf(stdout, NULL);
    printf("Программа перемножает два действительных числа\n");
    printf("Число может быть введено с точкой(перед числом, внутри или в конце) или без\n");
    printf("Знак числа может быть указан(перед числом) или нет\n");
    printf("При представлении числа в экспоненциальной форме: (знак)m.n Е (знак)K,\n"); 
    printf("где суммарная длина мантиссы (m+n) - до 30 цифр, а величина порядка K - до 5 цифр\n");
    printf("Между мантиссой и E один пробел, допустимо E/e\n");
    printf("Между E и порядком не более одного пробела\n");

    struct number first, second;
    int rc;

    printf("Введите первое число: ");
    // ввод первого числа и проверка успешности ввода
    if (OK != (rc = read_number(&first)))
    {
        printf("Некорректно введено первое число\n");
        return rc;
    }

    printf("Введите второе число: ");
    // ввод второго числа и проверка успешности ввода
    if (OK != (rc = read_number(&second)))
    {
        printf("Некорректно введено второе число\n");
        return rc;
    }

    short mantissa1[MAX_DIGITS_NUM], mantissa2[MAX_DIGITS_NUM], result_mantissa[MAX_DIGITS_NUM * 2 + 1] = {0};
    short size1, size2;

    // нормализация введенных чисел
    normalize_number(&first, mantissa1, &size1);
    normalize_number(&second, mantissa2, &size2);

    // перемножение мантисс (возвращаем индекс начала мантиссы в массиве)
    short start = mult_numbers(mantissa1, size1, mantissa2, size2, result_mantissa);

    long result_exp;
    // вычисление экспоненты
    if (OK != (rc = calc_exp(&result_exp, first.exp, second.exp, result_mantissa, &start)))
    {
        if (EXP_TOO_LARGE == rc)
            printf("Порядок при умножении превышен\n");
        else 
            printf("Порядок при умножении получился меньше допустимого\n");

        return rc;
    }

    // округление мантиссы (возвращаем индекс конца мантиссы в массиве)
    short end = round_mantissa(result_mantissa, start);

    printf("Результат умножения: ");
    // вывод ответа в экспоненциальной форме
    if (first.m_sign == second.m_sign)
        print_number('+', result_mantissa, start, end, result_exp);
    else
        print_number('-', result_mantissa, start, end, result_exp);

    return OK;
}
