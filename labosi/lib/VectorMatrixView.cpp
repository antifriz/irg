/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Class MatrixVectorView declaration, declares view of vector as matrix
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#include "VectorMatrixView.hpp"
#include "Vector.hpp"

double VectorMatrixView::get(int const idx) const {
    return this->rowMatrix ? this->original.get(0, idx) : this->original.get(idx, 0);
}

const IVector& VectorMatrixView::set(int const idx, double const val) const {
    this->rowMatrix ? this->original.set(0, idx, val) : this->original.set(idx, 0, val);
    return *this;
}

int VectorMatrixView::getDimension() const {
    return this->dimension;
}

IVector VectorMatrixView::copy() const {
    return Vector(this->toArray());
}

IVector VectorMatrixView::newInstance() const {
    throw "nema smisla";
}

VectorMatrixView::VectorMatrixView(const IMatrix& original)
        : original(original) {
    if (this->original.getColsCount() == 1) {
        this->rowMatrix = true;
        this->dimension = original.getColsCount();
    } else if (this->original.getRowsCount() == 1) {
        this->rowMatrix = false;
        this->dimension = original.getRowsCount();
    } else
        throw "bad VectorMatrixView initialization, matrix must be 1xN or Nx1";
}
