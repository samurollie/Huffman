#include <CUnit/CUnit.h>
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include "../queue/queue.h"

int init_suite(void) {
    return 0; 
}

int clean_suite(void) { 
    return 0; 
}

void test_hash(void) {
    hash_table *hash = create_hash_table();
    CU_ASSERT_PTR_NOT_NULL(hash);
    for (int i = 0; i < HASH_SIZE; i++) {
        CU_ASSERT_PTR_NULL(hash->table[i]);
    }

    put(hash, 'A', 6);
    CU_ASSERT(contains_key(hash, 'A') == 1); // se esse valor já foi adicionado, retorna 1;
    CU_ASSERT(contains_key(hash, 'B') == 0); //ira retornar zero, pois ainda não foi adicionado.
    put(hash, 'B', 5);
    CU_ASSERT(contains_key(hash, 'B') == 1);
    put(hash, 'C', 4);
    put(hash, 'D', 3);
    put(hash, 'E', 2);
    put(hash, 'F', 1);

    CU_ASSERT(get(hash, 'A') != -1);
    CU_ASSERT(get(hash, 'A') == 6);
    CU_ASSERT(hash->table['A']->frequency == 6);

    CU_ASSERT(get(hash, 'B') != -1);
    CU_ASSERT(get(hash, 'B') == 5);
    CU_ASSERT(hash->table['B']->frequency == 5);

    CU_ASSERT(get(hash, 'C') != -1);
    CU_ASSERT(get(hash, 'C') == 4);
    CU_ASSERT(hash->table['C']->frequency == 4);

    CU_ASSERT(get(hash, 'D') != -1);
    CU_ASSERT(get(hash, 'D') == 3);
    CU_ASSERT(hash->table['D']->frequency == 3);

    CU_ASSERT(get(hash, 'E') != -1);
    CU_ASSERT(get(hash, 'E') == 2);
    CU_ASSERT(hash->table['E']->frequency == 2);

    CU_ASSERT(get(hash, 'F') != -1);
    CU_ASSERT(get(hash, 'F') == 1);
    CU_ASSERT(hash->table['F']->frequency == 1);

    CU_ASSERT(get(hash, 'G') == -1);
    CU_ASSERT_PTR_NULL(hash->table['G']);

    CU_ASSERT(get(hash, 'H') == -1);
    CU_ASSERT_PTR_NULL(hash->table['H']);

    CU_ASSERT(get(hash, 'I') == -1);
    CU_ASSERT_PTR_NULL(hash->table['I']);

    remove_value(hash, 'A');
    remove_value(hash, 'B');
    remove_value(hash, 'C');
    CU_ASSERT(get(hash, 'A') == -1); // após removido, essa key não deve ser encontrada.
    CU_ASSERT(get(hash, 'B') == -1);
    CU_ASSERT(get(hash, 'C') == -1);

}

void test_tree(void) {
    queue *queue = create_queue();
    add_on_queue(queue, 'A', 6);
    add_on_queue(queue, 'B', 5);
    add_on_queue(queue, 'C', 4);
    add_on_queue(queue, 'D', 3);
    add_on_queue(queue, 'E', 2);
    add_on_queue(queue, 'F', 1);

    node *tree = build_tree(queue);
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT(tree->frequency == 21);
    CU_ASSERT(tree->item == '*');

    FILE *arq = fopen("test.txt", "w");
    print_tree_on_file(arq, tree);
    unsigned char caracter;
    int i;
    for(i = 0; i < 2; i++) {
        fscanf(arq, "%c", &caracter);
    }
    while(fscanf(arq, "%c", &caracter) != EOF) {
        if (i == 2) {
            CU_ASSERT(caracter == '*');
            i += 1;
        } else if (i == 3) {
            CU_ASSERT(caracter == 'C');
            i += 1;
        } else if (i == 4) {
            CU_ASSERT(caracter == 'B');
            i += 1;
        } else if (i == 5) {
            CU_ASSERT(caracter == '*');
            i += 1;
        } else if (i == 6) {
            CU_ASSERT(caracter == '*');
            i += 1;
        } else if (i == 7) {
            CU_ASSERT(caracter == '*');
            i += 1;
        } else if (i == 8) {
            CU_ASSERT(caracter == 'F');
            i += 1;
        } else if (i == 9) {
            CU_ASSERT(caracter == 'E');
            i += 1;
        } else if (i == 10) {
            CU_ASSERT(caracter == 'B');
            i += 1;
        } else if (i == 11) {
            CU_ASSERT(caracter == 'A');
            i += 1;
        }
    }
}

void test_queue(void) {
    queue *queue = create_queue();
    CU_ASSERT_PTR_NOT_NULL(queue); // verifica se a queue não é NULL.
    CU_ASSERT(queue->size == 0); // verifica se o tamanho é zero.

    add_on_queue(queue, 'A', 6); // nessa função criamos um nó e enfileiramos ordenadamente.
    CU_ASSERT(queue->head->item == 'A');
    add_on_queue(queue, 'B', 5);
    CU_ASSERT(queue->head->item == 'B');
    add_on_queue(queue, 'C', 4);
    CU_ASSERT(queue->head->item == 'C');
    add_on_queue(queue, 'D', 3);
    CU_ASSERT(queue->head->item == 'D');
    add_on_queue(queue, 'E', 2);
    CU_ASSERT(queue->head->item == 'E');
    add_on_queue(queue, 'F', 1);
    CU_ASSERT(queue->head->item == 'F');

    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(NULL == dequeue(queue));
}

int main () {
    CU_pSuite pSuite = NULL; // cria a variavel do tipo CU_pSuite.
    
    /* Se essa função não conseguir inicializar, retorna um erro.
    Caso consiga ela retorna a variavel CUE_SUCCESS. */
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite); // cria a suite.
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Se suite fosse uma fila, poderia dizer que a função
    CU_add_on_queue_test enfileira um caso de teste */
    if((CU_add_test(pSuite, "\n\nTesting Queue Functions...\n\n", test_queue) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((CU_add_test(pSuite, "\n\nTesting Tree...\n\n", test_tree) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if((CU_add_test(pSuite, "\n\nTesting Hash...\n\n", test_hash) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

// Para compilar : make -B test
// o "-B" força a compilação.
