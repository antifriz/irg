/*
* IRG VJ 1
* AbstractMatrix.cpp
*
* Abstract class AbstracMatrix definition, definition common matrix methods
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#include <vector>
#include <string>
#include "AbstractMatrix.hpp"


IMatrix AbstractMatrix::nTranspose(bool const i) const {
    return IMatrix();
}

const IMatrix& AbstractMatrix::add(IMatrix const& aConst) {
    return <#initializer#>;
}

IMatrix AbstractMatrix::nAdd(IMatrix const& aConst) const {
    return IMatrix();
}

const IMatrix& AbstractMatrix::sub(IMatrix const& aConst) {
    return <#initializer#>;
}

IMatrix AbstractMatrix::nSub(IMatrix const& aConst) const {
    return IMatrix();
}

IMatrix AbstractMatrix::nMultiply(IMatrix const& aConst) const {
    return IMatrix();
}

IMatrix AbstractMatrix::nInvert() const {
    return IMatrix();
}

std::vector<std::vector<double>> AbstractMatrix::toArray() const {
    return std::vector<std::vector<double>>();
}

IVector AbstractMatrix::toVector(bool const i) const {
    return IVector();
}

double AbstractMatrix::determinant() const {
    return 0;
}

IMatrix AbstractMatrix::subMatrix(int const i, int const i1, bool const i2) const {
    return IMatrix();
}

std::string AbstractMatrix::toString() const {
    return "jej";
}

std::string AbstractMatrix::toString(int const i) const {
    return "jej2";
}
