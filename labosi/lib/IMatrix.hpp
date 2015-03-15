/*
* IRG VJ 1
* IVector.hpp
*
* Interface IMatrix declaration, contains declarations of all methods that matrix implementation must contain
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef I_MATRIX_H_
#define I_MATRIX_H_

#include <vector>
#include "IVector.hpp"

class IMatrix {
public:
    virtual int getRowsCount() const = 0;

    virtual int getColsCount() const = 0;

    virtual double get(const int, const int) const = 0;

    virtual const IMatrix &set(const int, const int, const double) = 0;

    virtual IMatrix copy() const = 0;

    virtual IMatrix newInstance(const int, const int) const = 0;

    virtual IMatrix nTranspose(const bool) const = 0;

    virtual const IMatrix &add(const IMatrix &) = 0;

    virtual IMatrix nAdd(const IMatrix &) const = 0;

    virtual const IMatrix &sub(const IMatrix &) = 0;

    virtual IMatrix nSub(const IMatrix &) const = 0;

    virtual IMatrix nMultiply(const IMatrix &) const = 0;

    virtual double determinant() const = 0;

    virtual IMatrix subMatrix(const int, const int, const bool) const = 0;

    virtual IMatrix nInvert() const = 0;

    virtual std::vector<std::vector<double>> toArray() const = 0;

    virtual IVector toVector(const bool) const = 0;
};

#endif