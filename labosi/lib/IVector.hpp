/*
* IRG VJ 1
* IVector.hpp
*
* Interface IVector declaration, contains declarations of all methods that vector implementation must contain
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

#include "IMatrix.hpp"

class IVector {
public:
    /*
    * Gets vector element at given index
    */
    virtual double get(int) = 0;

    /*
    * sets vector element at given index
    */
    virtual IVector * set(int, double) = 0;

    /*
    * gets vector dimension
    */
    virtual int getDimension() = 0;

    /*
    * copies vector to a new instance
    */
    virtual IVector * copy() = 0;

    /*
    * copies first N vector elements
    * if N >= vector dimension, zeroes the rest of elements
    */
    virtual IVector * copyPart(int) = 0;

    /*
    * creates a new instance of vector with given dimension
    */
    virtual IVector * newInstance(int) = 0;

    /*
    * adds given vector to this vector
    * throws exception if vectors dimensions do not match
    */
    virtual IVector * add(IVector&) = 0;

    /*
    * add to a new vector
    * see add
    */
    virtual IVector * nAdd(IVector&) = 0;

    /*
    * subtracts given vector from this vector
    * throws exception if vectors dimensions do not match
    */
    virtual IVector * sub(IVector&) = 0;

    /*
    * sub to a new vector
    * see sub
    */
    virtual IVector * nSub(IVector&) = 0;

    /*
    * multiplies vector with given scalar
    */
    virtual IVector * scalarMultiply(double) = 0;

    /*
    * scalarMultiply to a new vector
    * see scalarMultiply
    */
    virtual IVector * nScalarMultiply(double) = 0;

    /*
    virtual double norm() = 0;

    virtual IVector normalize() = 0;

    virtual double cosine(IVector&) = 0;

    virtual double scalarProduct(IVector&) = 0;

    virtual IVector nVectorProduct(IVector&) = 0;
*/

    /*
    * creates new vector from this as homogeneous
    */
    virtual IVector nFromHomogeneous() = 0;

    /*
    virtual IMatrix toRowMatrix(bool) = 0;

    virtual IMatrix toColumnMatrix(bool) = 0;

    virtual std::vector<double> toArray() = 0;
    */
};