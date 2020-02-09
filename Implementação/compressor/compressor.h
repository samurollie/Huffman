#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "../queue/queue.h"
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include "../bits/bits.h"
#include <string.h>

/** @param tree:     árvore na qual se deseja buscar um item. */
/** @param item:     o caracter que está sendo procurado. */
/** @param path:     array com o novo mapeamento. */
/** @param i   :     indice do array. */
/** @param found:    variavel que indica se o item foi ou não encontrado. */
void search_huff_tree (node* tree, unsigned char item, int path[], int i, int* found);

/** @param number:   número que deseja tranformar em binário.*/
/** @param rest:     guarda o resto da divisão. */
void dec_to_bin(int number, int rest);

/** @param tree:    arvore da qual vamos contar a quantidade de nós. */
/** @param size:    tamanho da arvore. */
void get_number_of_nodes(node* tree, int* size);

/** @param mapping:   hash table que irá guardar o novo mapeamento. */
/** @param huff_tree: arvore que vai ser percorrida para o criar o mapeamento. */
void get_new_mapping(hash_table *mapping, node* huff_tree);

/** @param array:    array com o novo mapeamento. */
/** @return a quantidade de bits ocupados pelo caracter no novo mapeamento. */
int mapping_size(int array[]);

/** @param file:             arquivo original. */
/** @param compressed_file:  arquivo compactado. */
/** @param mapping:          hash table contendo o novo mapeamento. */
/** @param trash_size:       tamanho do lixo para imprimir o cabeçalho. */
void print_bits(FILE *file, FILE *compressed_file, hash_table *mapping, int trash_size);

/** @param mapping:     hash table contendo o novo mapeamento e a frequencia dos caracteres*/
/** @return:            O tamanho do lixo*/
int get_trash_size(hash_table *mapping);

/** @param file:    arquivo original. */
/** @param mapping: hash table que vai salvar a frequencia dos caracteres. */
void get_frequency(FILE *file, hash_table *mapping);

/** @param mapping: mapeamento que será impresso. */
void print_new_mapping(hash_table *mapping);

/** @param mapping:  hash table contendo os caracteres e suas frequências. */
/** @param queue:    fila de prioridade que vai ser construida a partir da hash. */
/** @return: A fila de prioridade. */
queue *create_queue_from_hash(hash_table *mapping, queue *queue);

void compress();

#endif