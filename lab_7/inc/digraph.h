#ifndef _DIGRAPH_H_
#define _DIGRAPH_H_

#include <stdio.h>
#include "../inc/node.h"
#include "../inc/return_codes.h"

// структура для определения орграфа в виде массива из списков смежностей вершин
struct digraph
{
    int size;  // размер массива
    node_s **arr;  // массив
};
typedef struct digraph digraph_s;

int digraph_create(FILE *file, digraph_s *graph);
void digraph_free(digraph_s *graph);
void dfs(digraph_s *graph, int *visited, int vertex);
void digraph_export_to_dot(FILE *f, digraph_s *graph);
void digraph_visited_export_to_dot(FILE *f, digraph_s *graph, int *visited);

#endif
