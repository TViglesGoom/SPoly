#include "../headers/SPoly.h"


Poly* createNewPoly(IType size) {
    Poly* newPoly = malloc(sizeof(Poly));
    newPoly->size = size;
    newPoly->count = 0;
    newPoly->elements = calloc(size, sizeof(PolyElem*));

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
    //get the hash
    int hashIndex = hashCode(degree, poly->size);
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

void delete(PolyElem* item, Poly* poly) {
    if (item == NULL) {
        return;
    }
    int degree = item->degree;
    //get the hash
    int hashIndex = hashCode(degree, poly->size);
    //move in array until an empty
    while(poly->elements[hashIndex] != NULL) {
        if(poly->elements[hashIndex]->degree == degree) {
            poly->elements[hashIndex] = NULL;
        }
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= poly->size;
    }
}

void display(Poly* poly) {
    int i = 0;
    for(i = poly->size - 1; i > -1; i--) {

        if(poly->elements[i] != NULL) {
            printf("%f*x^%d", poly->elements[i]->coefficient, poly->elements[i]->degree);
            if (i > 0) {
                printf(" + ");
            } else {
                printf("\n");
            }
        }
    }
}