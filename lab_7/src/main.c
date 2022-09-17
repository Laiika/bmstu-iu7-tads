#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/digraph.h"
#include "../inc/return_codes.h"

#define MAX_FILE_NAME 30

// функция для чтения имени файла
int read_file_name(char *const str, const int size)
{
    if (!fgets(str, size, stdin))
        return READ_ERROR;

    int ch, len = strlen(str);

    if ((len == MAX_FILE_NAME) && ((ch = getchar()) != '\n' && ch != EOF))
        return READ_ERROR;

    if (str[0] == '\n')
        return READ_ERROR;

    if (str[len - 1] == '\n')
        str[len - 1] = '\0';

    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);
    char name[MAX_FILE_NAME + 1];  // имя исходного файла
    FILE *in = NULL, *out = NULL;
    digraph_s dg;  // орграф
    int vertex, command = 1, create = 0, rc;
    int *visited;  // массив достижимости вершин из указанной
    char ch;

    // выполняем команды из меню
    while (command)
    {
        printf("\nВозможные действия (введите номер нужной команды):\n");
        printf("0. Завершить работу\n");
        printf("1. Ввести имя исходного файла\n");
        printf("2. Вывести орграф\n");
        printf("3. Вывести все вершины заданного opграфа, недостижимые из заданной его вершины\n");

        if (1 != scanf("%d", &command))
            continue;

        switch (command)
        {
            case 0:
                break;
            case 1:
                scanf("%c", &ch);
                if (OK == read_file_name(name, sizeof(name))) // чтение имени исходного файла
                {
                    if (NULL != (in = fopen(name, "r"))) 
                    {
                        if (create)  // орграф уже был создан
                            digraph_free(&dg);
                        // создание орграфа по файлу
                        if (READ_ERROR == (rc = digraph_create(in, &dg)))
                        {
                            printf("Ошибка ввода\n");
                            create = 0;
                        }
                        else if (MEMORY_ERROR == rc)
                        {
                            printf("Ошибка выделения памяти\n");
                            create = 0;
                        }
                        else
                            create = 1;  // орграф создан

                        fclose(in);
                    }
                    else
                        printf("Ошибка открытия файла\n");
                }
                else
                    printf("Ошибка ввода\n");
                break;
            case 2:
                if (create && NULL != (out = fopen("digraph.gv", "w"))) // открытие файла на запись 
                {
                    digraph_export_to_dot(out, &dg);
                    fclose(out);
                    system("dot -Tpng digraph.gv -o digraph.png");
                }
                else 
                    printf("Орграф не создан\n");
                break;
            case 3:
                printf("Введите номер вершины: ");
                if (1 != scanf("%d", &vertex) || vertex < 1 || vertex > dg.size) // ошибка ввода числа
                {
                    scanf("%c", &ch);
                    while ('\n' != ch)
                        scanf("%c", &ch);
                    printf("Ошибка ввода\n");
                }
                else if (create)  // орграф существует 
                {
                    visited = calloc(dg.size + 1, sizeof(int));

                    if (visited)
                    {
                        dfs(&dg, visited, vertex);  // поиск в глубину от указанной вершины
                        printf("Все недостижимые вершины:\n");

                        for (int i = 1; i <= dg.size; i++)
                            if (0 == visited[i])
                                printf("%d ", i);

                        printf("\n");
                        // вывод орграфа с раскрашенными вершинами в зависимости от их достижимости из заданной
                        out = fopen("visited.gv", "w");
                        digraph_visited_export_to_dot(out, &dg, visited);
                        fclose(out);
                        system("dot -Tpng visited.gv -o visited.png");

                        free(visited);
                    }
                    else
                        printf("Ошибка выделения памяти\n");
                }
                else 
                    printf("Орграф не создан\n");
                break;
            default:
                printf("Нет команды с введенным номером\n");
        }
    }

    if (create)
        digraph_free(&dg);
}
