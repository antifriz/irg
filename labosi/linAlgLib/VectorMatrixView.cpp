/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Class MatrixVectorView declaration, declares view of vector as matrix
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/

#include <ostream>
#include <iostream>
#include "VectorMatrixView.hpp"
#include "Vector.hpp"

double VectorMatrixView::get(int const idx) const {
    return this->rowMatrix ? this->original->get(0, idx) : this->original->get(idx, 0);
}

const IVectorPtr VectorMatrixView::set(int const idx, double const val) {
    this->rowMatrix ? this->original->set(0, idx, val) : this->original->set(idx, 0, val);
    return this->shared_from_this();
}

int VectorMatrixView::getDimension() const {
    return this->dimension;
}

const IVectorPtr VectorMatrixView::copy() const {
    IVectorPtr retVect = IVectorPtr(new Vector(std::vector<double>((unsigned int) this->dimension)));

    for (int i = this->dimension - 1; i >= 0; --i)
        retVect->set(i, this->get(i));

    return retVect;
}

const IVectorPtr VectorMatrixView::newInstance(const int dimension) const {
    return IVectorPtr(new Vector(std::vector<double>((unsigned int) dimension)));
}

VectorMatrixView::VectorMatrixView(const IMatrixPtr original)
        : original(original) {
    if (this->original->getColsCount() == 1) {
        this->rowMatrix = false;
        this->dimension = original->getRowsCount();
    } else if (this->original->getRowsCount() == 1) {
        this->rowMatrix = true;
        this->dimension = original->getColsCount();
    } else
        throw "bad VectorMatrixView initialization, matrix must be 1xN or Nx1";
}

const string VectorMatrixView::toString(int precision) const {
    return this->original->toString(precision);
}
