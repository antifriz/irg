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

const IVector& AbstractVector::add(const IVector& other) {
    if (this->getDimension() != other.getDimension())
        throw "bad AbstractVector::add() call; cannot add vectors with different dimension";

    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) + other.get(i));
    return *this;
}

IVector AbstractVector::nAdd(const IVector& other) const {
    return this->copy().add(other);
}

const IVector& AbstractVector::sub(const IVector& other) {
    if (this->getDimension() != other.getDimension())
        throw "bad AbstractVector::add() call; cannot add vectors with different dimension";

    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) - other.get(i));
    return *this;
}

IVector AbstractVector::nSub(const IVector& other) const {
    return this->copy().sub(other);
}

const IVector& AbstractVector::scalarMultiply(const double scalar) {
    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) * scalar);
    return *this;
}

IVector AbstractVector::nScalarMultiply(const double scalar) const {
    return this->copy().scalarMultiply(scalar);
}

IVector AbstractVector::nFromHomogeneous() const {
    int dim = this->getDimension();

    IVector retVectPtr = this->copyPart(--dim);

    double divisor = this->get(dim--);
    for (; dim >= 0; dim--)
        retVectPtr.set(dim, retVectPtr.get(dim) / divisor);
    return retVectPtr;
}

IVector AbstractVector::copyPart(int dimension) const {
    int dim = this->getDimension();
    IVector retVectPtr = this->newInstance(dimension);

    for (int i = 0; i < dim && i < dimension; i++)
        retVectPtr.set(i, this->get(i));

    for (int i = dim; i < dimension; i++)
        retVectPtr.set(i, 0);
    return retVectPtr;
}

double AbstractVector::norm() const {
    return 0;
}

IVector & AbstractVector::normalize() const {
    return <#initializer#>;
}

double AbstractVector::cosine(IVector const& aConst) const {
    return 0;
}

double AbstractVector::scalarProduct(IVector const& aConst) const {
    return 0;
}

IVector AbstractVector::nVectorProduct(IVector const& aConst) const {
    return IVector();
}

IMatrix AbstractVector::toRowMatrix(bool const i) const {
    return IMatrix();
}

IMatrix AbstractVector::toColumnMatrix(bool const i) const {
    return IMatrix();
}

std::vector<double> AbstractVector::toArray() const {
    return std::vector::<double>();
}
