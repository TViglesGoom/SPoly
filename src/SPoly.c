#include "../headers/SPoly.h"


Poly* createNewPoly(IType size) {
    Poly* newPoly = malloc(sizeof(Poly));
    newPoly->size = size;
    newPoly->count = 0;
    newPoly->elements = calloc(size, sizeof(PolyElem*));
    newPoly->sortedDegrees = malloc(size*sizeof(IType));
    return newPoly;
}

Poly* generate(size_t n, size_t m) {
    if (n < m) {
        n = m;
    }
    Poly* poly = createNewPoly((IType)n);
    srand (time(NULL));
    for (size_t c = 1; c <= m; c++)
    {
        insert(rand() % 100, (DType)(rand() % 100 - 50), poly);
    }
    return poly;
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

void insertDegree(IType degree, Poly* poly) {
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
}

void insert(IType degree, DType coefficient, Poly* poly) {
    if (poly->count >= poly->size) {
        printf("MAX POLY SIZE REACHED");
        return;
    }
    PolyElem *item = malloc(sizeof(PolyElem));
    item->coefficient = coefficient;
    item->degree = degree;
    insertDegree(degree, poly);
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
        printf("%.1f", search(degree, poly)->coefficient);
        if (degree != 0) {
            printf("*x^%d", degree);
        }
        if (i > 0) {
            printf(" + ");
        } else {
            printf("\n");
        }
    }
}

IType* createUnion(const IType* arr1, const IType* arr2, IType m, IType n, IType* size) {
    IType* unionOfArrays = malloc((m+n) * sizeof(IType));
    IType i = 0, j = 0, unionSize = 0;
    while (i < m && j < n) {
        if (arr1[i] < arr2[j])
            unionOfArrays[unionSize++] = arr1[i++];
        else if (arr2[j] < arr1[i])
            unionOfArrays[unionSize++] = arr2[j++];
        else {
            unionOfArrays[unionSize++] = arr2[j++];
            i++;
        }
    }
    /* Print remaining elements of the larger array */
    while(i < m)
        unionOfArrays[unionSize++] = arr1[i++];
    while(j < n)
        unionOfArrays[unionSize++] = arr2[j++];
    IType* sizedUnion = malloc(unionSize* sizeof(IType));
    for (IType ind = 0; ind < unionSize; ind++) {
        sizedUnion[ind] = unionOfArrays[ind];
    }
    free(unionOfArrays);
    *size = unionSize;
    return sizedUnion;
}


Poly* add(Poly* poly1, Poly* poly2) {
    IType unionSize;
    IType* tempArray = createUnion(poly1->sortedDegrees, poly2->sortedDegrees,
            poly1->count, poly2->count, &unionSize);
    Poly* newPoly = createNewPoly(unionSize);
    newPoly->sortedDegrees = tempArray;
    PolyElem* elem;
    IType degree;
    DType sum;
    for (IType c = 0; c < unionSize; c++) {
        sum = 0;
        degree = newPoly->sortedDegrees[c];
        elem = search(degree, poly1);
        if (elem != NULL) {
            sum += elem->coefficient;
        }
        elem = search(degree, poly2);
        if (elem != NULL) {
            sum += elem->coefficient;
        }
        if (sum != 0) {
            insert(degree, sum, newPoly);
        }
    }
    return newPoly;
}

Poly* unsub(Poly* poly) {
    Poly* newPoly = createNewPoly(poly->count);
    IType degree;
    for (IType c = 0; c < poly->count; c++) {
        degree = poly->sortedDegrees[c];
        insert(degree, -1*search(degree, poly)->coefficient, newPoly);
    }
    return newPoly;
}
