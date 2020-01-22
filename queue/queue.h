#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef long long int lli;
typedef struct node node;
typedef struct queue queue;

struct node {
    unsigned char item;
    int frequency;
    node* left;
    node* right;
    node* next;
};

struct queue {
	node* head;
    int size;
};

/** @param head: a cabeça da fila a ser imprimida */
void print_queue (node *head);

/** @param queue:     fila que receberá um novo elemento*/
/** @param new_node:  nó a ser inserido na fila*/
void enqueue(queue* queue, node* new_node);

node *dequeue(queue *queue);

/** @param queue:     fila que receberá um novo elemento*/
/** @param item:      o item que vai ser salvo na fila */
/** @param frequency: a frequencia do item*/
/** @return retorna um novo ponteiro para a fila*/
queue *add (queue *queue, unsigned char item, lli frequency);

/** @return retorna uma fila vazia */
queue *create_queue();

#endif
