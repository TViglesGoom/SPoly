#ifndef SPOLY_VLADHUZ_SPOLY_H
#define SPOLY_VLADHUZ_SPOLY_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef struct {
    DType coefficient;
    IType degree;
} PolyElem;

typedef struct {
    IType size;
    IType count;
    IType *sortedDegrees;
    PolyElem** elements;
} Poly;


Poly* createNewPoly(IType size);
IType hashCode(IType degree, IType size);
PolyElem* search(IType degree, Poly* poly);
void insert(IType degree, DType coefficient, Poly* poly);
void display();

#endif //SPOLY_VLADHUZ_SPOLY_H
