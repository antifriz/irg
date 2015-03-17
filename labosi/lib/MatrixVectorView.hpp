/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Class MatrixVectorView declaration, declares view of vector as matrix
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef MATRIX_VECTOR_VIEW_H_
#define MATRIX_VECTOR_VIEW_H_


#include "AbstractMatrix.hpp"

class MatrixVectorView : public AbstractMatrix {
private:
    IVectorPtr original;
    bool asRowMatrix;

public:
    MatrixVectorView(const IVectorPtr original, const bool asRowMatrix) : original(original), asRowMatrix(asRowMatrix) {
    }

    virtual int getRowsCount() const;

    virtual int getColsCount() const;

    virtual double get(int, int) const;

    virtual const IMatrixPtr set(int, int, double);

    virtual const IMatrixPtr copy() const;

    virtual const IMatrixPtr newInstance(int, int) const;
};

#endif
