#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "list/list.h"

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

struct list { //:)
	node* head;
  int size;
};

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

list *add (list *list, unsigned char item, lli frequency){ //create
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

lli *get_frequency(FILE *file) {
    lli *repeticao = (lli*) malloc(sizeof(lli) * 256);
    memset(repeticao, 0, 256);
    unsigned char unit;
	while (fscanf(file,"%c",&unit) != EOF) { // vai até o EOF.
		int a = (int) unit;
		repeticao[a] += 1;
  	}
    return repeticao;
}

FILE *open_file(char* path) {
    FILE *f = fopen(path, "r");
    return f;
}

int main() {
    FILE *arq; 
    arq = open_file("../a.txt");
    lli *frequency = get_frequency(arq);
    
    list *list = create_list();
    int i, size_list = 0;
    for (i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            list = add(list, 'a',frequency[i]);
            size_list++;
        }
    }
    print_list(list->head);
    
    return 0;
}