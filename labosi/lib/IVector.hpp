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
#include <memory>

//#include "IMatrix.hpp"

using std::shared_ptr;
using std::vector;
using std::string;


class IVector : public std::enable_shared_from_this<IVector> {
public:
    typedef shared_ptr<IVector> IVectorPtr;

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

    //   virtual IMatrix toRowMatrix(const bool) const = 0;

    //   virtual IMatrix toColumnMatrix(const bool) const = 0;

    virtual vector<double> toArray() const = 0;


    virtual const string toString() const = 0;

    virtual const string toString(int) const = 0;
};

typedef shared_ptr<IVector> IVectorPtr;


#endif