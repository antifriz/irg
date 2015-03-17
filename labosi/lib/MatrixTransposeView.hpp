/*
* IRG VJ 1
* MatrixTransposeView.hpp
*
* Class MatrixTransposeView declaration, declares implementation of IMatrix interface
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef MATRIX_TRANSPOSE_VIEW_H_
#define MATRIX_TRANSPOSE_VIEW_H_

#include <vector>
#include <string>
#include "AbstractMatrix.hpp"

class MatrixTransposeView : public AbstractMatrix {
protected:
    IMatrixPtr original;
public:
    MatrixTransposeView(const IMatrixPtr original) : original(original) {
    }


    virtual int getRowsCount() const {
        return original->getColsCount();
    }

    virtual int getColsCount() const {
        return original->getRowsCount();
    }


    virtual double get(const int row, const int col) const {
        return original->get(col, row);
    };

    virtual const IMatrixPtr set(int row, int col, double val) {
        this->original->set(col, row, val);
        return this->shared_from_this();
    }


    virtual const IMatrixPtr copy() const;

    virtual const IMatrixPtr newInstance(int row, int col) const {
        return this->original->newInstance(col, row);
    }


    virtual vector<vector<double>> toArray();
};

#endif

