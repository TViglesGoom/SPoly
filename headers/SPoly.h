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

DType hashCode (IType key);
struct DataItem *search (IType key);
void insert (IType key, IType data);
struct DataItem* delete(struct DataItem* item);
void display();

#endif //SPOLY_VLADHUZ_SPOLY_H
