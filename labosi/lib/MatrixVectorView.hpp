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

#include "IVector.hpp"
#include "AbstractMatrix.hpp"

class MatrixVectorView : public AbstractMatrix{
private:
    bool asRowMatrix;
    IVector & original;
public:
    MatrixVectorView(const IVector & original,const bool asRowMatrix): original(original), asRowMatrix(asRowMatrix){}
    virtual int getRowsCount() const;
    virtual int getColsCount() const;
    virtual double get(const int, const int) const;
    virtual const IMatrix & set(const int, const int, const double);
    virtual IMatrix copy() const;
    virtual IMatrix newInstance(const int, const int) const;
};

#endif
