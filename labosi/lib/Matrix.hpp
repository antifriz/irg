/*
* IRG VJ 1
* Matrix.hpp
*
* Class Matrix declaration, declares implementation of IMatrix interface
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <string>
#include "AbstractMatrix.hpp"

class Matrix : public AbstractMatrix {
protected:
    std::vector<std::vector<double>> elements;
    int rows;
    int cols;
    Matrix(const Matrix &);
public:
    Matrix(const int,const int);

    Matrix(const int, const int, const std::vector<std::vector<double>>,const bool);


    virtual int getRowsCount() const {
        return rows;
    }

    virtual int getColsCount() const {
        return cols;
    }

    virtual double get(const int col, const int row) const {
        return elements[col][row];
    };

    virtual const IMatrix& set(const int, const int, const double);

    virtual IMatrix copy() const;

    virtual IMatrix newInstance(const int, const int) const;

    static Matrix parseSimple(const std::string str);
};

#endif
