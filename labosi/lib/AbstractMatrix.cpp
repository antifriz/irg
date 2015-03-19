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
#include <iomanip>
#include <sstream>
#include "AbstractMatrix.hpp"
#include "MatrixSubMatrixView.hpp"
#include "MatrixTransposeView.hpp"
#include "VectorMatrixView.hpp"

const IMatrixPtr AbstractMatrix::nTranspose(bool liveView) {
    IMatrixPtr ptr = IMatrixPtr(new MatrixTransposeView(this->shared_from_this()));
    return liveView ? ptr : ptr->copy();
}

const IMatrixPtr AbstractMatrix::add(const IMatrixPtr other) {
    for (int j = this->getColsCount() - 1; j >= 0; --j)
        for (int i = this->getRowsCount() - 1; i >= 0; --i)
            this->set(j, i, this->get(j, i) + other->get(j, i));
    return this->shared_from_this();
}

const IMatrixPtr AbstractMatrix::nAdd(const IMatrixPtr other) const {
    return this->copy()->add(other);
}

const IMatrixPtr AbstractMatrix::sub(const IMatrixPtr other) {
    for (int j = this->getColsCount() - 1; j >= 0; --j)
        for (int i = this->getRowsCount() - 1; i >= 0; --i)
            this->set(j, i, this->get(j, i) - other->get(j, i));
    return this->shared_from_this();
}

const IMatrixPtr AbstractMatrix::nSub(const IMatrixPtr other) const {
    return this->copy()->sub(other);
}

const IMatrixPtr AbstractMatrix::nMultiply(const IMatrixPtr other) const {
    if (this->getColsCount() != other->getRowsCount())
        throw "bad AbstractMatrix::nMultiply call, can multiply only two matrices of nxa and bxn";

    IMatrixPtr retMatrixPtr = this->newInstance(this->getRowsCount(), other->getColsCount());

    for (int row = this->getRowsCount() - 1; row >= 0; --row)
        for (int otherCol = other->getColsCount() - 1; otherCol >= 0; --otherCol) {
            double value = 0;

            for (int iter = this->getColsCount() - 1; iter >= 0; --iter) {
                value += this->get(row, iter) * other->get(iter, otherCol);
            }
            retMatrixPtr->set(row, otherCol, value);
        }
    return retMatrixPtr;
}

const IMatrixPtr AbstractMatrix::nInvert() const {

    double determinant = this->determinant();

    if (!determinant) throw "bad AbstractMatrix::nInvert call, given matrix doesn't have inverse";

    IMatrixPtr ptrRoot = this->copy();
    IMatrixPtr ptr = this->copy();

    for (int i = ptr->getRowsCount() - 1; i >= 0; --i) {
        for (int j = ptr->getColsCount() - 1; j >= 0; --j) {
            ptr->set(i, j, (((i + j) % 2) ? -1 : 1) * ptrRoot->subMatrix(i, j, true)->determinant());
        }
    }
    return ptr->nTranspose(true)->multiplyByConstant(1.0 / determinant);
}

const IMatrixPtr AbstractMatrix::multiplyByConstant(double constant) {
    for (int i = 0; i < this->getRowsCount(); ++i) {
        for (int j = 0; j < this->getColsCount(); ++j) {
            this->set(i, j, this->get(i, j) * constant);
        }
    }
    return this->shared_from_this();
}

std::vector<std::vector<double>> AbstractMatrix::toArray() const {
    std::vector<std::vector<double>> retVect((unsigned int) this->getColsCount());

    for (int j = this->getColsCount() - 1; j >= 0; ++j) {
        retVect[j] = vector<double>((unsigned int) this->getRowsCount());
        for (int i = this->getRowsCount() - 1; i >= 0; ++i)
            retVect[j][i] = this->get(j, i);
    }
    return retVect;
}

const IVectorPtr AbstractMatrix::toVector(bool liveView) {
    return liveView ? IVectorPtr(new VectorMatrixView(this->shared_from_this())) : IVectorPtr(new VectorMatrixView(this->shared_from_this()))->copy();
}

double AbstractMatrix::determinant() const {
    if (this->getColsCount() != this->getRowsCount())
        throw "bad AbstractMatrix::determinant call, matrix must be square";

    if (this->getColsCount() == 1)
        return this->get(0, 0);
    if (this->getColsCount() == 2) {
        return this->get(0, 0) * this->get(1, 1) - this->get(1, 0) * this->get(0, 1);
    }
    double sum = 0;
    for (int excludeCol = this->getColsCount() - 1; excludeCol >= 0; --excludeCol) {
        MatrixSubMatrixView msmv = MatrixSubMatrixView(this->copy()->shared_from_this(), 0, excludeCol);
        sum += ((excludeCol % 2) ? -1 : 1) * msmv.determinant() * this->get(0, excludeCol);
    }
    return sum;
}

const IMatrixPtr AbstractMatrix::subMatrix(int excludeRow, int excludeCol, bool liveView) {
    IMatrixPtr iptr = IMatrixPtr(new MatrixSubMatrixView(this->shared_from_this(), excludeRow, excludeCol));
    return liveView ? iptr : iptr->copy();
}

const string AbstractMatrix::toString() const {
    return this->toString(2);
}

const string AbstractMatrix::toString(int precision) const {
    using std::stringstream;

    stringstream strream;
    strream << std::fixed << std::setprecision(precision);
    for (int row = 0; row < this->getRowsCount(); ++row) {
        strream << "[ ";
        for (int col = 0; col < this->getColsCount(); ++col) {
            strream << this->get(row, col) << (col != this->getColsCount() - 1 ? ", " : "]");
        }
        strream << std::endl;
    }
    return strream.str();
}
