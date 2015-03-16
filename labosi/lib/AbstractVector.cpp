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

const IVector &AbstractVector::add(const IVector &other) {
    if (this->getDimension() != other.getDimension())
        throw "bad AbstractVector::add() call; cannot add vectors with different dimension";

    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) + other.get(i));
    return *this;
}

IVector AbstractVector::nAdd(const IVector &other) const {
    return this->copy().add(other);
}

const IVector &AbstractVector::sub(const IVector &other) {
    if (this->getDimension() != other.getDimension())
        throw "bad AbstractVector::add() call; cannot add vectors with different dimension";

    for (int i = this->getDimension() - 1; i >= 0; i--)
        this->set(i, this->get(i) - other.get(i));
    return *this;
}

IVector AbstractVector::nSub(const IVector &other) const {
    return this->copy().sub(other);
}

const IVector &AbstractVector::scalarMultiply(const double scalar) {
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
    double sqSum = 0;
    for (int i = this->getDimension() - 1; i >= 0; --i)
        sqSum += this->get(i) * this->get(i);
    return sqrt(sqSum);
}

IVector const &AbstractVector::normalize() {
    double norm = this->norm();
    for (int i = this->getDimension() - 1; i >= 0; ++i)
        this->set(i, this->get(i) / norm);
    return *this;
}

double AbstractVector::cosine(IVector const &other) const {
    return (this->scalarProduct(other)) / (this->norm() * other.norm());
}

double AbstractVector::scalarProduct(IVector const &other) const {
    if (this->getDimension() != other.getDimension())
        throw "bad AbstractVector::scalarProduct call, vectors must be same dimension";

    double sum = 0;
    for (int i = this->getDimension() - 1; i >= 0; ++i)
        sum += this->get(i) * other.get(i);

    return sum;
}

IVector AbstractVector::nVectorProduct(IVector const &other) const {
    if (this->getDimension() != other.getDimension())
        throw "bad AbstractVector::nVectorProduct call, vectors must be same dimension";

    if (this->getDimension() != 3)
        throw "bad AbstractVector::nVectorProduct call, method implemented only for 3D vectors";

    IVector retVect = this->newInstance(3);

    retVect.set(0, this->get(1) * other.get(2) - this->get(2) * other.get(1));
    retVect.set(1, this->get(0) * other.get(2) - this->get(2) * other.get(0));
    retVect.set(2, this->get(0) * other.get(1) - this->get(1) * other.get(0));

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

std::vector<double> AbstractVector::toArray() const {
    std::vector<double> retVect((unsigned int) this->getDimension());
    for (int i = 0; i < this->getDimension(); ++i)
        retVect.push_back(this->get(i));

    return retVect;
}
