#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include "tree_node.h"

tree_node_s *tree_init();
void tree_free_all(tree_node_s *head);
tree_node_s *tree_insert(tree_node_s *head, tree_node_s *node, int *cmps);
tree_node_s *balanced_tree_insert(tree_node_s *head, tree_node_s *node, int *h, int *cmps);
tree_node_s *tree_find(tree_node_s *head, int num);
void tree_export_to_dot(FILE *f, tree_node_s *head);
void bst_print_insert_results();
void avl_print_insert_results();

#endif
