#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "../queue/queue.h"

/** @param tree: ponteiro para um nó da árvore*/
/** @return      retorna se o ponteiro é uma folha da árvore ou não*/
int is_leaf(node *tree);

/** @param tree: ponteiro para a árvore a ser impressa */
void print_tree (node* tree);

/** @param f:    arquivo a ser inscrito */
/** @param tree: ponteiro para a árvore a ser impressa no arquivo */
void print_tree_on_file (FILE *f, node* tree);

/** @param queue: ponteiro para queuea a ser manipulada*/
/** @return retorna um nó pai dos dois primeiros elementos da queuea, cuja frequência é a soma dos dois primeiros elementos da queuea*/
node* join(queue* queue);

/** @param myqueue: recebe um ponteiro para a queuea*/
/** @return retorna um nó que é o resultado final da construção da árvore de Huffman*/
node* build_tree (queue *myqueue);

#endif
