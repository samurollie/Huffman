/* /* //Função usada na hora de criar a lista.
list *add (list *list, unsigned char item, lli frequency, node* left, node* right){ //lembrar de colocar o parametro no resto do código onde ela foi chamada
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = item; 
    new_node -> frequency = frequency;
    new_node -> right = right;
    new_node -> left = left;
    insert(list, new_node);
    return list;
}


lli *get_frequency(FILE *file) {
    lli *repeticao = (lli*) malloc(sizeof(lli) * 256);
    memset(repeticao, 0, 256);
    unsigned char unit;
	while (fscanf(file,"%c",&unit) != EOF) { // vai até o EOF.
		int a = (int) unit;
		repeticao[a] += 1;
  	}
    return repeticao;
}

FILE *open_file(char* path) {
    FILE *f = fopen(path, "r");
    return f;
}

int main() {
    FILE *arq;
    arq = open_file("../a.txt");
    lli *frequency = get_frequency(arq);
    
    list *list = create_list();
    int i, size_list = 0;
    for (i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            list = add(list, 'a',frequency[i], NULL, NULL);
            size_list++;
        }
    }
    print_list(list->head);
    
    return 0;
} */