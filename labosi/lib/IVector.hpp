/*
* IRG VJ 1
* IVector.hpp
*
* Interface IVector declaration, contains declarations of all methods that vector implementation must contain
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#ifndef I_VECTOR_H_
#define I_VECTOR_H_

#include <vector>

#include "IMatrix.hpp"

class IVector {
public:
    /*
    * Gets vector element at given index
    */
    virtual double get(const int) const = 0;

    /*
    * sets vector element at given index
    */
    virtual const IVector & set(const int,const double) = 0;

    /*
    * gets vector dimension
    */
    virtual int getDimension() const = 0;

    /*
    * copies vector to a new instance
    */
    virtual IVector copy() const = 0;

    /*
    * copies first N vector elements
    * if N >= vector dimension, zeroes the rest of elements
    */
    virtual IVector copyPart(const int) const = 0;

    /*
    * creates a new instance of vector with given dimension
    */
    virtual IVector newInstance(const int) const = 0;

    /*
    * adds given vector to this vector
    * throws exception if vectors dimensions do not match
    */
    virtual const IVector & add(const IVector&) = 0;

    /*
    * add to a new vector
    * see add
    */
    virtual IVector nAdd(const IVector&) const = 0;

    /*
    * subtracts given vector from this vector
    * throws exception if vectors dimensions do not match
    */
    virtual const IVector & sub(const IVector&) = 0;

    /*
    * sub to a new vector
    * see sub
    */
    virtual IVector nSub(const IVector&) const= 0;

    /*
    * multiplies vector with given scalar
    */
    virtual const IVector & scalarMultiply(const double) = 0;

    /*
    * scalarMultiply to a new vector
    * see scalarMultiply
    */
    virtual IVector nScalarMultiply(const double) const = 0;

    virtual double norm() const = 0;

    virtual const IVector & normalize() const = 0;

    virtual double cosine(const IVector&) const = 0;

    virtual double scalarProduct(const IVector&) const = 0;

    virtual IVector nVectorProduct(const IVector&) const = 0;

    /*
    * creates new vector from this as homogeneous
    */
    virtual IVector nFromHomogeneous() const = 0;

    virtual IMatrix toRowMatrix(const bool) const = 0;

    virtual IMatrix toColumnMatrix(const bool) const = 0;

    virtual std::vector<double> toArray() const = 0;
};

#endif