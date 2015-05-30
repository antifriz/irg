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

#include "ForwardDeclarations.h"
#include "IMatrix.hpp"

class IVector : public std::enable_shared_from_this<IVector> {
public:

    /*
    * Gets vector element at given index
    */
    virtual double get(int) const = 0;

    /*
    * sets vector element at given index
    */
    virtual const IVectorPtr set(int, double) = 0;

    /*
    * gets vector dimension
    */
    virtual int getDimension() const = 0;

    /*
    * copies vector to a new instance
    */
    virtual const IVectorPtr copy() const = 0;

    /*
    * copies first N vector elements
    * if N >= vector dimension, zeroes the rest of elements
    */
    virtual const IVectorPtr copyPart(int) const = 0;

    /*
    * creates a new instance of vector with given dimension
    */
    virtual const IVectorPtr newInstance(int) const = 0;

    /*
    * adds given vector to this vector
    * throws exception if vectors dimensions do not match
    */
    virtual const IVectorPtr add(const IVectorPtr) = 0;

    /*
    * add to a new vector
    * see add
    */
    virtual const IVectorPtr nAdd(const IVectorPtr) const = 0;

    /*
    * subtracts given vector from this vector
    * throws exception if vectors dimensions do not match
    */
    virtual const IVectorPtr sub(const IVectorPtr) = 0;

    /*
    * sub to a new vector
    * see sub
    */
    virtual const IVectorPtr nSub(const IVectorPtr) const = 0;

    /*
    * multiplies vector with given scalar
    */
    virtual const IVectorPtr scalarMultiply(double) = 0;

    /*
    * scalarMultiply to a new vector
    * see scalarMultiply
    */
    virtual const IVectorPtr nScalarMultiply(double) const = 0;

    virtual double norm() const = 0;

    virtual const IVectorPtr normalize() = 0;

    virtual double cosine(const IVectorPtr) const = 0;

    virtual double scalarProduct(const IVectorPtr) const = 0;

    virtual const IVectorPtr nVectorProduct(const IVectorPtr) const = 0;

    /*
    * creates new vector from this as homogeneous
    */
    virtual const IVectorPtr nFromHomogeneous() const = 0;

    virtual const IMatrixPtr toRowMatrix(bool) = 0;

    virtual const IMatrixPtr toColumnMatrix(bool) = 0;

    virtual std::vector<double> toArray() const = 0;


    virtual const std::string toString() const = 0;

    virtual const std::string toString(int) const = 0;

};


#endif