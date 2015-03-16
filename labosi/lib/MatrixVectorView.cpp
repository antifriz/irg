/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Class MatrixVectorView declaration, declares view of vector as matrix
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/

#include "MatrixVectorView.hpp"
#include "Matrix.hpp"

int MatrixVectorView::getColsCount() const {
    return this->asRowMatrix ? this->original.getDimension() : 1;
}

int MatrixVectorView::getRowsCount() const {
    return !this->asRowMatrix ? this->original.getDimension() : 1;
}

double MatrixVectorView::get(int const col, int const row) const {
    return this->original.get(col > row ? col : row);
}

const IMatrix &MatrixVectorView::set(int const col, int const row, double const val) {
    this->original.set(col > row ? col : row, val);
    return *this;
}

IMatrix MatrixVectorView::copy() const {
    IMatrix retMatrix = Matrix(0, this->original.getDimension());

    for (int i = this->original.getDimension(); i >= 0; --i)
        retMatrix.set(0, i, this->original.get(i));

    return this->asRowMatrix ? retMatrix : retMatrix.nTranspose(false);
}

IMatrix MatrixVectorView::newInstance(int const cols, int const rows) const {
    return Matrix(cols, rows);
}
