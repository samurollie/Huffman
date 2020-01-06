#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "list/list.h"

typedef long long int lli;
typedef struct node node;
typedef struct list list;
typedef struct arvore arvore;

struct node {
    unsigned char item;
    int frequency;
    node* left;
    node* right;
    node* next;
};

struct arvore {
  int value;
  unsigned char item;
  node *left;
  node *right;
}

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

void remove_head(list* list) {
  node* aux = list->head;
  list->head = aux->next;
  free(aux); 
  //fila->size--; 
}

node *create_node(node *node, lli join_frequency, list *list){
  node *father = (node*) malloc(sizeof(node));
  father->frequency = join_frequency;
  father->item = '*';
  father->left = list->head;
  father->right = list->head->next;
  return father;
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

node* join(list* list) {
  //node *aux = NULL;
  //while(list->size > 0) 
    lli join_frequency;
    if(list->head->next == NULL) join_frequency = list->head->frequency;
    else join_frequency  = list->head->frequency + list->head->next->frequency;
    node *father = create_node(father, join_frequency, list);
    insert(list, father); // realoca o novo nó na posição correta
    aux = father;
    //list->size -= 2;
    //list = list->head->next->next;
  return aux; //??
	//toda vez que fizer um laço de repetição ele vai precisar do father novo, né? // sim // pode ser // tu pode fazer enquato tomo banho?// uns 10 minutos eu volto // tá
  //pera, a gente pode criar a repetição em outro lugar, tipo outra função, e a parte que tá dentro do while seria a join, siim, vou tentando aqui, vou só sair rapidão, mas não vai demorar nem 2 min
    
}

// 

void control_join()
{
  int i;
  for(i = 0; i < list->size; i++)
  {
    //join(list);
    create_
    
  }
}

arvore *create_arvore() {
  arvore *tree = (arvore*) malloc(sizeof(arvore));
  tree = join(list); // é isso?
  return tree;
}

list *add (list *list, unsigned char item, lli frequency){
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