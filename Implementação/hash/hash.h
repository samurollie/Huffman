#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HASH_SIZE 256

typedef struct hash_table hash_table;
typedef struct hash_node hash_node;
typedef long long int lli;

struct hash_node {
    hash_node* next;
    unsigned char key;
    lli frequency;
    int new_mapping[9];
};

struct hash_table {
    hash_node *table[HASH_SIZE];
};

/** @param  ht: Hash Table utilizada para busca */
/** @param key: item a ser procurado*/
/** @return retorna verdadeiro caso o item pertença à ht e falso caso contrário*/
int contains_key(hash_table *ht, unsigned char key);

/** @param head: ponteiro para uma queuea encadeada de um hash table a ser impressa*/
void print_linked_queue(hash_node* head);

/** @param ht: ponteiro para uma hash a ser impressa*/
void print_hash_table(hash_table *ht);

/** @param  ht: hash table a ser manipulada para remoção*/
/** @param key: valor a ser removido*/
void remove_value(hash_table *ht, unsigned char key);

/** @param  ht: hash table a ser manipulada para busca*/
/** @param key: valor a ser procurado*/
/** @return retorna a frequência do valor a ser procurado, caso ele exista, e -1 caso contrário */
int get(hash_table *ht, unsigned char key);

/** @param  head:     ponteiro para a cabeça da hash table a ser manipulada para inserção na posição key*/
/** @param frequency: frequência do elemento a ser inserido*/
/** @param key:       posição de inserção*/
/** @return retorna o novo nó a ser adicionado na hash*/
hash_node* add_on_hash(hash_node* head, lli frequency, unsigned char key);

/** @param  ht:        ponteiro para hash table a ser manipulada para inserção*/
/** @param  key:       elemento de inserção*/
/** @param  frequency: frequência do elemento a ser inserido*/
void put (hash_table *ht, unsigned char key, lli frequency);

/** @return retorna uma hash table vazia */
hash_table* create_hash_table ();

#endif
