#include "../headers/SPoly.h"

int test_insert(struct DataItem **poly) {
    insert(35, 5, poly);
    insert(55, -8, poly);
    insert(0, 3, poly);
    return 0;
}

int test_search(struct DataItem **poly) {
    struct DataItem *temp = NULL;
    temp = search(35, poly);
    if (temp != NULL) {
//        printf("%d, %d\n", temp->key, temp->data);
    } else {
        return -3;
    }
    temp = search(55, poly);
    if (temp != NULL) {
//        printf("%d, %d\n", temp->key, temp->data);
    } else {
        return -3;
    }
    temp = search(0, poly);
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

int test_delete(struct DataItem **poly) {
    struct DataItem* item = search(35, poly);
    delete(item, poly); // deleting existing item
    delete(item, poly); // deleting not existing item
    item = search(35, poly);
    delete(item, poly); // deleting NULL
    if (item != NULL) {
        return -5;
    }
    return 0;
}