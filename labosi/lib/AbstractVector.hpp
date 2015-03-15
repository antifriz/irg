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
#include "IVector.hpp"

class AbstractVector : public IVector {
public:
    AbstractVector(){};

    virtual double get(const int) const = 0;

    virtual IVector & set(const int, const double) const = 0;

    virtual int getDimension() const = 0;

    virtual IVector copy() const = 0;

    virtual IVector newInstance(const int) const = 0;

    IVector copyPart(const int) const;

    const IVector & add(const IVector&);

    IVector nAdd(const IVector&) const;

    const IVector & sub(const IVector&);

    IVector nSub(const IVector&) const;

    const IVector & scalarMultiply(const double);

    IVector nScalarMultiply(const double) const;

    double norm() const;

    const IVector & normalize();

    double cosine(const IVector&) const;

    double scalarProduct(const IVector&) const;

    IVector nVectorProduct(const IVector&) const;

    IVector nFromHomogeneous() const;

    IMatrix toRowMatrix(const bool) const;

    IMatrix toColumnMatrix(const bool) const;

    std::vector<double> toArray() const;
};

#endif
