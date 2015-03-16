/*
* IRG VJ 1
* Vector.hpp
*
* Class Vector declaration, inherits AbstractVector
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>
#include <string>
#include <memory>
#include "AbstractVector.hpp"

#define VECTOR_H_READONLY_DEFAULT false
#define VECTOR_H_IMMUTABLE_DEFAULT true

using std::vector;

class Vector : public AbstractVector, std::enable_shared_from_this<Vector> {
private:
    vector<double> elements;
    int dimension;
    bool readOnly;
public:

    /*
    * constructor which takes three values:
    *   - is vector readonly
    *   - can array be passed by reference // it is ignored so vector always copies input
    *   - array to be initialized with
    */
    Vector::Vector(bool readOnly, bool inputImmutable, const vector<double> &inputArray)
            : dimension((int) inputArray.size()),
              readOnly(readOnly),
              elements(inputArray) {
    }

    /*
    * constructor which takes one value:
    *   - array to be initialized with
    * other options default to defined values
    */
    Vector::Vector(const vector<double> &initializerVector)
            : Vector(VECTOR_H_READONLY_DEFAULT, VECTOR_H_IMMUTABLE_DEFAULT, initializerVector) {
    }


    /*
    * gets vector element at given index
    */
    double get(int idx) const {
        return elements[idx];
    }

    /*
    * if vector is not readonly sets value at given index, else throws exception
    */
    const IVectorPtr set(int, double);


    /*
    * gets vector dimension
    */
    int getDimension() const {
        return dimension;
    }


    /*
    * creates copy of this vector
    */
    const IVectorPtr copy() const {
        return IVectorPtr(new Vector(readOnly, true, this->elements));
    }

    /*
    * creates new instance of Vector with given dimension
    */
    const IVectorPtr newInstance(int dimension) const {
        return IVectorPtr(new Vector(vector<double>((unsigned int) dimension)));
    }


    /*
    * creates new instance of Vector with given string
    */
    static Vector parseSimple(const std::string);

};

#endif

