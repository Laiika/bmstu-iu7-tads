#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>

// структура для определения элемента списка смежностей вершины
struct node
{
    int vertex;  // номер вершины
    struct node *next;  // указатель на следующую вершину
};
typedef struct node node_s;

node_s *node_create(int num);
void node_free(node_s *node);

#endif
