#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

// структура для определения узла двоичного дерева поиска
struct tree_node
{
    int val; // значение узла
    struct tree_node *left; // указатель на левое поддерево
    struct tree_node *right; // указатель на правое поддерево
    int bal; // показатель сбалансированности вершины
};
typedef struct tree_node tree_node_s;

tree_node_s *tree_node_create(int num);
void tree_node_free(tree_node_s *node);

#endif
