/*
* IRG VJ 1
* AbstractVector.cpp
*
* Abstract class AbstractVector implementation, implements common vector methods
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#include "AbstractVector.hpp"

IVector * AbstractVector::add(IVector& other) {
    if (this->getDimension() != other.getDimension())
        throw 1;
    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) + other.get(i));
    return this;
}

IVector * AbstractVector::nAdd(IVector& other) {
    return this->copy()->add(other);
}

IVector * AbstractVector::sub(IVector& other) {
    if (this->getDimension() != other.getDimension())
        throw 1;
    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) - other.get(i));
    return this;
}

IVector * AbstractVector::nSub(IVector& other) {
    return this->copy()->sub(other);
}

IVector * AbstractVector::scalarMultiply(double scalar) {
    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) * scalar);
    return this;
}

IVector * AbstractVector::nScalarMultiply(double scalar) {
    return this->copy()->scalarMultiply(scalar);
}

IVector * AbstractVector::nFromHomogeneous() {
    int dim = this->getDimension();

    IVector * retVectPtr = this->copyPart(--dim);
    double divisor = this->get(dim--);
    for (; dim >= 0; dim--)
        retVectPtr->set(dim, retVectPtr->get(dim) / divisor);
    return retVectPtr;
}

IVector * AbstractVector::copyPart(int dimension) {
    int dim = this->getDimension();
    IVector * retVectPtr = this->newInstance(dimension);
    for (int i = 0; i < dim && i < dimension; i++)
        retVectPtr->set(i, this->get(i));
    for (int i = dim; i < dimension; i++)
        retVectPtr->set(i, 0);
    return retVectPtr;
}

