/*
* IRG VJ 1
* AbstractVector.hpp
*
* Abstract class AbstractVector declaration, declares common vector methods
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

#endif

#include "IVector.hpp"

class AbstractVector : public IVector {
public:
    virtual double get(int) = 0;

    virtual IVector * set(int, double) = 0;

    virtual int getDimension() = 0;

    virtual IVector * copy() = 0;

    virtual IVector * newInstance(int) = 0;

    IVector * copyPart(int);

    IVector * add(IVector&);

    IVector * nAdd(IVector&);

    IVector * sub(IVector&);

    IVector * nSub(IVector&);

    IVector * scalarMultiply(double);

    IVector * nScalarMultiply(double);

    /*
    double norm();

    IVector normalize();

    double cosine(IVector&);

    double scalarProduct(IVector&);

    IVector nVectorProduct(IVector&);
    */

    IVector * nFromHomogeneous();

    /*
    IMatrix toRowMatrix(bool);

    IMatrix toColumnMatrix(bool);

    std::vector<double> toArray();
    */
};