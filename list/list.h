#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef long long int lli;

typedef struct node node;
struct node {
    void* item;
    int frequency;
    node* left;
    node* right;
    node* next;
};

void print_list (node *head);

node *add(node *head, void* item, lli frequency);

node* create_list();

#endif