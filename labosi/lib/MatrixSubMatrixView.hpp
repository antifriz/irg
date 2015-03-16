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
#include "AbstractMatrix.hpp"

using std::vector;

class MatrixSubMatrixView : public AbstractMatrix {
protected:
    IMatrix &original;
    int excludedRow;
    int excludedCol;

public:
    MatrixSubMatrixView(const IMatrix &original, const int excludedCol, const int excludedRow)
            : original(original), excludedRow(excludedRow), excludedCol(excludedCol) {
    }
    virtual int getRowsCount() const {
        return this->original.getRowsCount() - 1;
    }

    virtual int getColsCount() const {
        return this->original.getColsCount() - 1;
    }


    virtual double get(const int, const int) const;

    virtual const IMatrix &set(const int, const int, const double);


    virtual IMatrix copy() const;

    virtual IMatrix newInstance(const int col, const int row) const {
        return this->original.newInstance(col, row);
    };


    virtual IMatrix subMatrix(const int col, const int row, const bool liveView) const {
        return this->copy().subMatrix(col, row, liveView).copy();
    }
};

#endif

