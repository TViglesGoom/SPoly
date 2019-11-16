#include "../headers/SPoly.h"
#define KEY1 35
#define KEY2 54
#define KEY3 2

int test_insert(Poly *poly) {
    insert(KEY1, 5, poly);
    insert(KEY2, -8, poly);
    insert(KEY3, 3, poly);
    return 0;
}

int test_search(Poly *poly) {
    Poly *temp = NULL;
    temp = search(KEY1, poly);
    if (temp != NULL) {
//        printf("%d, %d\n", temp->key, temp->data);
    } else {
        return -3;
    }
    temp = search(KEY2, poly);
    if (temp != NULL) {
//        printf("%d, %d\n", temp->key, temp->data);
    } else {
        return -3;
    }
    temp = search(KEY3, poly);
    if (temp != NULL) {
//        printf("%d, %d\n", temp->key, temp->data);
    } else {
        return -3;
    }
    temp = search(45, poly);
    if (temp == NULL) {
//        printf("NULL passed\n");
    } else {
        return -4;
    }
    return 0;
}
