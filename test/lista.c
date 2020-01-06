#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "list/list.h"

typedef long long int lli;
typedef struct node node;

struct node {
    unsigned char item;
    int frequency;
    node* left;
    node* right;
    node* next;
};

void print_list (node *head) {
    node* aux = head;
    while(aux != NULL){
        printf("%d ", aux->frequency);
        aux = aux -> next;
    }
    printf ("\n");
}

void insert (node* new_node, node* head) {
    if (head == NULL) { // Se a lista estiver vazia
        new_node->next = head;
    } else {
        node *aux = head;
        node *previous = NULL;
        while(aux != NULL && aux->frequency < new_node->frequency) {
            previous = aux;
            aux = aux->next;
        }
        if (previous == NULL) { // Se previous continuar valendo NULL, significa que eu desejo adicionar um valor na cabeça da lista;
            new_node->next = aux;
        } else {
            previous->next = new_node;
            new_node->next = aux;
        }
    }
}

node *add (node *head, unsigned char item, lli frequency){
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = item; 
    new_node -> frequency = frequency;
    new_node -> right = NULL;
    new_node -> left = NULL;
    insert(new_node, head);
    return new_node;
}

node* create_list() {
    return NULL;
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
    
    node *head = NULL;
    int i, size_list = 0;
    for (i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            head = add(head, 'a',frequency[i]);
            size_list++;
        }
    }
    print_list(head);
    
    return 0;
}