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
    put(hash, 'B', 5);
    put(hash, 'C', 4);
    put(hash, 'D', 3);
    put(hash, 'E', 2);
    put(hash, 'F', 1);

    CU_ASSERT(hash->table['A']->key == 'A');
    CU_ASSERT(hash->table['A']->frequency == 6);
    CU_ASSERT(hash->table['B']->key == 'B');
    CU_ASSERT(hash->table['B']->frequency == 5);
    CU_ASSERT(hash->table['C']->key == 'C');
    CU_ASSERT(hash->table['C']->frequency == 4);
    CU_ASSERT(hash->table['D']->key == 'D');
    CU_ASSERT(hash->table['D']->frequency == 3);
    CU_ASSERT(hash->table['E']->key == 'E');
    CU_ASSERT(hash->table['E']->frequency == 2);
    CU_ASSERT(hash->table['F']->key == 'F');
    CU_ASSERT(hash->table['F']->frequency == 1);
    CU_ASSERT(hash->table['G'] == NULL);

        
}

void test_tree(void) {
    queue *queue = create_queue();
    add(queue, 'A', 6);
    add(queue, 'B', 5);
    add(queue, 'C', 4);
    add(queue, 'D', 3);
    add(queue, 'E', 2);
    add(queue, 'F', 1);
    node *tree = build_tree(queue);
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT(tree->head->frequency == 21);
    CU_ASSERT(tree->head->item == '*');
    FILE *arq;
    *arq = fopen("test.txt", "w");
    print_tree_on_file(arq, tree);

    CU_ASSERT(getc(arq) == '*');
    CU_ASSERT(getc(arq) == '*');
    CU_ASSERT(getc(arq) == 'C');
    CU_ASSERT(getc(arq) == '*');
    CU_ASSERT(getc(arq) == 'D');
    CU_ASSERT(getc(arq) == '*');
    CU_ASSERT(getc(arq) == 'F');
    CU_ASSERT(getc(arq) == 'E');
    CU_ASSERT(getc(arq) == '*');
    CU_ASSERT(getc(arq) == 'B');
    CU_ASSERT(getc(arq) == 'A');
}

void test_queue(void) {
    queue *queue = create_queue();
    CU_ASSERT_PTR_NOT_NULL(queue); // verifica se a queue não é NULL.
    CU_ASSERT(queue->size == 0); // verifica se o tamanho é zero.

    add(queue, 'A', 6); // nessa função criamos um nó e enfileiramos ordenadamente.
    CU_ASSERT(queue->head->item == 'A');
    add(queue, 'B', 5);
    CU_ASSERT(queue->head->item == 'B');
    add(queue, 'C', 4);
    CU_ASSERT(queue->head->item == 'C');
    add(queue, 'D', 3);
    CU_ASSERT(queue->head->item == 'D');
    add(queue, 'E', 2);
    CU_ASSERT(queue->head->item == 'E');
    add(queue, 'F', 1);
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
    CU_add_test enfileira um caso de teste */
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
