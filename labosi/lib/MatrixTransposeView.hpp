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
    IMatrix &original;
public:
    MatrixTransposeView(const IMatrix &original) : original(original) {
    }


    virtual int getRowsCount() const {
        return original.getColsCount();
    }

    virtual int getColsCount() const {
        return original.getRowsCount();
    }


    virtual double get(const int col, const int row) const {
        return original.get(row, col);
    };

    virtual const IMatrix &set(const int col, const int row, const double val) {
        this->original.set(row, col, val);
        return *this;
    }


    virtual IMatrix copy() const;

    virtual IMatrix newInstance(const int col, const int row) const {
        return this->original.newInstance(col, row);
    }


    virtual std::vector<std::vector<double>> toArray();
};

#endif

