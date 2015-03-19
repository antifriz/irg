/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Class MatrixVectorView declaration, declares view of vector as matrix
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/

#include <iostream>
#include "MatrixVectorView.hpp"
#include "Matrix.hpp"

int MatrixVectorView::getColsCount() const {
    return this->asRowMatrix ? this->original->getDimension() : 1;
}

int MatrixVectorView::getRowsCount() const {
    return !this->asRowMatrix ? this->original->getDimension() : 1;
}

double MatrixVectorView::get(int row, int col) const {
    return this->original->get(col > row ? col : row);
}

const IMatrixPtr MatrixVectorView::set(int row, int col, double val) {
    this->original->set(col > row ? col : row, val);
    return this->shared_from_this();
}

const IMatrixPtr MatrixVectorView::copy() const {
    IMatrixPtr retMatrixPtr = IMatrixPtr(new Matrix(this->original->getDimension(), 1));

    for (int i = this->original->getDimension() - 1; i >= 0; --i)
        retMatrixPtr->set(i, 0, this->original->get(i));

    return this->asRowMatrix ? retMatrixPtr : retMatrixPtr->nTranspose(false);
}

const IMatrixPtr MatrixVectorView::newInstance(int rows, int cols) const {
    return IMatrixPtr(new Matrix(rows, cols));
}
