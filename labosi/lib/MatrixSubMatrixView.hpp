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
    IMatrix& original;

    vector<int> rowIndexes;
    vector<int> colIndexes;

    MatrixSubMatrixView(const MatrixSubMatrixView& matrix)
            : original(matrix.original),rowIndexes(matrix.rowIndexes),colIndexes(matrix.colIndexes) {
    }


    MatrixSubMatrixView(const IMatrix& original, vector<int> cols, vector<int> rows)
            : original(original), rowIndexes(rows), colIndexes(cols) {
    }


public:
    MatrixSubMatrixView(const IMatrix& original, int excludingCol, int excludingRow);

    virtual int getRowsCount() const {
        return (int) this->rowIndexes.size();
    }

    virtual int getColsCount() const {
        return (int) this->colIndexes.size();
    }

    virtual double get(const int col, const int row) const;

    virtual const IMatrix& set(const int, const int, const double);

    virtual IMatrix copy() const {
        return MatrixSubMatrixView(*this);
    };

    virtual IMatrix newInstance(const int, const int) const;

    virtual IMatrix subMatrix(const int, const int,const bool) const;

    virtual std::vector<std::vector<double>> toArray();
};

#endif

