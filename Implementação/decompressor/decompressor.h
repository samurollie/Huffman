#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "../queue/queue.h"
#include "../bits/bits.h"
#include "../huff_tree/huff_tree.h"
#include <string.h>
#include <math.h>

typedef struct tree tree;

struct tree {
    unsigned char item;
    tree *left;
    tree * right;
};

void print_tree_again(tree* tree);
int is_leaf_temp (tree *tree);
void the_walking_tree (FILE *compressed_file, FILE *file, tree *mytree, int trash_size);
tree* create_child (unsigned char item, tree* left, tree* right);
tree* create_tree_from_file(FILE* file, tree* tree);
void decompress ();

#endif