#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

int contains_key(hash_table *ht, unsigned char key);
void print_linked_list(hash_node* head);
void print_hash_table(hash_table *ht);
void remove_value(hash_table *ht, unsigned char key);
int get(hash_table *ht, unsigned char key);
hash_node* add_node(hash_node* head, lli frequency, unsigned char key);
void put (hash_table *ht, unsigned char key, lli frequency);
hash_table* create_hash_table ();

#endif