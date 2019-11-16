#ifndef SPOLY_VLADHUZ_SPOLY_H
#define SPOLY_VLADHUZ_SPOLY_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define SIZE 20

struct DataItem {
    int data;
    int key;
};

IType hashCode (IType key);
struct DataItem *search(IType key, struct DataItem **hashArray);
void insert(IType key, IType data, struct DataItem **hashArray);
void delete(struct DataItem* item, struct DataItem **hashArray);
void display();

#endif //SPOLY_VLADHUZ_SPOLY_H
