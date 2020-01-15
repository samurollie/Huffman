#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "../list/list.h"

int is_leaf(node *tree);
void print_tree (node* tree, int h);
void print_on_file (FILE *f, node* tree);
node *create_node(node *head, lli frequency, unsigned char item, list *list);
node* join(list* list);
node* build_tree (list *mylist);

#endif