/*
* IRG VJ 1
* Vector.hpp
*
* Class Vector declaration, inherits AbstractVector
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

#endif

#ifndef STDEXCEPT_H
#define STDEXCEPT_H

#include <stdexcept>

#endif

#include "AbstractVector.hpp"

class Vector : public AbstractVector {
private:
    std::vector<double> *elements;
    int dimension;
    bool readOnly = false;
public:
    Vector::Vector(std::vector<double>& inputArray)
            : dimension((int) inputArray.size()),
              elements(new std::vector<double>(inputArray)) {
    }

    Vector(bool readOnly, bool inputImmutable, std::vector<double>& inputArray)
            : readOnly(readOnly),
              elements(inputImmutable ? new std::vector<double>(inputArray) : &inputArray) {
    }

    double get(int idx) {
        return (*elements)[idx];
    };

    IVector *set(int idx, double value) {
        return readOnly ? (throw std::runtime_error("vector is readonly")) : (*elements)[idx] = value;
    };

    int getDimension() {
        return dimension;
    };

    IVector *copy() {
        return new Vector(readOnly, true, *elements);
    };

    IVector *newInstance(int dimension) {
        return new Vector(*(new std::vector<double>(dimension, 0)));
    };

    /*
    IVector copyPart(int dimension){return AbstractVector::copyPart(dimension);};

    IVector add(IVector& other){return AbstractVector::add(other)};

    IVector nAdd(IVector& other){AbstractVector::nAdd()};

    IVector sub(IVector&);

    IVector nSub(IVector&);

    IVector scalarMultiply(double);

    IVector nScalarMultiply(double);

    double norm();

    IVector normalize();

    double cosine(IVector&);

    double scalarProduct(IVector&);

    IVector nVectorProduct(IVector&);

    IVector nFromHomogeneous();

    IMatrix toRowMatrix(bool);

    IMatrix toColumnMatrix(bool);

    std::vector<double> toArray();*/
};