#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    unsigned char item;
    int frequency;
    node* left;
    node* right;
    node* next;
};

void print_list (node *head);

node *add(node *head, int item);

node* create_list();

#endif