#include "compressor.h"

#define DEBUG if(0)

void search_huff_tree (node* tree, unsigned char item, int path[], int i, int* found) {
	if (tree != NULL) {
		if (is_leaf(tree) && tree->item == item) {
			*found = 1;
			return;
		}

		if(*found != 1) {
			path[i] = 0;
			search_huff_tree(tree->left, item, path, i + 1, found);
		} 	
		
		if(*found != 1) {
			path[i] = 1;
			search_huff_tree(tree->right, item, path, i + 1, found);
		}
	}
	if (*found != 1) path[i - 1] = -1;
}

void dec_to_bin(int number, int rest) {
	if(number >= 1) { 
		rest = number % 2;
		number = number / 2;
		dec_to_bin(number, 0);
		printf ("%d", rest);
	}
}

void get_number_of_nodes(node* tree, int* size) { // vai contar o numero de nós da arvore.
	if (tree == NULL) {
		return;
	}
	if (is_leaf(tree) && (tree -> item == '*' || tree -> item == '\\')) {
		(*size)++;
	}
	(*size)++;
	get_number_of_nodes(tree->left, size);
	get_number_of_nodes(tree->right, size);
}

int mapping_size(int array[]) {
	int total = 0;
	  for(int i = 0; i < 9; i++) {
		if (array[i] != -1) {
			total++;
		}
	}
	return total;
}

void print_bits(FILE *file, FILE *compressed_file, hash_table *mapping, int trash_size) {
	unsigned char c; 
	unsigned char byte = 0; 
	int i = 0; 

	while (fscanf (file, "%c", &c) != EOF) { 
		int h = (int) c; 
		int n = mapping_size(mapping->table[h]->new_mapping);
	
		for(int j = 0; j < n; j++) {
			if (i == 8) { // Completei um byte! :)
				fprintf(compressed_file, "%c", byte);
				byte = 0;
				i = 0;
			}
	
			if (mapping->table[h]->new_mapping[j] == 1) {
				byte <<= 1;
				byte = set_bit(byte, 0);
			} else if (mapping->table[h]->new_mapping[j] == 0) {
				byte <<= 1;
			}
			i++; 
		}

		if (i == 8) { // Completei um byte! :)
			fprintf(compressed_file, "%c", byte);
			byte = 0;
			i = 0;
		}
	}
	
	byte <<= trash_size;
	fprintf(compressed_file, "%c", byte);
}

void get_new_mapping(hash_table *mapping, node* huff_tree) {
	for (int i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) {
			int path[9];
			memset(path, -1, sizeof(path));
			unsigned char item = *(unsigned char*) mapping->table[i]->key;
			int found = 0;
			// printf("i = %d\n", i);

			/* passa o i = 8, pois estamos preenchendo de tras pra frente. */
			search_huff_tree(huff_tree, item, mapping->table[i]->new_mapping, 0, &found);
		}
	}
}

int get_trash_size(hash_table *mapping) {
	int i;
	int bits_usados = 0;
	for (i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) { // Tenho que multiplicar quantos bits um unico caracter daquele ocupa pela quantidade de vezes que ele aparece no texto
			int n = mapping_size(mapping->table[i]->new_mapping);
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
			printf("aq na get_frequency\n");
		} else {
			mapping->table[h]->frequency++;
		}
	  }
}

void print_new_mapping(hash_table *mapping) {
	for (int  i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) {
			printf("%c = ", *(unsigned char*)mapping->table[i]->key);
			for (int j = 8; j >= 0; j--) {
				printf("%d ", mapping->table[i]->new_mapping[j]);
			}
			printf("\n");
		}
	}
}

queue *create_queue_from_hash(hash_table *mapping, queue *queue) {
	for (int i = 0; i < 256; i++) {
		if (mapping->table[i] != NULL) {
			queue = add_on_queue(queue,*(unsigned char*) mapping->table[i]->key, mapping->table[i]->frequency);
		}
	}
	return queue;
}

void compress() {
	FILE *arq;
	char file_path[5000];

	while (1) {
		printf("\nDigite o caminho para o arquivo que deseja comprimir:\n");
		scanf ("%[^\n]s", file_path);
		arq = fopen(file_path, "rb");
		if (arq == NULL) {
			printf("\nNão foi possivel encontrar o arquivo!\n");
			getchar();
		} else {
			break;
		}
	}
	
	hash_table* mapping = create_hash_table();
	get_frequency(arq, mapping);

	DEBUG printf("\nHASH TABLE::::: \n");
	DEBUG print_hash_table(mapping);
	DEBUG printf("\n");

	queue *myqueue = create_queue();
	myqueue = create_queue_from_hash(mapping, myqueue);

	node *huff_tree = build_tree(myqueue);
	DEBUG print_tree(huff_tree);
	
	rewind(arq);
	get_new_mapping(mapping, huff_tree);
	DEBUG print_new_mapping(mapping);

	int tree_size = 0;
	get_number_of_nodes(huff_tree, &tree_size);

	int trash_size = get_trash_size(mapping);

	DEBUG printf ("Tamanho da árvore: %d (", tree_size);
	DEBUG dec_to_bin(tree_size, 0);
	DEBUG printf (")\n");
	
	DEBUG printf("Tamanho do lixo: %d (", trash_size);
	DEBUG dec_to_bin(trash_size, 0);
	DEBUG printf (")\n");
	 
	printf("\nCompactando %s...\n", file_path);
	unsigned short int c = 0;
	c = trash_size;
	c <<= 13;
	c += tree_size;

	strcat(file_path, ".huff");
	FILE *compressed_file = fopen(file_path, "wb"); // cria um arquivo e permite a escrita nele.
	if (compressed_file == NULL) {
		printf ("Não foi possível compactar %s\n", file_path - 6);
		return;
	}
    fprintf(compressed_file, "%c%c", c >> 8, c);

	// printf(">>>>>>>\n");
	print_tree_on_file(compressed_file, huff_tree); // função que imprimi a arvore no arquivo.
	
	print_bits(arq, compressed_file, mapping, trash_size);
	fclose(compressed_file);
	fclose(arq);
	/*compressed_file = fopen(file_path, "r");
	unsigned char ch;
	int count = 0;
	while(fscanf(compressed_file, "%c", &ch) != EOF) {
		if(count < tree_size + 2) {
			count++;
			continue;
		}
		printar_byte(ch);
		printf("|");
	} */
	return;
}