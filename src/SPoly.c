#include "../headers/SPoly.h"


IType hashCode(IType key) {
    return key % SIZE;
}

DataItem *search(IType key, DataItem **hashArray) {
    //get the hash
    IType hashIndex = hashCode(key);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {

        if(hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}

void insert(IType key, IType data, DataItem **hashArray) {

    DataItem *item = (DataItem*) malloc(sizeof(DataItem));
    item->data = data;
    item->key = key;

    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty or deleted cell
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= SIZE;

    }

    hashArray[hashIndex] = item;
}

void delete(DataItem* item, DataItem **hashArray) {
    if (item == NULL) {
        return;
    }
    int key = item->key;
    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key) {
            hashArray[hashIndex] = NULL;
        }
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= SIZE;
    }
}

void display(DataItem **hashArray) {
    int i = 0;
    for(i = SIZE-1; i>-1; i--) {

        if(hashArray[i] != NULL) {
            printf("%d*x^%d", hashArray[i]->data, hashArray[i]->key);
            if (i > 0) {
                printf(" + ");
            } else {
                printf("\n");
            }
        }
    }
}