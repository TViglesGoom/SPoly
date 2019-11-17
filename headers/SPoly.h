#ifndef SPOLY
#define SPOLY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
Poly* generate(size_t n, size_t m);
IType hashCode(IType degree, IType size);
PolyElem* search(IType degree, Poly* poly);
void insertDegree(IType degree, Poly* poly);
void insert(IType degree, DType coefficient, Poly* poly);
void display();

Poly* add(Poly* poly1, Poly* poly2);
IType* createUnion(const IType* arr1, const IType* arr2, IType m, IType n, IType* unionSize);
Poly* sub(Poly* poly1, Poly* poly2);

// number = 1 for plain multiplication, dividing, and taking module poly1[*/%]poly2
// poly2 = NULL for poly1[*/%]number
Poly* mul(Poly* poly1, Poly* poly2, DType number);
Poly* divide(Poly* poly1, Poly* poly2, DType number);
Poly* mod(Poly* poly1, Poly* poly2, DType number);

#endif //SPOLY
