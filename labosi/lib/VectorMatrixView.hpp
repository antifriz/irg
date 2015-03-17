/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Class VectorMatrixView declaration, declares view of matrix as vector
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef VECTOR_MATRIX_VIEW_H_
#define VECTOR_MATRIX_VIEW_H_


#include "AbstractVector.hpp"
#include "IMatrix.hpp"

class VectorMatrixView : public AbstractVector {
private:
    bool rowMatrix;
    int dimension;
    IMatrixPtr original;
public:
    VectorMatrixView(const IMatrixPtr original);

    double get(int) const;

    const IVectorPtr set(int, double);

    int getDimension() const;

    const IVectorPtr copy() const;

    const IVectorPtr newInstance(int) const;


    virtual const string toString(int i) const;
};

#endif
