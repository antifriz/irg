//
// Created by ivan on 3/12/15.
//

#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

void zadatakprvi();

int main() {

    zadatakprvi();

    return 0;
}

void zadatakprvi() {
    IVectorPtr a = Vector::parseSimple("2 3 -4");
    IVectorPtr b = Vector::parseSimple("-1 4 -3");
    IVectorPtr c = Vector::parseSimple("2 2 4");

    IMatrixPtr d = Matrix::parseSimple("1 2 3 | 2 1 3 | 4 5 1");
    IMatrixPtr e = Matrix::parseSimple("-1 2 -3 | 5 -2 7 | -4 -1 3");
    IMatrixPtr f = Matrix::parseSimple("-24 18 5 | 20 -15 -4 | -5 4 1");
    IMatrixPtr g = Matrix::parseSimple("1 2 3 | 0 1 4 | 5 6 0");

    IVectorPtr v1 = a->nAdd(b);
    cout << "v1: " << endl << v1->toString() << endl;

    double s = v1->scalarProduct(b);
    cout << "s: " << endl << s << endl << endl;

    IVectorPtr v2 = v1->nVectorProduct(a);
    cout << "v2: " << endl << v2->toString() << endl;

    IVectorPtr v3 = v2->copy()->normalize();
    cout << "v3: " << endl << v3->toString() << endl;

    IVectorPtr v4 = v2->copy()->nScalarMultiply(-1);
    cout << "v4: " << endl << v4->toString() << endl;

    IMatrixPtr m1 = d->nAdd(e);
    cout << "m1: " << endl << m1->toString() << endl;

    IMatrixPtr m2 = d->nMultiply(e->nTranspose(true));
    cout << "m2: " << endl << m2->toString() << endl;

    IMatrixPtr m3 = f->nInvert()->nMultiply(g->nInvert());
    cout << "m3: " << endl << m3->toString() << endl;

}
