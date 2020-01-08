#include "../list/list.h"
#include "../hash/hash.h"
#include <string.h>

/*void remove_head(list* list) {
  node* aux = NULL;
  aux = list->head;
  list->head = aux->next; //hmm, o correto seria fazer oq?
  free(aux); 
  list->size--; 
}*/

void print_tree (node* tree) {
	if(tree ==  NULL) {
		return;
	}
	printf("Caracter: %c, frequencia: %d\n", tree->item, tree->frequency);
	print_tree(tree->left);
	print_tree(tree->right);
}

void print_on_file (FILE *f, node* tree) {
	if (tree == NULL) {
		return;
    }
  	fprintf(f, "%c", tree->item);
  	print_on_file(f, tree->left);
  	print_on_file(f, tree->right);
}

node *create_node(node *head, lli frequency, unsigned char item, list *list){
	node *new_node = (node*) malloc(sizeof(node));
    new_node->frequency = frequency;
    new_node->item = item;
    new_node->left = list->head;
    new_node->right = list->head->next;
    list->head = list->head->next->next;
    new_node->left->next = NULL;
    new_node->right->next = NULL;
    new_node->next = NULL;
    return new_node;
}

// Serve para juntar dois nós da lista, criando um pai pra eles;
node* join(list* list) { 
  	node* father = NULL; // Cria um nó
    lli frequency = list->head->frequency + list->head->next->frequency; // Soma a frequencia dos dois primeiros nós da lista;
    unsigned char id = '*'; // O item que eu devo salvar pra indicar que é um nó interno
  	father = create_node(father, frequency, id, list); // Adiciono tudo ao novo nó;
  	list->size--;
  	list->size--;
  	return father;
} 

// Constroi a árvore de Huffman
node* build_tree (list *mylist) {
  while(mylist->size > 1) { 
  	node* father = join(mylist);
    insert(mylist, father);
    /* print_list(mylist->head);
    printf ("TAMANHO DA LISTA: %d\n", mylist->size);
    printf("AQUI\n"); */
  }
  node *huff_tree = mylist->head;
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