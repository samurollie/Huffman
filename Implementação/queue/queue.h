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

/** @param head: a cabeça da fila que deve ser impressa */
void print_queue (node *head);

/** @param queue:     fila que receberá um novo elemento*/
/** @param new_node:  nó a ser inserido na fila*/
void enqueue(queue* queue, node* new_node);

node *dequeue(queue *queue);

/** @param frequency:  frequência do item a ser utilizado*/
/** @param item:       item a ser utilizado*/
/** @param queue:      ponteiro para a queuea*/
/** @param left:       ponteiro para o filho da esquerda*/
/** @param right:      ponteiro para o filho da direita*/
/** @return retorna um novo nó para queue*/
node *create_node(lli frequency, unsigned char item, queue *queue, node *left, node *right);

/** @param queue:     fila que receberá um novo elemento*/
/** @param item:      o item que vai ser salvo na fila */
/** @param frequency: a frequencia do item*/
/** @return retorna um novo ponteiro para a fila*/
queue *add_on_queue (queue *queue, unsigned char item, lli frequency);

/** @return retorna uma fila vazia */
queue *create_queue();

#endif
