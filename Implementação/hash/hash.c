#include "hash.h"

// Verifica se ja foi adicionado um valor com aquela chave, retornando 1 se for encontrado e 0 caso contrario;
int contains_key(hash_table *ht, unsigned char key) {
    int h = (int) key;
    hash_node* aux = ht->table[h];
    while (aux != NULL) {
        if (*(unsigned char*) aux->key == key) return 1; 
        aux = aux->next;
    }
    return 0;
}

// Imprime uma queuea encadeada;
void print_linked_queue (hash_node* head) {
    while (head != NULL) {
        printf ("Chave: %c, Frequencia: %lld ", *(unsigned char*) head->key, head->frequency);
        head = head->next;
    }
    printf ("\n");
}

// Imprime uma hash table;
void print_hash_table(hash_table *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (ht->table[i] != NULL) {
            printf("Posicao %d: ", i);
            print_linked_queue(ht->table[i]);
        }
    }
}

// Remove um valor na hash_table;
void remove_value(hash_table *ht, unsigned char key) {
    int h = (int) key;
    hash_node* aux = ht->table[h];
    hash_node* previous = NULL;
    while (aux != NULL) {
        if (*(unsigned char*) aux->key == key) {
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

// Adiciona um novo valor na hash table;
void put (hash_table *ht, unsigned char key, lli frequency) {
    int h = (int) key; // Esse aqui que e o meu calculo que diz qual vai ser a posição no array que eu vou adicionar o elemento  
    ht->table[h] = add_on_hash(ht->table[h], frequency, key);
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