#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "../list/list.h"

/** @param tree: ponteiro para um nó da árvore*/
/** @return      retorna se o ponteiro é uma folha da árvore ou não*/
int is_leaf(node *tree);

/** @param tree: ponteiro para a árvore a ser impressa */
/** @param h:    altura dos respectivos nós */
void print_tree (node* tree, int h);

/** @param f:    arquivo a ser inscrito */
/** @param tree: ponteiro para a árvore a ser impressa no arquivo */
void print_on_file (FILE *f, node* tree);

//OBS: RETIRAR ESSE HEAD DO PARAMETRO!!!!!!!!!!!!!!!!!!!!!!

/** @param frequency:  frequência do item a ser utilizado*/
/** @param item:       item a ser utilizado*/
/** @param list:       ponteiro para a lista*/
/** @return retorna um novo nó para lista*/
node *create_node(node *head, lli frequency, unsigned char item, list *list);

/** @param list: ponteiro para lista a ser manipulada*/
/** @return retorna um nó pai dos dois primeiros elementos da lista, cuja frequência é a soma dos dois primeiros elementos da lista*/
node* join(list* list);

/** @param mylist: recebe um ponteiro para a lista*/
/** @return retorna um nó que é o resultado final da construção da árvore de Huffman*/
node* build_tree (list *mylist);

#endif
