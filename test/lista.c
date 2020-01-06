#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "list/list.h"
// #include "../hash/hash.h"

typedef long long int lli;
typedef struct node node;
typedef struct list list;
#include <ctype.h>

#define HASH_SIZE 256

typedef struct hash_table hash_table;
typedef struct hash_node hash_node;
typedef long long int lli;

struct hash_node {
    hash_node* next;
    unsigned char key;
    lli frequency;
};

struct hash_table {
    hash_node *table[HASH_SIZE];
};

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

// Verifica se ja foi adicionado um valor com aquela chave, retornando 1 se for encontrado e 0 caso contrario;
int contains_key(hash_table *ht, unsigned char key) {
    int h = (int) key;
    hash_node* aux = ht->table[h];
    while (aux != NULL) {
        if (aux->key == key) return 1; 
        aux = aux->next;
    }
    return 0;
}

// Imprime uma lista encadeada;
void print_linked_list (hash_node* head) {
    while (head != NULL) {
        printf ("Chave: %c, Frequencia: %lld ", head->key, head->frequency);
        head = head->next;
    }
    printf ("\n");
}

// Imprime uma hash table;
void print_hash_table(hash_table *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (ht->table[i] != NULL) {
            printf("Posicao %d: ", i);
            print_linked_list(ht->table[i]);
        }
    }
}

// Remove um valor na hash_table;
void remove_value(hash_table *ht, unsigned char key) {
    int h = (int) key;
    hash_node* aux = ht->table[h];
    hash_node* previous = NULL;
    while (aux != NULL) {
        if (aux->key == key) {
            if (previous == NULL) {
                ht->table[h] = aux->next;
            } else {
                previous->next = aux->next;
            }
            free(aux);
            aux = NULL;
            return;
        }
        previous = aux;
        aux = aux->next;
    }
}

// Procura um valor na hash table
int get(hash_table *ht, unsigned char key) {
    int h = (int) key;
    hash_node* aux = ht->table[h];
    while (aux != NULL) {
        if (aux->key == key) {
            return aux->frequency;
        }
        aux = aux->next;
    }
    return -1;
}

hash_node* add_node(hash_node* head, lli frequency, unsigned char key) {
    hash_node* new_node = (hash_node*) malloc(sizeof(hash_node));
    new_node ->next = head;
    new_node->frequency = frequency;
    new_node->key = key;
    return new_node;
}

// Adiciona um novo valor na hash table;
void put (hash_table *ht, unsigned char key, lli frequency) {
    int h = (int) key; // Esse aqui que e o meu calculo que diz qual vai ser a posição no array que eu vou adicionar o elemento  
    ht->table[h] = add_node(ht->table[h], frequency, key);
    return;
}

// Cria uma nova hash table;
hash_table* create_hash_table () {
    hash_table *new_hash_table = (hash_table*) malloc (sizeof(hash_table)); // Aquela alocação de espaço na memoria que a gente ja ta acostumado
    for (int i = 0; i < HASH_SIZE; i++) { // Navego pelo array e faço cada elemento apontar para nulo;
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

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

void *get_frequency(FILE *file, hash_table *mapping) {
    unsigned char unit;
	while (fscanf(file,"%c",&unit) != EOF) { // vai até o EOF.
		int h = (int) unit;
		if (!contains_key(mapping, unit)) { // Se eu ainda não adicionei aquele caracter;
            put(mapping, unit, 1);
        } else {
            mapping->table[h]->frequency++;
        }
  	}
}

FILE *open_file(char* path) {
    FILE *f = fopen(path, "r");
    return f;
}

int main() {
    FILE *arq; 
    arq = open_file("../a.txt");
    hash_table* mapping = create_hash_table();
    get_frequency(arq, mapping);
    print_hash_table(mapping);

    list *list = create_list();
    int i, size_list = 0;
    for (i = 0; i < 256; i++) {
        if (mapping->table[i] != NULL) {
            list = add(list, mapping->table[i]->key, mapping->table[i]->frequency);
            size_list++;
        }
    }
    // print_list(list->head);
    
    return 0;
}