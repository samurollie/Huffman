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

/** @param compressed_file: arquivo comprimido. */
/** @param file:            arquivo descompactado. */
/** @param mytree:          árvore que será percorrida. */
/** @param trash_size:      tamanho do lixo. */
void print_original_file (FILE *compressed_file, FILE *file, tree *mytree, int trash_size);

/** @param item:   item a ser salvo no nó. */
/** @param left:   ponteiro para o filho da esquerda. */
/** @param right:  ponteiro para o filho da direita. */
tree* create_child (unsigned char item, tree* left, tree* right);

/** @param file:    arquivo compactado. */
/** @param tree:    árvore a ser construída. */
/** @return:        a árvore construída. */
tree* create_tree_from_file(FILE* file, tree* tree);

void decompress ();

#endif