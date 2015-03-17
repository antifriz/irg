/*
* IRG VJ 1
* MatrixTransposeView.hpp
*
* Class MatrixTransposeView declaration, declares implementation of IMatrix interface
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef MATRIX_SUB_MATRIX_VIEW_H_
#define MATRIX_SUB_MATRIX_VIEW_H_

#include <vector>
#include <string>
#include <memory>
#include "AbstractMatrix.hpp"

using std::vector;
using std::shared_ptr;

class MatrixSubMatrixView : public AbstractMatrix {
protected:
    const IMatrixPtr original;
    const int excludedCol;
    const int excludedRow;

public:
    MatrixSubMatrixView(const IMatrixPtr original, int excludedRow, int excludedCol)
            : original(original), excludedCol(excludedCol), excludedRow(excludedRow) {
    }
    virtual int getRowsCount() const {
        return this->original->getRowsCount() - 1;
    }

    virtual int getColsCount() const {
        return this->original->getColsCount() - 1;
    }


    virtual double get(int, int) const;

    virtual const IMatrixPtr set(int, int, double);


    virtual const IMatrixPtr copy() const;

    virtual const IMatrixPtr newInstance(int row, int col) const {
        return this->original->newInstance(row, col);
    };


    virtual const IMatrixPtr subMatrix(const int row, const int col, const bool liveView) const {
        return this->copy()->subMatrix(row, col, liveView)->copy();
    }
};

#endif

