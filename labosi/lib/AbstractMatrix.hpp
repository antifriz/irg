/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Abstract class AbstracMatrix declaration, declares common matrix methods
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef ABSTRACT_MATRIX_H_
#define ABSTRACT_MATRIX_H_

#include <vector>
#include <memory>
#include "IMatrix.hpp"

using std::shared_ptr;
using std::vector;
using std::string;

class AbstractMatrix : public IMatrix {
public:
    typedef shared_ptr<AbstractMatrix> AbstractMatrixPtr;

    virtual int getRowsCount() const = 0;

    virtual int getColsCount() const = 0;

    virtual double get(int, int) const = 0;

    virtual const IMatrixPtr set(int, int, double) = 0;

    virtual const IMatrixPtr copy() const = 0;

    virtual const IMatrixPtr newInstance(int, int) const = 0;


    virtual const IMatrixPtr nTranspose(bool);

    virtual const IMatrixPtr add(const IMatrixPtr);

    virtual const IMatrixPtr nAdd(const IMatrixPtr) const;

    virtual const IMatrixPtr sub(const IMatrixPtr);

    virtual const IMatrixPtr nSub(const IMatrixPtr) const;

    virtual const IMatrixPtr nMultiply(const IMatrixPtr) const;

    virtual double determinant() const;

    virtual const IMatrixPtr subMatrix(int, int, bool);

    virtual const IMatrixPtr nInvert() const;

    virtual vector<vector<double>> toArray() const;

    virtual const IVectorPtr toVector(bool);


    virtual const string toString() const;

    virtual const string toString(int) const;

    IMatrixPtr const multiplyByConstant(double constant);
};

typedef shared_ptr<AbstractMatrix> AbstractMatrixPtr;

#endif
