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
    IMatrix & original;
    MatrixTransposeView(const MatrixTransposeView & matrix):original(matrix.original){}
public:
    MatrixTransposeView(const IMatrix & original): original(original){}

    virtual int getRowsCount() const {
        return original.getColsCount();
    }

    virtual int getColsCount() const {
        return original.getRowsCount();
    }

    virtual double get(const int col, const int row) const {
        return original.get(row,col);
    };

    virtual const IMatrix& set(const int, const int, const double);

    virtual IMatrix copy() const{ return MatrixTransposeView(*this);};

    virtual IMatrix newInstance(const int, const int) const;

    virtual std::vector<std::vector<double>> toArray();
};

#endif

