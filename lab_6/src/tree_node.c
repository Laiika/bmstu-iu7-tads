#include <stdio.h>
#include <stdlib.h>
#include "../inc/tree_node.h"

// функция для создания узла дерева
tree_node_s *tree_node_create(int num)
{
    tree_node_s *node = malloc(sizeof(tree_node_s));

    if (node)
    {
        node->val = num;
        node->left = NULL;
        node->right = NULL;   
        node->bal = 0;    
    }
        
    return node;
}

// функция для освобождения памяти из под узла дерева
void tree_node_free(tree_node_s *node)
{
    free(node);
}
