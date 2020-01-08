#include "../list/list.h"
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include <string.h>

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
    
    FILE *compressed_file = fopen("compressed.huff", "w");
    if (compressed_file ==  NULL) {
      printf ("Não foi possível comprimir o arquivo\n");
    }

    print_on_file(compressed_file, huff_tree);
    return 0;
}