#ifndef SPOLY_VLADHUZ_SPOLY_H
#define SPOLY_VLADHUZ_SPOLY_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define SIZE 20

typedef struct {
    int data;
    int key;
} DataItem;


IType hashCode (IType key);
DataItem *search(IType key, DataItem **hashArray);
void insert(IType key, IType data, DataItem **hashArray);
void delete(DataItem* item, DataItem **hashArray);
void display();

#endif //SPOLY_VLADHUZ_SPOLY_H
