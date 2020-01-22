#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "../queue/queue.h"

/** @param tree: ponteiro para um nó da árvore*/
/** @return      retorna se o ponteiro é uma folha da árvore ou não*/
int is_leaf(node *tree);

/** @param tree: ponteiro para a árvore a ser impressa */
/** @param h:    altura dos respectivos nós */
void print_tree (node* tree, int h);

/** @param f:    arquivo a ser inscrito */
/** @param tree: ponteiro para a árvore a ser impressa no arquivo */
void print_on_file (FILE *f, node* tree);

/** @param frequency:  frequência do item a ser utilizado*/
/** @param item:       item a ser utilizado*/
/** @param queue:       ponteiro para a queuea*/
/** @return retorna um novo nó para queuea*/
node *create_node(lli frequency, unsigned char item, queue *queue);

/** @param queue: ponteiro para queuea a ser manipulada*/
/** @return retorna um nó pai dos dois primeiros elementos da queuea, cuja frequência é a soma dos dois primeiros elementos da queuea*/
node* join(queue* queue);

/** @param myqueue: recebe um ponteiro para a queuea*/
/** @return retorna um nó que é o resultado final da construção da árvore de Huffman*/
node* build_tree (queue *myqueue);

#endif
