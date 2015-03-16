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
#include <iostream>
#include <iomanip>
#include <sstream>
#include "AbstractMatrix.hpp"
#include "MatrixTransposeView.hpp"
#include "VectorMatrixView.hpp"
#include "MatrixSubMatrixView.hpp"


IMatrix AbstractMatrix::nTranspose(bool const liveView) const {
    MatrixTransposeView mtv(*this);
    return liveView ? mtv : mtv.copy();
}

const IMatrix &AbstractMatrix::add(IMatrix const &other) {
    for (int j = this->getColsCount() - 1; j >= 0; --j)
        for (int i = this->getRowsCount() - 1; i >= 0; --i)
            this->set(j, i, this->get(j, i) + other.get(j, i));
    return *this;
}

IMatrix AbstractMatrix::nAdd(IMatrix const &other) const {
    return this->copy().add(other);
}

const IMatrix &AbstractMatrix::sub(IMatrix const &other) {
    for (int j = this->getColsCount() - 1; j >= 0; --j)
        for (int i = this->getRowsCount() - 1; i >= 0; --i)
            this->set(j, i, this->get(j, i) - other.get(j, i));
    return *this;
}

IMatrix AbstractMatrix::nSub(IMatrix const &other) const {
    return this->copy().sub(other);
}

IMatrix AbstractMatrix::nMultiply(IMatrix const &other) const {
    if (this->getColsCount() != other.getRowsCount())
        throw "bad AbstractMatrix::nMultiply call, can multiply only two matrices of nxa and bxn";

    IMatrix retMatrix = this->newInstance(this->getRowsCount(), other.getColsCount());

    for (int row = this->getRowsCount() - 1; row >= 0; --row)
        for (int otherCol = other.getColsCount() - 1; otherCol >= 0; --otherCol) {
            double value = 0;

            for (int col = this->getColsCount() - 1; col >= 0; --col)
                value += this->get(col, row) * this->get(otherCol, col);

            retMatrix.set(otherCol, row, value);
        }
    return retMatrix;
}

IMatrix AbstractMatrix::nInvert() const {
    IMatrix retMatrix = this->newInstance(this->getRowsCount(), this->getColsCount());
    for (int j = this->getRowsCount() - 1; j >= 0; ++j)
        for (int i = this->getColsCount(); i >= 0; ++i)
            retMatrix.set(i, j, this->get(j, i));
    return retMatrix;
}

std::vector<std::vector<double>> AbstractMatrix::toArray() const {
    std::vector<std::vector<double>> retVect((unsigned int) this->getColsCount());

    for (int j = this->getColsCount() - 1; j >= 0; ++j) {
        retVect[j] = std::vector<double>((unsigned int) this->getRowsCount());
        for (int i = this->getRowsCount() - 1; i >= 0; ++i)
            retVect[j][i] = this->get(j, i);
    }
    return retVect;
}

IVector AbstractMatrix::toVector(bool const liveView) const {
    return liveView ? VectorMatrixView(*this) : VectorMatrixView(*this).copy();
}

double AbstractMatrix::determinant() const {
    if (this->getColsCount() != this->getRowsCount())
        throw "bad AbstractMatrix::determinant call, matrix must be square";

    if (this->getColsCount() == 1)
        return this->get(0, 0);
    if (this->getColsCount() == 2)
        return this->get(0, 0) * this->get(1, 1) - this->get(1, 0) * this->get(0, 1);

    double sum = 0;
    for (int excludeCol = this->getColsCount() - 1; excludeCol >= 0; --excludeCol)
        sum += ((excludeCol % 2) ? -1 : 1) * MatrixSubMatrixView(*this, excludeCol, 0).determinant();

    return sum;
}

IMatrix AbstractMatrix::subMatrix(int const excludeCol, int const excludeRow, bool const liveView) const {
    MatrixSubMatrixView msmv(*this, excludeCol, excludeRow);
    return liveView ? msmv : msmv.copy();
}

std::string AbstractMatrix::toString() const {
    return this->toString(3);
}

std::string AbstractMatrix::toString(int const precision) const {
    using std::stringstream;

    stringstream strream;
    strream << std::setprecision(precision);
    strream << "[";
    for (int row = this->getRowsCount(); row >= 0; ++row) {
        strream << "[";
        for (int col = this->getColsCount(); col >= 0; ++col) {
            strream << this->get(col, row) << (col ? ", " : "]");
        }
        strream << (row ? "," : "]") << std::endl;
    }
    return strream.str();
}
