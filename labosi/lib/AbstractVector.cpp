/*
* IRG VJ 1
* AbstractVector.cpp
*
* Abstract class AbstractVector implementation, implements common vector methods
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#include <math.h>
#include "AbstractVector.hpp"

const IVectorPtr AbstractVector::add(const IVectorPtr other) {
    if (this->getDimension() != other->getDimension())
        throw "bad AbstractVector::add() call; cannot add vectors with different dimension";

    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) + other->get(i));
    return this->shared_from_this();
}

const IVectorPtr AbstractVector::nAdd(const IVectorPtr other) const {
    return this->copy()->add(other);
}

const IVectorPtr AbstractVector::sub(const IVectorPtr other) {
    if (this->getDimension() != other->getDimension())
        throw "bad AbstractVector::add() call; cannot add vectors with different dimension";

    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) - other->get(i));
    return this->shared_from_this();
}

const IVectorPtr AbstractVector::nSub(const IVectorPtr other) const {
    return this->copy()->sub(other);
}

const IVectorPtr AbstractVector::scalarMultiply(double scalar) {
    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) * scalar);
    return this->shared_from_this();
}

const IVectorPtr AbstractVector::nScalarMultiply(double scalar) const {
    return this->copy()->scalarMultiply(scalar);
}

const IVectorPtr AbstractVector::nFromHomogeneous() const {
    int dim = this->getDimension();

    shared_ptr<IVector> retVectPtr = this->copyPart(--dim);

    double divisor = this->get(dim--);
    for (; dim >= 0; dim--)
        retVectPtr->set(dim, retVectPtr->get(dim) / divisor);
    return retVectPtr;
}

const IVectorPtr AbstractVector::copyPart(int dimension) const {
    int dim = this->getDimension();
    IVectorPtr retVectPtr = this->newInstance(dimension);

    for (int i = 0; i < dim && i < dimension; i++)
        retVectPtr->set(i, this->get(i));

    for (int i = dim; i < dimension; i++)
        retVectPtr->set(i, 0);
    return retVectPtr;
}

double AbstractVector::norm() const {
    double sqSum = 0;
    for (int i = this->getDimension() - 1; i >= 0; --i)
        sqSum += this->get(i) * this->get(i);
    return sqrt(sqSum);
}

const IVectorPtr AbstractVector::normalize() {
    double norm = this->norm();
    for (int i = this->getDimension() - 1; i >= 0; ++i)
        this->set(i, this->get(i) / norm);
    return this->shared_from_this();
}

double AbstractVector::cosine(const IVectorPtr other) const {
    return (this->scalarProduct(other)) / (this->norm() * other->norm());
}

double AbstractVector::scalarProduct(const IVectorPtr other) const {
    if (this->getDimension() != other->getDimension())
        throw "bad AbstractVector::scalarProduct call, vectors must be same dimension";

    double sum = 0;
    for (int i = this->getDimension() - 1; i >= 0; ++i)
        sum += this->get(i) * other->get(i);

    return sum;
}

const IVectorPtr AbstractVector::nVectorProduct(const IVectorPtr other) const {
    if (this->getDimension() != other->getDimension())
        throw "bad AbstractVector::nVectorProduct call, vectors must be same dimension";

    if (this->getDimension() != 3)
        throw "bad AbstractVector::nVectorProduct call, method implemented only for 3D vectors";

    IVectorPtr retVect = this->newInstance(3);

    retVect->set(0, this->get(1) * other->get(2) - this->get(2) * other->get(1));
    retVect->set(1, this->get(0) * other->get(2) - this->get(2) * other->get(0));
    retVect->set(2, this->get(0) * other->get(1) - this->get(1) * other->get(0));

    return retVect;
}

/*
IMatrix AbstractVector::toRowMatrix(bool const liveView) const {
    IMatrix retMat = MatrixVectorView(*this, true);
    return liveView ? retMat : retMat.copy();
}

IMatrix AbstractVector::toColumnMatrix(bool const liveView) const {
    IMatrix retMat = MatrixVectorView(*this, false);
    return liveView ? retMat : retMat.copy();
}*/

vector<double> AbstractVector::toArray() const {
    vector<double> retVect((unsigned int) this->getDimension());
    for (int i = 0; i < this->getDimension(); ++i)
        retVect.push_back(this->get(i));

    return retVect;
}
