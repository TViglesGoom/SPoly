#include "headers/common.h"
#include "headers/SPoly.h"
#include "tests/test_SPoly.h"


int main() {
    Poly *poly1 = createNewPoly(4);
    printf("test insert - %d\n", test_insert(poly1));
    printf("test search - %d\n", test_search(poly1));
    display(poly1);
    Poly* poly2 = generate(6, 4);
    display(poly2);
    printf("test add - %d\n", test_add(poly1, poly2));
    printf("test unsub - %d\n", test_unsub(poly1));

    return 0;
}