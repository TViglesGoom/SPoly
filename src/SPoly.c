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
//        printf("MAX POLY SIZE REACHED");
        return;
    }
    if (search(degree, poly) != NULL) {
//        printf("ELEMENT WITH THIS DEGREE ALREADY IS IN POLY");
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
    IType i = 0, degree;
    DType coefficient;
    for(i = poly->count - 1; i > -1; i--) {
        degree = poly->sortedDegrees[i];
        coefficient = search(degree, poly)->coefficient;
        if (i < poly->count - 1) {
            printf(coefficient > 0 ? " + " : " - ");
        }
        printf("%.1f", (coefficient > 0 || i == poly->count - 1 ? 1 : -1) * coefficient);
        if (degree != 0) {
            if (degree == 1) {
                printf("*x");
            } else {
                printf("*x^%d", degree);
            }
        }
    }
    if (poly->count == 0) {
        printf("0");
    }
    printf("\n");
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

Poly* sub(Poly* poly1, Poly* poly2) {
    return add(poly1, unsub(poly2));
}

Poly* mul(Poly* poly1, Poly* poly2, DType number) {
    if (poly1 == NULL) {
        poly1 = createNewPoly(1);
        insert(0, 1, poly1);
    }
    if (poly2 == NULL) {
        poly2 = createNewPoly(1);
        insert(0, 1, poly2);
    }
    IType degree, degree1, degree2;
    Poly* newPoly = createNewPoly(poly1->count + poly2->count);
    for (IType i = 0; i < poly1->count; i++) {
        degree1 = poly1->sortedDegrees[i];
        for (IType j = 0; j < poly2->count; j++) {
            degree2 = poly2->sortedDegrees[j];
            degree = degree1 + degree2;
            insert(degree, 0, newPoly);
            search(degree, newPoly)->coefficient += number * search(degree1, poly1)->coefficient * search(degree2, poly2)->coefficient;
        }
    }
    return newPoly;
}

Poly* divideAlgorithm(Poly *poly1, Poly *poly2, DType number, IType flag) {
    if (poly1 == NULL) {
        return NULL;
    }
    if (poly2 != NULL) {
        Poly *temp = createNewPoly(poly1->size);
        memcpy(temp, poly1, sizeof(Poly));
        Poly *result = createNewPoly(
                poly1->sortedDegrees[poly1->count - 1] - poly2->sortedDegrees[poly2->count - 1] + 1);

        IType tempDegree, poly2Degree, resDegree;
        DType resCoefficient;
        tempDegree = temp->sortedDegrees[temp->count - 1];
        poly2Degree = poly2->sortedDegrees[poly2->count - 1];
        while (tempDegree >= poly2Degree) {
            resDegree = tempDegree - poly2Degree;
            resCoefficient = search(tempDegree, temp)->coefficient / search(poly2Degree, poly2)->coefficient;
            insert(resDegree, resCoefficient, result);
            Poly *temp2 = createNewPoly(1);
            insert(resDegree, resCoefficient, temp2);
            memcpy(temp, sub(temp, mul(poly2, temp2, 1)), sizeof(Poly));
            free(temp2);
            tempDegree = temp->sortedDegrees[temp->count - 1];
        }
        if (flag) {
            return mul(result, NULL, 1 / number);
        }
        return temp;
    } else {
        if (flag) {
            return mul(poly1, NULL, 1 / number);
        }
        Poly* mod = createNewPoly(1);
        insert(0, 0, mod);
        return mod;
    }

}

Poly* divide(Poly* poly1, Poly* poly2, DType number) {
    return divideAlgorithm(poly1, poly2, number, 1);
}

Poly* mod(Poly* poly1, Poly* poly2, DType number) {
    return divideAlgorithm(poly1, poly2, number, 0);
}

DType value(Poly* poly, DType x) {
    DType sum = 0, xPowed = 1;
    PolyElem* elem;
    for (IType c = 0; c <= poly->sortedDegrees[poly->count-1]; c++) {
        elem = search(c, poly);
        if (elem != NULL) {
            sum += elem->coefficient * xPowed;
        }
        xPowed *= x;
    }
    return sum;
}

Poly* derivative(Poly* poly) {
    Poly* newPoly = createNewPoly(poly->count);
    IType degree;
    for (IType c = 0; c < poly->count; c++) {
        degree = poly->sortedDegrees[c];
        if (degree != 0) {
            insert(degree-1, search(degree, poly)->coefficient * degree, newPoly);
        }
    }
    return newPoly;
}

Poly* integral(Poly* poly, DType C) {
    Poly* newPoly = createNewPoly(poly->count + (C == 0 ? 0 : 1));
    IType degree;
    for (IType c = 0; c < poly->count; c++) {
        degree = poly->sortedDegrees[c];
        insert(degree+1, search(degree, poly)->coefficient / (degree + 1), newPoly);
    }
    if (C != 0) {
        insert(0, C, newPoly);
    }
    return newPoly;
}

DType integrate(Poly* poly, DType a, DType b) {
    Poly* newPoly = integral(poly, 0);
    return value(newPoly, b) - value(newPoly, a);
}
