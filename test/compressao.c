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
      	if (*found != 1) path[i + 1] = -1;
      	return;
    } else if (is_leaf(tree) && tree->item == item) {
  		printf("ACHEI!\n");
      	*found = 1;
		return;
    }
  	printf("Estou no nó %c\n", tree->item);
  	if(*found != 1) {
	  printf("if 1: (I): %d de (%c)\n", i,item);
      path[i] = 0;
	} 	
	search_huff_tree(tree->left, item, path, i - 1, found);
    if(*found != 1) {
      printf("if 2: (I): %d de (%c)\n", i,item);
      path[i] = 1;
    }
  	search_huff_tree(tree->right, item, path, i - 1, found);
    if (*found != 1) path[i + 1] = -1;
}

void dec_to_bin(int beggin, int rest, int array[], int i) { // passar resto = 0;
	if(beggin >= 1) { // ?????????? ke???
    	rest = beggin % 2;
    	beggin = beggin / 2;
    	// printf ("i ::: %d\n", i);
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
	// for (int i = 0; i < HASH_SIZE; i++) {
	// 	if (mapping->table[i] != NULL) {
	// printf("Posicao %d: ", i);
	// printf("Chave: %c, Frequencia: %lld, ", mapping->table[i]->key, mapping->table[i]->frequency);
	// printf("Novo mapeamento: ");
	// for (int x = 0; x < 8; x++) {
	// 			printf("%d ", mapping->table[i]->new_mapping[x]);
	// }
	// printf("\n");
	// }
	// }
    	unsigned char unit; //okay
    int i = 0; //okay
  	unsigned char c = 0; //okay
  	while (fscanf(file, "%c", &unit) != EOF) {	
      	printf("UNIT: %c\n", unit);
    	int h = (int) unit; //tá dando certo
      	int n = changed_positions(mapping->table[h]->new_mapping, 8);
      
      	for (int j = 0; j < n; j++) {
          if (i == 8) {
            for (int x = 7; x >= 0; x--) {
				printf("%d", (is_bit_i_set(c, x) == 0) ? 0 : 1);
            }
            printf("\n");
			fprintf(compressed_file, "%c", c);
            c = 0;
            i = 0;
          }
          printf("i = %d\n", i);
          printf("mapping do %c(%d) :\n", h, unit);
          for (int kkk = 0; kkk < 8; kkk++) {
			printf("%d ", mapping->table[h]->new_mapping[kkk]);
          }
           printf("\n");
          if (mapping->table[h]->new_mapping[j] == 1) {
            c = set_bit(c, i);
          }
          i++;
        }
    }
  	c <<= trash_size; //deslocar os bits à esquerda de acordo com o tamanho do lixo
    fprintf(compressed_file, "%c", c);
	
    for (int x = 7; x >= 0; x--) {
        printf("%d", (is_bit_i_set(c, x) == 0) ? 0 : 1);
    }
    printf("\n");
}

int get_trash_size(hash_table *mapping) {
	int i;
  	int bits_usados = 0;
  	for (i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) { // Tenho que multiplicar quantos bits um unico caracter daquele ocupa pela quantidade de vezes que ele aparece no texto
          bits_usados += changed_positions(mapping->table[i]->new_mapping, 8);
          printf("Bits usados pelo %c: %d\n", mapping->table[i]->key, changed_positions(mapping->table[i]->new_mapping, 8));
          bits_usados *= mapping->table[i]->frequency;
          printf("BITS USADOS (TOTAL): %d\n", bits_usados);
        }
    }
  printf("RESULTADO FINAL: %d\n", bits_usados);
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
    // print_tree(huff_tree, 0);
    
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
		  	search_huff_tree(huff_tree, item, path, 7, &found);	
            // mapping->table[i]->new_mapping = path;
          	for(int e = 0; e < 8; e++)
            {
              mapping->table[i]->new_mapping[e] = path[e];
            }
          	
          	printf ("O caminho para o %c: ", item);
            for (int x = 0; x < 8; x++) {
                printf ("%d ", mapping->table[i]->new_mapping[x]);
            }
            printf ("\n");
        }
    }
  
  	/* for (int i = 0; i < HASH_SIZE; i++) {
		if (mapping->table[i] != NULL) {
        	printf("Posicao %d: ", i);
          	printf("Chave: %c, Frequencia: %lld, ", mapping->table[i]->key, mapping->table[i]->frequency);
          	printf("Novo mapeamento: ");
          	for (int x = 0; x < 8; x++) {
				printf("%d ", mapping->table[i]->new_mapping[x]);
            }
          	printf("\n");
        }
    } */

  	//agora vamos escrever todos os bytes no arquivo, bit a bit;
  	int tree_size = 0;
  	get_number_of_nodes(huff_tree, &tree_size);
  	printf ("Tamanho da árvore: %d\n", tree_size);

    int trash_size = get_trash_size(mapping);
    printf("Tamanho do lixo: %d\n", trash_size);

  	int array[16];
  	memset(array, 0, sizeof(array));  // 
    
    printf ("Tamanho da árvore em binario: ");
  	dec_to_bin(tree_size, 0, array, 0);
    printf ("\n");
    
    printf ("Tamanho do lixo em binario: ");
  	dec_to_bin(trash_size, 0, array, 13);
    printf ("\n");
  	
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
	
    fclose(arq);
    arq = open_file(file_path);
    print_bits(arq, compressed_file, mapping, trash_size); 
  
    return 0;
}