#include <stdlib.h>
#include "../inc/digraph.h"

// функция для создания орграфа
int digraph_create(FILE *file, digraph_s *graph)
{
    // чтение количества вершин в графе
    if (1 != fscanf(file, "%d", &(graph->size)) || graph->size < 1)
        return READ_ERROR;

    graph->arr = calloc((graph->size + 1), sizeof(node_s*));
    // получилось выделить память под массив
    if (graph->arr)
    {
        int num;
        // граф в файле задан в виде матрицы смежности
        for (int i = 1; i <= graph->size; i++)
        {
            graph->arr[i] = NULL;

            for (int j = 1; j <= graph->size; j++)
            {
                if (1 != fscanf(file, "%d", &num) || (0 != num && 1 != num))
                {
                    digraph_free(graph);
                    return READ_ERROR;
                }
                // есть путь из iой вершины в jую
                if (num)
                {
                    node_s* new_node = node_create(j);

                    if (new_node)  // добавляем вершину j в список смежности вершины i 
                    {
                        new_node->next = graph->arr[i];
                        graph->arr[i] = new_node;
                    }
                    else
                    {
                        digraph_free(graph);
                        return READ_ERROR;
                    }
                }
            }  
        }
    }
    else
        return MEMORY_ERROR;

    return OK;
}

// функция для освобождения памяти из под орграфа
void digraph_free(digraph_s *graph)
{
    for (int i = 1; i <= graph->size; i++)
    {
        node_s *next;

        for (; graph->arr[i]; graph->arr[i] = next)
        {
            next = graph->arr[i]->next;
            node_free(graph->arr[i]);
        }
    }

    free(graph->arr);
}

// функция для обхода орграфа в глубину из заданной вершины
void dfs(digraph_s *graph, int *visited, int vertex) 
{
    struct node* cur = graph->arr[vertex];
    // посетили вершину
    visited[vertex] = 1;
    // проходимся по списку смежности вершины
    while (cur != NULL) 
    {
        int connected_v = cur->vertex;
        // вершина из списка еще не посещена
        if (0 == visited[connected_v]) 
            dfs(graph, visited, connected_v);

        cur = cur->next;
    }      
}

// функция для вывода орграфа на языке DOT в файл
void digraph_export_to_dot(FILE *f, digraph_s *graph)
{
    fprintf(f, "digraph result {\n");

    for (int i = 1; i <= graph->size; i++)
        fprintf(f, "%d [style=\"filled\", color=\"black\", fillcolor=\"white\"];\n", i);

    for (int i = 1; i <= graph->size; i++)
    {
        for (node_s *cur = graph->arr[i]; cur; cur = cur->next)
            fprintf(f, "%d -> %d;\n", i, cur->vertex);
    }

    fprintf(f, "}\n");
}

// функция для вывода раскрашенного в зависимости от посещенности вершин орграфа на языке DOT в файл
void digraph_visited_export_to_dot(FILE *f, digraph_s *graph, int *visited)
{
    fprintf(f, "digraph visited {\n");

    for (int i = 1; i <= graph->size; i++)
    {
        fprintf(f, "%d ", i);

        if (visited[i])  // вершина была посещена
            fprintf(f, "[style=\"filled\", color=\"black\", fillcolor=\"green\"];\n");
        else
            fprintf(f, "[style=\"filled\", color=\"black\", fillcolor=\"red\"];\n");
    }

    fprintf(f, "\n");

    for (int i = 1; i <= graph->size; i++)
    {
        for (node_s *cur = graph->arr[i]; cur; cur = cur->next)
            fprintf(f, "%d -> %d;\n", i, cur->vertex);
    }

    fprintf(f, "}\n");
}
