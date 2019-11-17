#include "../headers/SPoly.h"
#define KEY1 35
#define KEY2 102
#define KEY3 0

#define VALUE1 5
#define VALUE2 -8
#define VALUE3 3

IType test_insert(Poly *poly) {
    insert(KEY1, VALUE1, poly);
    insert(KEY2, VALUE2, poly);
    insert(KEY3, VALUE3, poly);
    insert(9, -4.3, poly);
    return 0;
}

IType test_search(Poly *poly) {
    PolyElem *temp;
    temp = search(KEY1, poly);
    if (temp == NULL || temp->coefficient != VALUE1) {
        return -3;
    }
    temp = search(KEY2, poly);
    if (temp == NULL || temp->coefficient != VALUE2) {
        return -3;
    }
    temp = search(KEY3, poly);
    if (temp == NULL || temp->coefficient != VALUE3) {
        return -3;
    }
    temp = search(45, poly);
    if (temp != NULL) {
        return -4;
    }
    return 0;
}

IType test_add(Poly* poly1, Poly* poly2) {
    if (poly2->sortedDegrees[0] != 0) {
        insert(0, -3, poly2);
    }
    insert(KEY1, VALUE2, poly2);
    display(add(poly1, poly2));
    return 0;
}

IType test_unsub(Poly* poly) {
    display(unsub(poly));
    return 0;
}

IType test_sub(Poly* poly1, Poly* poly2) {
    display(sub(poly1, poly2));
    return 0;
}

IType test_mul() {
    Poly* poly1 = createNewPoly(2);
    Poly* poly2 = createNewPoly(3);
    insert(0, 3, poly1);
    insert(2, 2, poly1);
    insert(7, 4, poly2);
    insert(5, 3, poly2);
    insert(1, -9, poly2);
    printf("MULTIPLICATION TESTS\n");
    display(mul(poly1, poly2, 1));
    display(mul(poly1, poly2, 3));
    display(mul(poly1, poly2, -5));
    display(mul(poly2, NULL, -5));
    display(mul(NULL, NULL, -5));
    printf("\n\n");
}
