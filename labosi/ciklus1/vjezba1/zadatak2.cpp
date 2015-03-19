//
// Created by ivan on 3/12/15.
//

#include <iostream>
#include "Matrix.hpp"

using namespace std;

void zadatakdrugi();

int main() {

    zadatakdrugi();

    return 0;
}

void zadatakdrugi() {
    IMatrixPtr lhs(new Matrix(3, 3));
    IMatrixPtr rhs(new Matrix(3, 1));

    double d;
    cin >> d;
    lhs->set(0, 0, d);
    cin >> d;
    lhs->set(1, 0, d);
    cin >> d;
    lhs->set(2, 0, d);

    cin >> d;
    rhs->set(0, 0, d);

    cin >> d;
    lhs->set(0, 1, d);
    cin >> d;
    lhs->set(1, 1, d);
    cin >> d;
    lhs->set(2, 1, d);

    cin >> d;
    rhs->set(1, 0, d);

    cin >> d;
    lhs->set(0, 2, d);
    cin >> d;
    lhs->set(1, 2, d);
    cin >> d;
    lhs->set(2, 2, d);

    cin >> d;
    rhs->set(2, 0, d);

    cout<<lhs->toString()<<endl;
    cout<<rhs->toString()<<endl;

    cout << "[x,y,z] = " << lhs->nInvert()->nMultiply(rhs)->nTranspose(true)->toString() << endl;
}
