#include "headers/common.h"
#include "headers/SPoly.h"
#include "tests/test_SPoly.h"

#include <stdio.h>

int main() {
    Poly* poly1 = createNewPoly(3);
    insert(2, 1, poly1);
    insert(1, -8, poly1);
    insert(0, 15, poly1);
    Poly* poly2 = createNewPoly(3);
    insert(2, 1, poly2);
    insert(1, -6, poly2);
    insert(0, 8, poly2);
    Poly* poly3 = createNewPoly(2);
    insert(2, 1, poly3);
    insert(0, -36, poly3);
    DLine line;
    line.x1 = -100;
    line.x2 = 100;
    line.dx = 0.0000001;
    int poly1RootsCount = 0;
    DType* poly1Roots = polyRealRoots(poly1, &poly1RootsCount, line);
    int poly2RootsCount = 0;
    DType* poly2Roots = polyRealRoots(poly2, &poly2RootsCount, line);
    int poly3RootsCount = 0;
    DType* poly3Roots = polyRealRoots(poly3, &poly3RootsCount, line);
    if (poly1RootsCount == 0 || poly2RootsCount == 0 || poly3RootsCount == 0) {
        printf("There are no roots");
        exit(0);
    }
    DLine intervals[3];
    int intervalsCount = 3;
    int k = 0;
    if (value(poly1, (line.x1 + poly1Roots[0]) / 2) < 0) {
        intervals[k].x1 = line.x1;
        intervals[k++].x2 = poly1Roots[0];
    }
    if (value(poly1, (poly1Roots[0] + poly1Roots[1]) / 2) < 0) {
        intervals[k].x1 = poly1Roots[0];
        intervals[k++].x2 = poly1Roots[1];
    }
    if (value(poly1, (poly1Roots[1] + line.x2) / 2) < 0) {
        intervals[k].x1 = poly1Roots[1];
        intervals[k++].x2 = line.x2;
    }
    for (int i = 0; i < poly2RootsCount; i++) {
        for (int j = 0; j < intervalsCount; j++) {
            if (inLine(poly2Roots[i], intervals[j])) {
                if (value(poly2, (intervals[j].x1 + poly2Roots[i]) / 2) >= 0) {
                    intervals[j].x2 = poly2Roots[i];
                } else {
                    intervals[j].x1 = poly2Roots[i];
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < intervalsCount; j++) {
            if (inLine(poly3Roots[i], intervals[j])) {
                if (value(poly3, (intervals[j].x1 + poly3Roots[i]) / 2) >= 0) {
                    intervals[j].x2 = poly3Roots[i];
                } else {
                    intervals[j].x1 = poly3Roots[i];
                }
            }
        }
    }
    for (int i = 0; i < k; i++) {
        if (intervals[i].x1 <= intervals[i].x2) printf("(%f, %f), ", intervals[i].x1, intervals[i].x2);
    }
    return 0;
}