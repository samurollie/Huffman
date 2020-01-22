#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef long long int lli;
typedef struct node node;
typedef struct list list;

struct node {
    unsigned char item;
    int frequency;
    node* left;
    node* right;
    node* next;
};

struct list {
	node* head;
    int size;
};

/** @param head: a cabeça da lista a ser imprimida */
void print_list (node *head);

/** @param list:      lista que receberá um novo elemento*/
/** @param new_node:  nó a ser inserido na lista*/
void insert(list* list, node* new_node);

/** @param list:      lista que receberá um novo elemento*/
/** @param item:      o item que vai ser salvo na lista */
/** @param frequency: a frequencia do item*/
/** @return retorna um novo ponteiro para a lista*/
list *add (list *list, unsigned char item, lli frequency);

/** @return retorna uma lista vazia */
list* create_list();

#endif