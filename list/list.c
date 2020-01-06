#include "list.h"

void print_list (node *head) {
    node* aux = head;
    while(aux != NULL){
        printf("%d ", aux->frequency);
        aux = aux -> next;
    }
    printf ("\n");
}

void insert(list* list, node* new_node) {
    if(list->size == 0 || new_node->frequency < list->head->frequency) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        node* aux = list->head;
        while (aux->next != NULL && aux->next->frequency < new_node->frequency) {
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }
    list->size++;
}

list *add (list *list, unsigned char item, lli frequency) { //create
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = item; 
    new_node -> frequency = frequency;
    new_node -> right = NULL;
    new_node -> left = NULL;
    insert(list, new_node);
    return list;
}

list* create_list() {
    list *new_list = (list*) malloc(sizeof(list));
    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}