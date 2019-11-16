#include "../headers/SPoly.h"


Poly* createNewPoly(IType size) {
    Poly* newPoly = malloc(sizeof(Poly));
    newPoly->size = size;
    newPoly->count = 0;
    newPoly->elements = calloc(size, sizeof(PolyElem*));
    newPoly->sortedDegrees = (IType*)malloc(size*sizeof(IType));
    return newPoly;
}

IType hashCode(IType degree, IType size) {
    return degree % size;
}

PolyElem* search(IType degree, Poly *poly) {
    //get the hash
    IType hashIndex = hashCode(degree, poly->size);
    IType counter = 0;
    //move in array until an empty
    while(poly->elements[hashIndex] != NULL && counter <= poly->count) {

        if(poly->elements[hashIndex]->degree == degree)
            return poly->elements[hashIndex];
        //go to next cell
        ++hashIndex;
        ++counter;
        //wrap around the table
        hashIndex %= poly->size;
    }

    return NULL;
}

void insert(IType degree, DType coefficient, Poly* poly) {

    PolyElem *item = malloc(sizeof(PolyElem));
    item->coefficient = coefficient;
    item->degree = degree;

    IType sortedIndex = poly->count;
    for (IType i = 0; i < poly->count; i++) {
        if (poly->sortedDegrees[i] > degree) {
            sortedIndex = i;
            break;
        }
    }
    for (IType i = poly->count; i > sortedIndex; i--) {
        poly->sortedDegrees[i] = poly->sortedDegrees[i-1];
    }
    poly->sortedDegrees[sortedIndex] = degree;

    //get the hash
    IType hashIndex = hashCode(degree, poly->size);
    //move in array until an empty or deleted cell
    while(poly->elements[hashIndex] != NULL) {
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= poly->size;

    }
    poly->count += 1;
    poly->elements[hashIndex] = item;
}

void display(Poly* poly) {
    IType i = 0;
    for(i = poly->count - 1; i > -1; i--) {
        IType degree = poly->sortedDegrees[i];
        printf("%f*x^%d", search(degree, poly)->coefficient, degree);
        if (i > 0) {
            printf(" + ");
        } else {
            printf("\n");
        }
    }
}