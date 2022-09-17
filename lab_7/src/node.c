#include <stdlib.h>
#include "../inc/node.h"

// функция для создания элемента
node_s *node_create(int num)
{
    node_s *node = calloc(1, sizeof(node_s));

    if (node)
    {
        node->vertex = num;
        node->next = NULL;        
    }
        
    return node;
}

// функция для освобождения памяти из под элемента
void node_free(node_s *node)
{
    free(node);
}
