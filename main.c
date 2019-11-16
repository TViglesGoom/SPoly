#include "headers/common.h"
#include "headers/SPoly.h"
#include "tests/test_SPoly.h"


int main() {
    Poly *poly1 = createNewPoly(5);
    printf("test insert - %d\n", test_insert(poly1));
    printf("test search - %d\n", test_search(poly1));
    display(poly1);
    return 0;
}