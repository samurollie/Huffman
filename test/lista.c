#include "../list/list.h"
#include "../hash/hash.h"
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
    FILE *arq; 
    arq = open_file("../a.txt");
    hash_table* mapping = create_hash_table();
    get_frequency(arq, mapping);
    print_hash_table(mapping);

    list *list = create_list();
    int i, size_list = 0;
    for (i = 0; i < 256; i++) {
        if (mapping->table[i] != NULL) {
            list = add(list, mapping->table[i]->key, mapping->table[i]->frequency);
            size_list++;
        }
    }
    print_list(list->head);
    
    return 0;
}