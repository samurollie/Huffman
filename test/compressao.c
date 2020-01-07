#include "../list/list.h"
#include "../hash/hash.h"
#include <string.h>

void remove_head(list* list) {
  node* aux = list->head;
  list->head = aux->next;
  free(aux); 
  list->size--; 
}

node *create_node(node *head, lli frequency, unsigned char item, list *list){
  node *new_node = (node*) malloc(sizeof(node));
  new_node->frequency = frequency;
  new_node->item = item;
  new_node->left = list->head;
  new_node->right = list->head->next;
  new_node->next = NULL;
  return new_node;
}

// Serve para juntar dois nós da lista, criando um pai pra eles;
node* join(list* list) { 
  	node* father = NULL; // Cria um nó
    lli frequency = list->head->frequency + list->head->next->frequency; // Soma a frequencia dos dois primeiros nós da lista;
    unsigned char id = '*'; // O item que eu devo salvar pra indicar que é um nó interno
  	father = create_node(father, frequency, id, list); // Adiciono tudo ao novo nó;
    father->next = father->right->next;
  	remove_head(list);
  	remove_head(list);
 		return father;
} 

// Constroi a árvore de Huffman
list* build_tree (list *mylist) {
  list* huff_tree = create_list(); 
  while(mylist->size >= 1) { 
  	node* father = join(mylist);
  	insert(mylist, father);
  }
  return huff_tree;
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
    FILE *arq; 
    arq = open_file("../a.txt");
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
    
    list *huff_tree = build_tree(mylist);
    printf("%d\n", huff_tree->head->frequency);
    return 0;
}