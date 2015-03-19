//
// Created by ivan on 3/12/15.
//

#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

void probaKopiranjaVektora();

void izracunBaricentricnihKoordinata();

void izracunBaricentricnihKoordinataDrugiNacin();

void modeliranjeMatrice();

void rjesavanjeSustavaJednadzbi();

void izracunReflektiranogVektora();

int main() {

    //probaKopiranjaVektora();

    //izracunBaricentricnihKoordinata();

    //modeliranjeMatrice();

    //rjesavanjeSustavaJednadzbi();

    //izracunBaricentricnihKoordinataDrugiNacin();

    //izracunReflektiranogVektora();

    return 0;
}

void izracunReflektiranogVektora() {
    IVectorPtr vector = Vector::parseSimple("1 0 0");
    IVectorPtr reflector = Vector::parseSimple("1 1 0");

    cout << reflector->normalize()->nScalarMultiply(2)->nScalarMultiply(reflector->scalarProduct(vector))->nSub(vector)->toString() << endl;

}

void rjesavanjeSustavaJednadzbi() {

    IMatrixPtr a = Matrix::parseSimple("3 5 | 2 10");
    IMatrixPtr r = Matrix::parseSimple("2 | 8");
    IMatrixPtr v = a->nInvert()->nMultiply(r);

    cout << "Rjesenje sustava je:" << endl;
    cout << v->toString();
}

void modeliranjeMatrice() {
    IMatrixPtr m1 = Matrix::parseSimple("1 2 3 | 4 5 6");


    IMatrixPtr m2 = m1->nTranspose(false);

    cout << "m1:" << endl << m1->toString() << endl;
    cout << "m2:" << endl << m2->toString() << endl;

    m2->set(2, 1, 9);

    cout << "m1:" << endl << m1->toString() << endl;
    cout << "m2:" << endl << m2->toString() << endl;
}

void probaKopiranjaVektora() {
    IVectorPtr a = Vector::parseSimple("-2 4 1");
    IVectorPtr b = a->copyPart(2);
    IVectorPtr c = a->copyPart(5);

    std::cout << a->toString() << std::endl;
    std::cout << b->toString() << std::endl;
    std::cout << c->toString() << std::endl;

}

void izracunBaricentricnihKoordinata() {
    IVectorPtr a = Vector::parseSimple("1 0 0");
    IVectorPtr b = Vector::parseSimple("5 0 0");
    IVectorPtr c = Vector::parseSimple("3 8 0");

    IVectorPtr t = Vector::parseSimple("3 4 0");

    double pov = b->nSub(a)->nVectorProduct(c->nSub(a))->norm() / 2.0;
    double povA = b->nSub(t)->nVectorProduct(c->nSub(t))->norm() / 2.0;
    double povB = a->nSub(t)->nVectorProduct(c->nSub(t))->norm() / 2.0;
    double povC = a->nSub(t)->nVectorProduct(b->nSub(t))->norm() / 2.0;

    double t1 = povA / pov;
    double t2 = povB / pov;
    double t3 = povC / pov;

    cout << "Baricentricne koordinate su: (" << t1 << "," << t2 << "," << t3 << ")." << std::endl;
}

void izracunBaricentricnihKoordinataDrugiNacin() {
    IMatrixPtr m = Matrix::parseSimple("1 5 3 | 0 0 8 | 1 1 1");

    IMatrixPtr r = Matrix::parseSimple("3 | 4 | 1");

    IMatrixPtr t = m->nInvert()->nMultiply(r);

    cout << "Baricentricne koordinate su:" << endl << t->toString() << std::endl;
}