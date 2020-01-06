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

void print_list (node *head);

void insert(list* list, node* new_node);

list *add (list *list, unsigned char item, lli frequency);

list* create_list();

#endif