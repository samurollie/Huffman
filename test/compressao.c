#include "../list/list.h"
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include <string.h>

unsigned char set_bit(unsigned char c, int i) { // essa função transforma o zero em um.
	  unsigned char mask = 1 << i;	
	  return mask | c;
}

int is_bit_i_set(unsigned char c, int i) { // verifica se o int i é igual a um.
	  unsigned char mask = 1 << i;
	  return mask & c;
}

void search_huff_tree (node* tree, unsigned char item, int path[], int i, int* found) {
	if (tree == NULL) {
      	return;
    } else if (tree->item == item) {
      *found = 1;
		return;
    }
    if(*found != 1){
      path[i] = 1;
    }
  	search_huff_tree(tree->right, item, path, i++, found);
    if(*found != 1) {
      path[i] = 0;
    } 	
  	search_huff_tree(tree->left, item, path, i++, found);
}

void dec_to_bin(int beggin, int rest, int array[], int i) { // passar resto = 0;
  if(beggin >= 2) { // ?????????? ke???
    rest = beggin % 2;
    beggin = beggin / 2;
    dec_to_bin(beggin, 0, array, i++);
    array[i] = rest;
  }
}

void get_number_of_nodes(node* tree, int* size) { // vai contar o numero de nós da arvore.
	if (tree == NULL) {
		return;
    }
  	(*size)++;
  	get_number_of_nodes(tree->left, size);
  	get_number_of_nodes(tree->right, size);
}

int changed_positions(int array[], int size) {
	int total = 0;
  	for(int i = 0; i < size; i++) {
		if (array[i] != -1) {
			total++;
        }
    }
  return total;
}

void print_bits(FILE *file, FILE *compressed_file, hash_table *mapping) {
	unsigned char unit;
  	int aux[8], i = 0;
    memset(aux, -1, sizeof(aux));
  	while (fscanf(file,"%c",&unit) != EOF) {
        printf("AQUI\n");
		int h = (int) unit;
      	int n = changed_positions(mapping->table[h]->new_mapping, 8);
      	for (int j = 0; j < n; j++, i++) {
			aux[i] = mapping->table[h]->new_mapping[j];
        }
      	if (i == 8) {
            unsigned char c = 0;
          	for (int j = 0; j < 8; j++) {
				if (aux[j] == 1) {
					c = set_bit(c, j); //mudando os bits pra 1 de acordo com o mapeamento do array.
                }
            }
          	fprintf(compressed_file, "%c", c);
        }
  	}
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

FILE *open_file(char* path) {
    FILE *f = fopen(path, "r");
    return f;
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
    print_hash_table(mapping);

    list *mylist = create_list();
    for (int i = 0; i < 256; i++) {
        if (mapping->table[i] != NULL) {
            mylist = add(mylist, mapping->table[i]->key, mapping->table[i]->frequency);
        }
    }
    print_list(mylist->head);
    
    node *huff_tree = build_tree(mylist);
    print_tree(huff_tree);
    
    FILE *compressed_file = fopen("compressed.huff", "w"); // cria um arquivo e permite a escrita nele.
    if (compressed_file ==  NULL) {
      printf ("Não foi possível comprimir o arquivo\n");
      return 0;
    }
      	
  	for (int i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) {
          	int path[8];
          	memset(path, -1, sizeof(path));
          	unsigned char item = mapping->table[i]->key;
          	int found = 0;
		  	search_huff_tree(huff_tree, item, path, 0, &found);	
            /* // array path = 1 0 1 -1 -1 -1 -1 -1 
          	// unsigned char = 0 0 0 0 0 0 0 0
          	// após chamar a função set_bit, unsigned char = 0 0 0 0 0 1 0 1 :::: Deve ser printado no arquivo.
          	unsigned char c = 0;
          	for (int j = 0; j < 8; j++) {
				if (path[j] == 1) {
					c = set_bit(c, j); //mudando os bits pra 1 de acordo com o mapeamento do array.
                }
            } */
          	//salvando o que vai ser ptintado na hash table
          	mapping->table[i]->new_mapping = path;
        }
    }
  	//agora vamos escrever todos os bytes no arquivo, bit a bit;
  	int tree_size = 0;
  	get_number_of_nodes(huff_tree, &tree_size);
  	int trash_size = tree_size - 16;
  	int array[16];
  	memset(array, 0, sizeof(array));
  	dec_to_bin(tree_size, 0, array, 0);
  	dec_to_bin(trash_size, 0, array, 13);
  	
  	unsigned char c = 0, d = 0;	
  	for (int i = 0; i < 16; i++) {
		if (i < 8) { // Salvo em um dos bytes;
			if (array[i] == 1) {
				c = set_bit(c, i);
            }
        } else { // Salva no outro byte;
			if (array[i] == 1) {
				d = set_bit(d, i - 8);
            }
        }
    }

  	fprintf(compressed_file, "%c", d);
  	fprintf(compressed_file, "%c", c);
    print_on_file(compressed_file, huff_tree); // função que imprimi a arvore no arquivo.
	print_bits(arq, compressed_file, mapping);
  	
    return 0;
}