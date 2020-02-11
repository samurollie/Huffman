#include "hash.h"

int contains_key(hash_table *ht, unsigned char key) {
    int h = (int) key;
    hash_node* aux = ht->table[h];
    while (aux != NULL) {
        if (*(unsigned char*) aux->key == key) return 1; 
        aux = aux->next;
    }
    return 0;
}

void print_linked_queue (hash_node* head) {
    while (head != NULL) {
        printf ("Chave: %c, Frequencia: %lld ", *(unsigned char*) head->key, head->frequency);
        head = head->next;
    }
    printf ("\n");
}

void print_hash_table(hash_table *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (ht->table[i] != NULL) {
            printf("Posicao %d: ", i);
            print_linked_queue(ht->table[i]);
        }
    }
}

int get(hash_table *ht, unsigned char key) {
    int h = (int) key;
    hash_node* aux = ht->table[h];
    while (aux != NULL) {
        if (*(unsigned char*) aux->key == key) {
            return aux->frequency;
        }
        aux = aux->next;
    }
    return -1;
}

hash_node* add_on_hash(hash_node* head, lli frequency, unsigned char key) {
    hash_node* new_node = (hash_node*) malloc(sizeof(hash_node));
    new_node->next = head;
    new_node->frequency = frequency;
    
    unsigned char* aux = (unsigned char*) malloc(sizeof(unsigned char));
    *aux = key;
    new_node->key = aux;
    
    memset(new_node->new_mapping, -1, sizeof(new_node->new_mapping));
    return new_node;
}

void put (hash_table *ht, unsigned char key, lli frequency) {
    int h = (int) key;
    ht->table[h] = add_on_hash(ht->table[h], frequency, key);
    return;
}

hash_table* create_hash_table () {
    hash_table *new_hash_table = (hash_table*) malloc (sizeof(hash_table));
    for (int i = 0; i < HASH_SIZE; i++) {
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}