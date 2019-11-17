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
    Poly* temp = unsub(poly);
    IType degree;
    display(temp);
    for (IType c = 0; c < poly->count; c++) {
        degree = poly->sortedDegrees[c];
        printf("%.1f, ", search(degree, temp)->coefficient);
    }
    return 0;
}
