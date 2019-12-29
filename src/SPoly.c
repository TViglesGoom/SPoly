#include "../headers/SPoly.h"


/* Выделение памяти под новый полином */
Poly *createNewPoly(IType size) {
    Poly *newPoly = malloc(sizeof(Poly));
    newPoly->size = size;
    newPoly->count = 0;
    newPoly->elements = calloc(size, sizeof(PolyElem *));
    newPoly->sortedDegrees = malloc(size * sizeof(IType));
    return newPoly;
}


/* Генерация случайного полинома с количеством максимальным количеством элементов n
 * и реальным количеством m */
Poly *generate(size_t n, size_t m) {
    if (n < m) {
        n = m;
    }
    Poly *poly = createNewPoly((IType) n);
    srand(time(NULL));
    for (size_t c = 1; c <= m; c++) {
        insert(rand() % 100, (DType) (rand() % 100 - 50), poly);
    }
    return poly;
}


/* Создание полинома из строки,
 * полином должен иметь вид an*x^n + an-1*x^(n-1) + ... + a0*x^0,
 * где an != 0, для всех n >= 0 */
IType inputFromString(Poly *poly, char *str) {
    IType countX = 0;
    DType doubleCoef;
    IType intDeg;
    for (unsigned i = 0; i < strlen(str); i++) {
        if (str[i] == 'x') countX++;
    }
    poly = createNewPoly(countX);
    IType i = 0;
    while (i < strlen(str)) {
        char *coef = "";
        char *deg = "";
        char *coefEnd;
        char *degEnd;
        if (str[i] == 'x') {
            doubleCoef = strtod(coef, &coefEnd);
        }
        if (str[i] == ' ' && str[i - 1] != '+') {

        }
    }
}

/* Функция для взятия хешкода степени */
IType hashCode(IType degree, IType size) {
    return degree % size;
}


/* Поиск элемента PolyElem по его степени degree в полиноме poly */
PolyElem *search(IType degree, Poly *poly) {
    //get the hash
    IType hashIndex = hashCode(degree, poly->size);
    IType counter = 0;
    //move in array until an empty
    while (poly->elements[hashIndex] != NULL && counter <= poly->count) {

        if (poly->elements[hashIndex]->degree == degree)
            return poly->elements[hashIndex];
        //go to next cell
        ++hashIndex;
        ++counter;
        //wrap around the table
        hashIndex %= poly->size;
    }

    return NULL;
}


/* Вставка степени в массив элементов полинома */
void insertDegree(IType degree, Poly *poly) {
    IType sortedIndex = poly->count;
    for (IType i = 0; i < poly->count; i++) {
        if (poly->sortedDegrees[i] > degree) {
            sortedIndex = i;
            break;
        }
    }
    for (IType i = poly->count; i > sortedIndex; i--) {
        poly->sortedDegrees[i] = poly->sortedDegrees[i - 1];
    }
    poly->sortedDegrees[sortedIndex] = degree;
}


/* Вставка элемента по его степени и коэфициенту */
void insert(IType degree, DType coefficient, Poly *poly) {
    /* Если достигнуто максимальное количество элементов, выходим */
    if (poly->count >= poly->size) {
//        printf("MAX POLY SIZE REACHED");
        return;
    }
    /* Если уже есть элемент с такой же степенью в полиноме, выходим */
    if (search(degree, poly) != NULL) {
//        printf("ELEMENT WITH THIS DEGREE ALREADY IS IN POLY");
        return;
    }
    PolyElem *item = malloc(sizeof(PolyElem));
    item->coefficient = coefficient;
    item->degree = degree;
    insertDegree(degree, poly);
    /* Получаем хеш */
    IType hashIndex = hashCode(degree, poly->size);
    /* Двигаемся по массиву (по кругу), пока не встретим пустую ячейку */
    while (poly->elements[hashIndex] != NULL) {
        ++hashIndex;
        hashIndex %= poly->size;

    }
    poly->count += 1;
    poly->elements[hashIndex] = item;
}


/* Удаление элемента el из полинома poly */
void delete(PolyElem *el, Poly *poly) {
    for (int i = 0; i < poly->count; i++) {
        if (poly->elements[i] == el) {
            /* Элемент делаем NULL, уменьшаем count и смещаем все степени после удалённой на 1 индекс влево,
             * сохраняя при этом отсортированность */
            poly->elements[i] = NULL;
            IType index = -1;
            for (int j = 0; j < poly->count; j++) {
                if (poly->sortedDegrees[j] == el->degree) {
                    index = j;
                    break;
                }
            }
            poly->count--;
            for (; index < poly->count; index++) {
                poly->sortedDegrees[index] = poly->sortedDegrees[index + 1];
            }
        }
    }
}


/* Вывод в консоль полинома */
void display(Poly *poly) {
    IType i = 0, degree;
    DType coefficient;
    for (i = poly->count - 1; i > -1; i--) {
        degree = poly->sortedDegrees[i];
        coefficient = search(degree, poly)->coefficient;
        if (i < poly->count - 1) {
            printf(coefficient > 0 ? " + " : " - ");
        }
        printf("%.2f", (coefficient > 0 || i == poly->count - 1 ? 1 : -1) * coefficient);
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


/* Нахождение всех степеней полинома */
IType *createUnion(const IType *arr1, const IType *arr2, IType m, IType n, IType *size) {
    IType *unionOfArrays = malloc((m + n) * sizeof(IType));
    IType i = 0, j = 0, unionSize = 0;
    /* Объединение двух множеств */
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
    while (i < m)
        unionOfArrays[unionSize++] = arr1[i++];
    while (j < n)
        unionOfArrays[unionSize++] = arr2[j++];
    IType *sizedUnion = malloc(unionSize * sizeof(IType));
    for (IType ind = 0; ind < unionSize; ind++) {
        sizedUnion[ind] = unionOfArrays[ind];
    }
    free(unionOfArrays);
    *size = unionSize;
    return sizedUnion;
}


/* Сложение полиномов */
Poly *add(Poly *poly1, Poly *poly2) {
    IType unionSize;
    /* Находим все степени нового полинома */
    IType *tempArray = createUnion(poly1->sortedDegrees, poly2->sortedDegrees,
                                   poly1->count, poly2->count, &unionSize);
    Poly *newPoly = createNewPoly(unionSize);
    newPoly->sortedDegrees = tempArray;
    PolyElem *elem;
    IType degree;
    DType sum;
    /* Складываем коэффициенты соответствующих степеней в полиномах
     * Если в каком-то из полиномов не присутствует какая-либо степень, то возвращается NULL
     * В таком случае просто не прибавляем к нашей сумме ничего */
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


/* Унарный минус для полинома */
Poly *unsub(Poly *poly) {
    Poly *newPoly = createNewPoly(poly->count);
    IType degree;
    for (IType c = 0; c < poly->count; c++) {
        degree = poly->sortedDegrees[c];
        insert(degree, -1 * search(degree, poly)->coefficient, newPoly);
    }
    return newPoly;
}


/* Вычитание полиномов */
Poly *sub(Poly *poly1, Poly *poly2) {
    return add(poly1, unsub(poly2));
}


/* Умножение полиномов */
Poly *mul(Poly *poly1, Poly *poly2, DType number) {
    if (poly1 == NULL) {
        poly1 = createNewPoly(1);
        insert(0, 1, poly1);
    }
    if (poly2 == NULL) {
        poly2 = createNewPoly(1);
        insert(0, 1, poly2);
    }
    IType degree, degree1, degree2;
    /* Выделяем память не меньше необходимого, но может быть и больше */
    Poly *newPoly = createNewPoly(poly1->count + poly2->count);
    for (IType i = 0; i < poly1->count; i++) {
        degree1 = poly1->sortedDegrees[i];
        for (IType j = 0; j < poly2->count; j++) {
            degree2 = poly2->sortedDegrees[j];
            degree = degree1 + degree2;
            insert(degree, 0, newPoly);
            search(degree, newPoly)->coefficient +=
                    number * search(degree1, poly1)->coefficient * search(degree2, poly2)->coefficient;
        }
    }
    return newPoly;
}


/* Алгоритм деления полинома на полином */
Poly *divideAlgorithm(Poly *poly1, Poly *poly2, DType number, IType flag) {
    if (poly1 == NULL) {
        return NULL;
    }
    if (poly2 != NULL) {
        /* Обычный алгоритм деления полинома на полином */
        Poly *temp = createNewPoly(poly1->size);
        memcpy(temp, poly1, sizeof(Poly));
        /* Предполагаем, что новый массив будет не больше степени, чем разница наибольшей степени первого
         * и наибольшей степени второго, из чего следует наибольшее количество элементов итогового полинома */
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
        Poly *mod = createNewPoly(1);
        insert(0, 0, mod);
        return mod;
    }

}


/* Нахождение полинома, полученного при делении двух данных */
Poly *divide(Poly *poly1, Poly *poly2, DType number) {
    return divideAlgorithm(poly1, poly2, number, 1);
}


/* Нахождение полинома-остатка, полученного при делении двух данных */
Poly *mod(Poly *poly1, Poly *poly2, DType number) {
    return divideAlgorithm(poly1, poly2, number, 0);
}


/* Нахождение значения полинома в точке x */
DType value(Poly *poly, DType x) {
    DType sum = 0, xPowed = 1;
    PolyElem *elem;
    for (IType c = 0; c <= poly->sortedDegrees[poly->count - 1]; c++) {
        elem = search(c, poly);
        if (elem != NULL) {
            sum += elem->coefficient * xPowed;
        }
        xPowed *= x;
    }
    return sum;
}


/* Нахождение производной полинома */
Poly *derivative(Poly *poly) {
    Poly *newPoly = createNewPoly(poly->count);
    IType degree;
    for (IType c = 0; c < poly->count; c++) {
        degree = poly->sortedDegrees[c];
        if (degree != 0) {
            insert(degree - 1, search(degree, poly)->coefficient * degree, newPoly);
        }
    }
    return newPoly;
}


/* Неопределенный интеграл с константой C */
Poly *integral(Poly *poly, DType C) {
    Poly *newPoly = createNewPoly(poly->count + (C == 0 ? 0 : 1));
    IType degree;
    for (IType c = 0; c < poly->count; c++) {
        degree = poly->sortedDegrees[c];
        insert(degree + 1, search(degree, poly)->coefficient / (degree + 1), newPoly);
    }
    if (C != 0) {
        insert(0, C, newPoly);
    }
    return newPoly;
}


/* Определенный интеграл в промежутке от a до b */
DType integrate(Poly *poly, DType a, DType b) {
    Poly *newPoly = integral(poly, 0);
    return value(newPoly, b) - value(newPoly, a);
}


/* Нормирование полинома */
Poly *normalize(Poly *poly) {
    Poly *newPoly = createNewPoly(poly->count);
    DType firstCoefficient = search(poly->sortedDegrees[poly->count - 1], poly)->coefficient;
    for (IType c = 0; c < poly->count; c++) {
        insert(poly->sortedDegrees[c],
               search(poly->sortedDegrees[c], poly)->coefficient / firstCoefficient,
               newPoly);
    }
    return newPoly;
}


/* Проверка нахождения точки в линии */
int inLine(DType x, DLine line) {
    return line.x1 <= x && x <= line.x2;
}


/* Нахождение действительных корней полинома */
DType *polyRealRoots(Poly *poly, IType *rootsCount, DLine line) {
    /* Нормализируем полином для избежания больших коэфициэнтов n!*an */
    poly = normalize(poly);
    DType *roots = malloc(sizeof(DType) * poly->sortedDegrees[poly->count - 1]);
    PolyElem *zeroDeg = search(0, poly);
    PolyElem *oneDeg = search(1, poly);
    /* Дошли до степени 1, просто находим корень */
    if (poly->count <= 2 && oneDeg != NULL) {
        if (zeroDeg == NULL && poly->count == 1 && inLine(0, line)) roots[(*rootsCount)++] = 0;
        else {
            DType root = (oneDeg->coefficient < 0 ? 1 : -1) * zeroDeg->coefficient;
            if (inLine(root, line)) roots[(*rootsCount)++] = root;
        }
        return roots;
    }
    IType derivativeRootsCount = 0;
    /* Находим корни производной, корни нашего полинома будут между концами промежутков монотонности,
     * если те имеют разные знаки */
    DType *derivativeRoots = polyRealRoots(derivative(poly), &derivativeRootsCount, line);
    DType *intervals = malloc(sizeof(DType) * (derivativeRootsCount + 2));
    intervals[0] = line.x1;
    intervals[derivativeRootsCount + 1] = line.x2;
    /* Заполняем массив концов промежутков монотонности */
    for (int i = 1; i < derivativeRootsCount + 1; i++) {
        intervals[i] = derivativeRoots[i - 1];
    }
    /* Если левый конец есть корнем, то добавляем. В дальнейшем проверяются только правые */
    if (fabs(value(poly, intervals[0])) < line.dx) {
        roots[(*rootsCount)++] = intervals[0];
    }
    /* Нужен для того, чтобы определить, что правый конец был корнем, чтобы избежать повторения корней */
    int flag = 0;
    for (int i = 0; i < derivativeRootsCount + 1; i++) {
        if (flag) {
            flag = 0;
            continue;
        }
        DType leftSide = intervals[i];
        DType rightSide = intervals[i + 1];
        /* Проверка, что правый конец является корнем */
        if (fabs(value(poly, rightSide)) < line.dx) {
            roots[(*rootsCount)++] = rightSide;
            flag = 1;
            continue;
        }
        /* Метод деления пополам */
        if (value(poly, intervals[i]) * value(poly, intervals[i + 1]) < 0) {
            DType root;
            DType rootValue;
            root = (leftSide + rightSide) / 2.0;

            do {
                root = (leftSide + rightSide) / 2.0;
                rootValue = value(poly, root);
                if (rootValue * value(poly, leftSide) < 0) {
                    rightSide = root;
                } else {
                    leftSide = root;
                }
            } while (fabs(rootValue) > line.dx && fabs(leftSide - rightSide) > 0.000000001);
            roots[(*rootsCount)++] = root;
        }
    }
    free(intervals);
    return roots;
}


/* Взятие коэфициэнтов полинома по модулю */
Poly *takeModuleCoefs(Poly *poly, IType module) {
    Poly *newPoly = createNewPoly(poly->count);
    for (IType i = 0; i < poly->count; i++) {
        PolyElem *el = search(poly->sortedDegrees[i], newPoly);
        /* Так как нельзя взять по модулю не целое число, то делаем так,
         * чтобы наш коэфициент попал в промежуток от 0 до module */
        if (el->coefficient >= module) {
            insert(el->degree, el->coefficient - floor(el->coefficient / module) * module, newPoly);
        }
        while (el->coefficient < 0) {
            insert(el->degree, el->coefficient + module, newPoly);
        }
    }
}


/* Модульное сложение двух полиномов */
Poly *moduleAdd(Poly *poly1, Poly *poly2, IType module) {
    return takeModuleCoefs(add(poly1, poly2), module);
}


/* Модульное умножение двух полиномов */
Poly *moduleMul(Poly *poly1, Poly *poly2, IType module) {
    return takeModuleCoefs(mul(poly1, poly2, 1), module);
}

