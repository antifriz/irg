/*
* IRG VJ 1
* AbstractMatrix.hpp
*
* Abstract class AbstracMatrix declaration, declares common matrix methods
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef ABSTRACT_MATRIX_H_
#define ABSTRACT_MATRIX_H_

#include <vector>
#include <string>
#include "IMatrix.hpp"

class AbstractMatrix : public IMatrix {
public:
    virtual int getRowsCount() const = 0;

    virtual int getColsCount() const = 0;

    virtual double get(const int, const int) const = 0;

    virtual const IMatrix &set(const int, const int, const double) = 0;

    virtual IMatrix copy() const = 0;

    virtual IMatrix newInstance(const int, const int) const = 0;



    virtual IMatrix nTranspose(const bool) const;

    virtual const IMatrix &add(const IMatrix &);

    virtual IMatrix nAdd(const IMatrix &) const;

    virtual const IMatrix &sub(const IMatrix &);

    virtual IMatrix nSub(const IMatrix &) const;

    virtual IMatrix nMultiply(const IMatrix &) const;

    virtual double determinant() const;

    virtual IMatrix subMatrix(const int, const int, const bool) const;

    virtual IMatrix nInvert() const;

    virtual std::vector<std::vector<double>> toArray() const;

    virtual IVector toVector(const bool) const;


    virtual std::string toString() const;

    virtual std::string toString(const int) const;
};

#endif
