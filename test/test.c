#include <CUnit/CUnit.h>
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include "../list/list.h"

void test_create_list(void) {
    CU_ASSERT_PTR_NOT_NULL(create_list());
}

int main () {
    CU_pSuite pSuite = NULL; // cria a variavel do tipo CU_pSuite.


    /* Se essa função não conseguir inicializar, retorna um erro.
    Caso consiga ela retorna a variavel CUE_SUCCESS. */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite);

    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
}