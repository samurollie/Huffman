#include "huff_tree.h"

int is_leaf(node *tree) {
  return !tree->left && !tree->right;
}

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
	if (is_leaf(tree)) {
		if (tree->item == '*' || tree->item == '\\') {
  			fprintf(f, "\\%c", tree->item);
		} else {
  			fprintf(f, "%c", tree->item);
		}
	} else {
  		fprintf(f, "%c", tree->item);
	}
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

node* join(list* list) { 
  	node* father = NULL; // Cria um nó
    lli frequency = list->head->frequency + list->head->next->frequency; // Soma a frequencia dos dois primeiros nós da lista;
    unsigned char id = '*'; // O item que eu devo salvar pra indicar que é um nó interno
  	father = create_node(father, frequency, id, list); // Adiciono tudo ao novo nó;
  	list->size--;
  	list->size--;
  	return father;
} 

node* build_tree (list *mylist) {
  while(mylist->size > 1) { 
  	node* father = join(mylist);
    insert(mylist, father);
  }
  node *huff_tree = mylist->head;
  return huff_tree;
}