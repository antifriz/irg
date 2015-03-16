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

class VectorMatrixView : public AbstractVector {
private:
    bool rowMatrix;
    int dimension;
    IMatrix &original;
public:
    VectorMatrixView(const IMatrix &original);

    double get(const int) const;

    const IVector &set(const int, const double) const;

    int getDimension() const;

    IVector copy() const;

    IVector newInstance(const int) const;
};

#endif
