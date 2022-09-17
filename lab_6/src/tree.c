#include <time.h>
#include <stdlib.h>
#include "../inc/tree.h"

// функция для инициализации корня дерева
tree_node_s *tree_init()
{
    return NULL;
}

// функция для освобождения памяти из под дерева
void tree_free_all(tree_node_s *head)
{
    if (!head)
        return;

    tree_free_all(head->left);
    tree_free_all(head->right);
    tree_node_free(head);
}

// функция для добавления узла в ддп
tree_node_s *tree_insert(tree_node_s *head, tree_node_s *node, int *cmps)
{
    if (!head)
        return node;

    if (head->val < node->val)
        head->right = tree_insert(head->right, node, cmps);
    else if (head->val > node->val)
        head->left = tree_insert(head->left, node, cmps);

    (*cmps)++;
    return head;
}

// функция для добавления узла в авл дерево
tree_node_s *balanced_tree_insert(tree_node_s *head, tree_node_s *node, int *h, int *cmps)
{
    if (!head)
    {
        *h = 1;
        return node;
    }

    tree_node_s *head1, *head2;

    if (head->val < node->val)  // добавление в правое поддерево
    {
        head->right = balanced_tree_insert(head->right, node, h, cmps);  // выросла правая ветвь
        // если высота увеличилась
        if (*h)
        {
            switch (head->bal)
            {
                case -1:
                    head->bal = 0;
                    *h = 0;
                    break;
                case 0:
                    head->bal = 1;
                    break;
                case 1:  // балансировка
                    head1 = head->right;
                    if (1 == head1->bal)  // однократный RR-поворот
                    {
                        head->right = head1->left;
                        head1->left = head;
                        head->bal = 0;
                        head = head1;
                    }
                    else  // двукратный RL-поворот
                    {
                        head2 = head1->left;
                        head1->left = head2->right;
                        head2->right = head1;
                        head->right = head2->left;
                        head2->left = head;

                        if (1 == head2->bal)
                            head->bal = -1;
                        else 
                            head->bal = 0; 

                        if (-1 == head2->bal)
                            head1->bal = 1;
                        else 
                            head1->bal = 0; 
                        
                        head = head2;
                    }
                    head->bal = 0; 
                    *h = 0;
            }
        }
    }
    else if (head->val > node->val)
    {
        head->left = balanced_tree_insert(head->left, node, h, cmps);  // выросла левая ветвь
        // если высота увеличилась
        if (*h)
        {
            switch (head->bal)
            {
                case 1:
                    head->bal = 0;
                    *h = 0;
                    break;
                case 0:
                    head->bal = -1;
                    break;
                case -1:  // балансировка
                    head1 = head->left;
                    if (-1 == head1->bal)  // однократный LL-поворот
                    {
                        head->left = head1->right;
                        head1->right = head;
                        head->bal = 0;
                        head = head1;
                    }
                    else  // двукратный LR-поворот
                    {
                        head2 = head1->right;
                        head1->right = head2->left;
                        head2->left = head1;
                        head->left = head2->right;
                        head2->right = head;

                        if (-1 == head2->bal)
                            head->bal = 1;
                        else 
                            head->bal = 0; 

                        if (1 == head2->bal)
                            head1->bal = -1;
                        else 
                            head1->bal = 0; 
                        
                        head = head2;
                    }
                    head->bal = 0; 
                    *h = 0;
            }
        }
    }
    
    (*cmps)++;
    return head;
}

tree_node_s *min_node(tree_node_s *tree)
{
    tree_node_s *cur = tree;

    while (cur && cur->left)
        cur = cur->left;
    
    return cur;
}

// функция для удаления узла ддп
tree_node_s *tree_delete(tree_node_s *tree, int key)
{
    if (tree == NULL)
        return tree;
    
    if (key < tree->val)
        tree->left = tree_delete(tree->left, key);
    else if (key > tree->val)
        tree->right = tree_delete(tree->right, key);
    else if (tree->left != NULL && tree->right != NULL)
    {
        tree->val = min_node(tree->right)->val;
        tree->right = tree_delete(tree->right, tree->val);
    }
    else
    {
        if (!tree->left)
            tree = tree->right;
        else if (!tree->right && tree->left)
            tree = tree->left;
        else
            tree = NULL;
    }

    return tree;
}

// H = true, левая ветвь стала короче
tree_node_s *l_balance(tree_node_s *head, int *h)
{
    int b1, b2;
    tree_node_s *head1, *head2;

    switch (head->bal)
    {
        case -1:
            head->bal = 0;
            break;
        case 0:
            head->bal = 1;
            *h = 0;
            break;
        case 1:  // балансировка
            head1 = head->right;
            b1 = head1->bal;
            if (b1 >= 0)  // однократный RR-поворот
            {
                head->right = head1->left;
                head1->left = head;
                if (b1 == 0)
                {
                    head->bal = 1;
                    head1->bal = -1;
                    *h = 0;
                }
                else
                {
                    head->bal = 0;
                    head1->bal = 0;
                }
                head = head1;
            }
            else  // двукратный RL-поворот
            {
                head2 = head1->left;
                b2 = head2->bal;
                head1->left = head2->right;
                head2->right = head1; 
                head->right = head2->left;
                head2->left = head;
                if (b2 == 1) 
                    head->bal = -1;
                else 
                    head->bal = 0;
                if (b2 == -1) 
                    head1->bal = 1;
                else
                    head1->bal = 0;
                
                head = head2;
                head2->bal = 0;
            }
    }

    return head;
}
// H = true, правая ветвь стала короче
tree_node_s *r_balance(tree_node_s *head, int *h)
{
    int b1, b2;
    tree_node_s *head1, *head2;

    switch (head->bal)
    {
        case 1:
            head->bal = 0;
            break;
        case 0:
            head->bal = -1;
            *h = 0;
            break;
        case -1:  // балансировка
            head1 = head->left;
            b1 = head1->bal;
            if (b1 <= 0)  //однократный LL-поворот
            {
                head->left = head1->right;
                head1->right = head;
                if (b1 == 0)
                {
                    head->bal = -1;
                    head1->bal = 1;
                    *h = 0;
                }
                else
                {
                    head->bal = 0;
                    head1->bal = 0;
                }
                head = head1;
            }
            else  //двукратный LR-поворот
            {
                head2 = head1->right; 
                b2 = head2->bal;
                head1->right = head2->left;
                head2->left = head1; 
                head->left = head2->right;
                head2->right = head;
                if (b2 == -1) 
                    head->bal = 1;
                else 
                    head->bal = 0;
                if (b2 == 1) 
                    head1->bal = -1;
                else
                    head1->bal = 0;
                
                head = head2;
                head2->bal = 0;
            }
    }

    return head;
}

tree_node_s *del(tree_node_s *head, tree_node_s *p, int *h)
{
    if (head)
    {
        head = del(head->right, p, h);

        if (*h)
            head = r_balance(head, h);
    }
    else
    {
        p->val = head->val;
        p = head;
        head = head->left;
        *h = 1;
    }

    return head;
}

// функция для удаления узла авл дерева
tree_node_s *balanced_tree_delete(tree_node_s *head, tree_node_s *node, int *h)
{
    tree_node_s *head2;

    if (!head)
        return head;

    if (node->val < head->val)
    {
        head->left = balanced_tree_delete(head->left, node, h);

        if (*h)
            head = l_balance(head, h);
    }
    else if (node->val > head->val)
    {
        head->right = balanced_tree_delete(head->right, node, h);

        if (*h)
            head = r_balance(head, h);
    }
    else
    {
        head2 = head;
        if (NULL == head2->right)
        {
            head = head2->left;
            *h = 1;
        }
        else
        {
            if (NULL == head2->left)
            {
                head = head2->right;
                *h = 1;
            }
            else
            {
                head2->left = del(head2->left, head2, h);
                if (*h)
                    head = l_balance(head, h);
            }
        }
    }
    
    return head;
}

// функция для поиска узла в дереве с переданным значением
tree_node_s *tree_find(tree_node_s *head, int num)
{
    while (head && num != head->val)
    {
        if (num < head->val)
            head = head->left;
        else
            head = head->right;
    }

    return head;
}

// функция для печати в файл узла дерева и его двух потомков
void tree_to_dot(tree_node_s *head, void *param)
{
    FILE *f = param;

    if (head->left)
        fprintf(f, "%d -> %d;\n", head->val, head->left->val);

    if (head->right)
        fprintf(f, "%d -> %d;\n", head->val, head->right->val);
}

// функция для обработки узлов дерева переданной функцией
void tree_apply(tree_node_s *head, void (*f)(tree_node_s*, void*), void *arg)
{
    if (!head)
        return;

    f(head, arg);
    tree_apply(head->left, f, arg);
    tree_apply(head->right, f, arg);
}

// функция для вывода дерева на языке DOT в файл
void tree_export_to_dot(FILE *f, tree_node_s *head)
{
    fprintf(f, "digraph bst {\n");
    tree_apply(head, tree_to_dot, f);
    fprintf(f, "}\n");
}

// функция для вывода времени добавления в ддп, памяти и количества сравнений
void bst_print_insert_results()
{
    tree_node_s *bst, *bst_node;
    clock_t start; // время до
    clock_t time = 0;
    int cmps = 0, rep = 1000, mem, cmp;
    
    for (int j = 0; j < rep; j++)
    {
        bst = tree_init();
        // время выполнения
        start = clock();

        for (int i = 0; i < 500; i++)
        {
            bst_node = tree_node_create(rand() % 1000);

            if (bst_node)
            {
                cmp = 0;
                bst = tree_insert(bst, bst_node, &cmp);
                cmps += cmp;
            }
        }
        
        time += clock() - start;
        // память под ддп
        mem = 500 * sizeof(tree_node_s);
        tree_free_all(bst);
    }

    printf("|%20s ", "bst");
    printf("|%27f ", (float)time / rep);
    printf("|%27d ", mem);
    printf("|%f\n\n", (float)cmps / (rep * 500));
}

// функция для вывода времени добавления в авл, памяти и количества сравнений
void avl_print_insert_results()
{
    tree_node_s *avl, *avl_node;
    clock_t start; // время до
    clock_t time = 0;
    int cmps = 0, rep = 1000, mem, cmp, h;
    
    for (int j = 0; j < rep; j++)
    {
        avl = tree_init();
        // время выполнения
        start = clock();

        for (int i = 0; i < 500; i++)
        {
            avl_node = tree_node_create(rand() % 1000);

            if (avl_node)
            {
                h = 0;
                cmp = 0;
                avl = balanced_tree_insert(avl, avl_node, &h, &cmp);
                cmps += cmp;
            }
        }
        
        time += clock() - start;
        // память под авл
        mem = 500 * sizeof(tree_node_s);
        tree_free_all(avl);
    }

    printf("|%20s ", "avl");
    printf("|%27f ", (float)time / rep);
    printf("|%27d ", mem);
    printf("|%f\n\n", (float)cmps / (rep * 500));
}
