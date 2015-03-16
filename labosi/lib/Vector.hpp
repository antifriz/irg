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
#include "AbstractVector.hpp"

#define VECTOR_H_READONLY_DEFAULT false
#define VECTOR_H_IMMUTABLE_DEFAULT true

using std::vector;

class Vector : public AbstractVector {
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
    Vector::Vector(const bool readOnly, const bool inputImmutable, const vector<double> &inputArray)
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
    double get(const int idx) const {
        return elements[idx];
    }

    /*
    * if vector is not readonly sets value at given index, else throws exception
    */
    const IVector &set(const int, const double);


    /*
    * gets vector dimension
    */
    int getDimension() const {
        return dimension;
    }


    /*
    * creates copy of this vector
    */
    IVector copy() const {
        return Vector(readOnly, true, this->elements);
    }

    /*
    * creates new instance of Vector with given dimension
    */
    IVector newInstance(const int dimension) const {
        return Vector(vector<double>((unsigned int) dimension));
    }


    /*
    * creates new instance of Vector with given string
    */
    static Vector parseSimple(const std::string);

};

#endif

