#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER 2000

typedef struct node node;
typedef struct tree tree;

struct node {
    node *next;
    int item;
};

struct tree {
    int item;
    tree* left;
    tree* right;
};

void search_binary_tree(tree* bt, int item, int *cont) { 
    *cont += 1;
    if ((bt == NULL) || bt->item == item) {
        return;
    } else if (bt->item >= item) {
        return search_binary_tree(bt->left, item, cont);
    } else {
        return search_binary_tree(bt->right, item, cont);
    }
}

tree* create_tree(int item, tree* left, tree* right) {
    tree* new_child = (tree*) malloc(sizeof(tree));
    new_child->item = item;
    new_child->left = left;
    new_child->right = right;
    return new_child;
}

tree* add_tree(tree* bt, int number) {
    if (bt == NULL) {
        bt = create_tree(number, NULL, NULL);
    } else if (bt->item > number) {
        bt->left = add_tree(bt->left, number);
    } else {
        bt->right = add_tree(bt->right, number);
    }
    return bt;
}

void search_list (node *head, int item, int *cont) {
    node *aux = head;
    while (aux != NULL) {
        *cont += 1;
        if (aux->item == item) {            
            return; 
        }
        aux = aux->next; 
    }
    return; 
}

node* add_list(node* head, int item) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = item; 
    new_node->next = head; 
    return new_node; 
}

int random_numbers() {
    return rand() % 7777;
}

int main() {
    tree* arvore = NULL;
    node* list = NULL;
    for (int i = 0; i < MAX_NUMBER; i++) {
        int n = random_numbers();
        list = add_list(list, n);
        arvore = add_tree(arvore, n);
    }
    printf ("Valor    Lista   Arvore\n");
    for(int i = 0; i < MAX_NUMBER; i++) {
        int n = random_numbers();

        int cont_tree = 0;
        search_binary_tree(arvore, n, &cont_tree);

        int cont_list = 0;
        search_list(list, n, &cont_list);

        printf ("%d    %d   %d\n", n, cont_list, cont_tree);
    }
    return 0;
}