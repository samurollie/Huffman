#include "../queue/queue.h"
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include "../files/files.h"
#include <string.h>

void search_huff_tree (node* tree, unsigned char item, int path[], int i, int* found) {
	if (tree == NULL) {
		if (*found != 1) path[i + 1] = -1;
		return;
	} else if (is_leaf(tree) && tree->item == item) {
		*found = 1;
		return;
	}
	if(*found != 1) {
	  path[i] = 0;
	} 	
	search_huff_tree(tree->left, item, path, i - 1, found);
	if(*found != 1) {
	  path[i] = 1;
	}
	search_huff_tree(tree->right, item, path, i - 1, found);
	if (*found != 1) path[i + 1] = -1;
}

void dec_to_bin(int beggin, int rest, int array[], int i) { // passar resto = 0;
	if(beggin >= 1) { 
		rest = beggin % 2;
		beggin = beggin / 2;
		dec_to_bin(beggin, 0, array, i+1);
		printf ("%d", rest);
		array[i] = rest;
	}
}

void get_number_of_nodes(node* tree, int* size) { // vai contar o numero de nós da arvore.
	if (tree == NULL) {
		return;
	}
	if (is_leaf(tree) == 1 && (tree -> item == '*' || tree -> item == '\\')) {
		(*size)++;
	}
	(*size)++;
	get_number_of_nodes(tree->left, size);
	get_number_of_nodes(tree->right, size);
}

// Calcula quantos bits o caracter ocupa no novo mapeamento
int changed_positions(int array[], int size) {
	int total = 0;
	  for(int i = 0; i < size; i++) {
		if (array[i] != -1) {
			total++;
		}
	}
	return total;
}

void print_bits(FILE *file, FILE *compressed_file, hash_table *mapping, int trash_size) {
	unsigned char c; // ok
	unsigned char byte = 0; // ok
	int i = 0; // ok
	while (fscanf (file, "%c", &c) != EOF) { // ok
		int h = (int) c; // ok
		int n = changed_positions (mapping->table[h]->new_mapping, 9); // ok;
		for(int j = 8; j >= 9 - n; j--) {
			if (i == 8) { // Completei um byte! :)
				fprintf(compressed_file, "%c", byte);
				byte = 0;
				i = 0;
			}

			if (mapping->table[h]->new_mapping[j] == 1) {
				// printf("aq\n");
				byte = set_bit(byte, 0);
			}
			if (i < 7) byte <<= 1;
			i++;
		}
	}
	byte >>= 1; // por causa do ultimo loop;
	byte <<= trash_size;
	fprintf(compressed_file, "%c", byte);
}

int get_trash_size(hash_table *mapping) {
	int i;
	int bits_usados = 0;
	for (i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) { // Tenho que multiplicar quantos bits um unico caracter daquele ocupa pela quantidade de vezes que ele aparece no texto
			int n = changed_positions(mapping->table[i]->new_mapping, 9);
			int m = mapping->table[i]->frequency;
			bits_usados += n * m; 
		}
	}
	return (8 - (bits_usados % 8) == 8 ? 0 : 8 - (bits_usados % 8));
}

void get_frequency(FILE *file, hash_table *mapping) {
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

int main() {
	char file_path[5000];
	printf("Digite o caminho para o arquivo que deseja comprimir: ");
	scanf ("%s", file_path);
	
	FILE *arq; 
	arq = open_file(file_path);
	if (arq == NULL) {
		printf ("Arquivo não encontrado\n");
	  	return 0;
	}
	
	hash_table* mapping = create_hash_table();
	get_frequency(arq, mapping);

	queue *myqueue = create_queue();
	for (int i = 0; i < 256; i++) {
		if (mapping->table[i] != NULL) {
			myqueue = add(myqueue, mapping->table[i]->key, mapping->table[i]->frequency);
		}
	}
	node *huff_tree = build_tree(myqueue);
	
	fclose(arq);
	arq = open_file(file_path);

	strcat(file_path, ".huff");
	FILE *compressed_file = fopen(file_path, "w"); // cria um arquivo e permite a escrita nele.
	if (compressed_file ==  NULL) {
	  printf ("Não foi possível comprimir o arquivo\n");
	  return 0;
	}
	
	for (int i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) {
			int path[9];
			memset(path, -1, sizeof(path));
			unsigned char item = mapping->table[i]->key;
			int found = 0;
			search_huff_tree(huff_tree, item, path, 8, &found);	

			for(int e = 0; e < 9; e++) {
				mapping->table[i]->new_mapping[e] = path[e];
			}
		}
	}

	//agora vamos escrever todos os bytes no arquivo, bit a bit;
	int tree_size = 0;
	get_number_of_nodes(huff_tree, &tree_size);

	int trash_size = get_trash_size(mapping);

	int array[16];
	memset(array, 0, sizeof(array)); 

	printf ("Tamanho da árvore: %d (", tree_size);
	dec_to_bin(tree_size, 0, array, 0);
	printf (")\n");
	
	printf("Tamanho do lixo: %d (", trash_size);
	dec_to_bin(trash_size, 0, array, 13);
	printf (")\n");
	  
	unsigned char c = 0, d = 0;
	  for (int i = 16 - 1; i >= 0; i--) {
		if (i >= 8) { // Salvo em um dos bytes;
			if (array[i] == 1) {
				c = set_bit(c, i - 8);
			}
		} else { // Salva no outro byte;
			if (array[i] == 1) {
				d = set_bit(d, i);
			}
		}
	}

	  fprintf(compressed_file, "%c", c);
	  fprintf(compressed_file, "%c", d);
	print_on_file(compressed_file, huff_tree); // função que imprimi a arvore no arquivo.
	
	print_bits(arq, compressed_file, mapping, trash_size); 
  
	return 0;
}