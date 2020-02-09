#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct tree tree;

struct node {
    struct node *next;
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

void list() {
    node *list = NULL;
    int number;
    for(int i = 0; i < 999; i++) {
        scanf("%d", &number);
        list = add_list(list, number);
    }
    for (int i = 0; i < 999; i++) {
        int cont = 0;
        scanf("%d", &number);
        search_list(list, number, &cont);
        printf("%d\n", cont);
    }
    return;
}

void binary_tree () {
    tree* arvore = NULL;
    int number;
    for(int i = 0; i < 999; i++) {
        scanf("%d", &number);
        arvore = add_tree(arvore, number);
    }
    for(int i = 0; i < 999; i++) {
        int cont = 0;
        scanf("%d", &number);
        search_binary_tree(arvore, number, &cont);
        printf("%d\n", cont);
    }
    return;
}

int main() {
    list();
    binary_tree();   
    return 0;
}