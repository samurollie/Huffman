#include "list.h"

void print_list (node *head) {
    node* aux = head;
    while(aux != NULL){
        printf("%d | ", aux -> item);
        aux = aux -> next;
    }
    printf ("\n");
}

node *add (node *head, void* item, lli frequency){
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = item; 
    new_node -> frequency = frequency;
    new_node -> next = head;
    new_node -> right = NULL;
    new_node -> left = NULL;
    return new_node;
}

node* create_list() {
    return NULL;
}