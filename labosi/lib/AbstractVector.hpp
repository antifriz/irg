/*
* IRG VJ 1
* AbstractVector.hpp
*
* Abstract class AbstractVector declaration, declares common vector methods
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#ifndef ABSTRACT_VECTOR_H_
#define ABSTRACT_VECTOR_H_

#include <vector>
#include <memory>
#include "IVector.hpp"

using std::shared_ptr;
using std::vector;

class AbstractVector : public IVector {
public:
    AbstractVector() {
    };

    virtual double get(int) const = 0;

    virtual const IVectorPtr set(int, double) = 0;

    virtual int getDimension() const = 0;

    virtual const IVectorPtr copy() const = 0;

    virtual const IVectorPtr newInstance(int) const = 0;


    const IVectorPtr copyPart(int) const;

    const IVectorPtr add(const IVectorPtr);

    const IVectorPtr nAdd(const IVectorPtr) const;

    const IVectorPtr sub(const IVectorPtr);

    const IVectorPtr nSub(const IVectorPtr) const;

    const IVectorPtr scalarMultiply(double);

    const IVectorPtr nScalarMultiply(double) const;

    double norm() const;

    const IVectorPtr normalize();

    double cosine(const IVectorPtr) const;

    double scalarProduct(const IVectorPtr) const;

    const IVectorPtr nVectorProduct(const IVectorPtr) const;

    const IVectorPtr nFromHomogeneous() const;

    //IMatrix toRowMatrix(const bool) const;

    //IMatrix toColumnMatrix(const bool) const;

    vector<double> toArray() const;
};

#endif
