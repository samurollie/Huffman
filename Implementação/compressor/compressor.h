#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "../queue/queue.h"
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include "../bits/bits.h"
#include <string.h>

void search_huff_tree (node* tree, unsigned char item, int path[], int i, int* found);
void dec_to_bin(int beggin, int rest, int array[], int i);
void get_number_of_nodes(node* tree, int* size);
int changed_positions(int array[], int size);
void print_bits(FILE *file, FILE *compressed_file, hash_table *mapping, int trash_size);
int get_trash_size(hash_table *mapping);
void get_frequency(FILE *file, hash_table *mapping);
void compress();

#endif