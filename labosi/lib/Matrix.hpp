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

using std::vector;

class Matrix : public AbstractMatrix {
protected:
    vector<vector<double>> elements;
    int rows;
    int cols;
public:
    Matrix(const int, const int);

    /*
    * rawData is representation of matrix, constructor always copies the rawData into Matrix class
    */
    Matrix(const int rows, const int cols, const vector<vector<double>> &rawData, const bool)
            : rows(rows), cols(cols), elements(rawData) {
    };


    virtual int getRowsCount() const {
        return rows;
    }

    virtual int getColsCount() const {
        return cols;
    }


    virtual double get(const int col, const int row) const {
        return elements[col][row];
    };

    virtual const IMatrix &set(const int col, const int row, const double val) {
        elements[col][row] = val;
        return *this;
    }


    virtual IMatrix copy() const;

    virtual IMatrix newInstance(const int, const int) const;


    static Matrix parseSimple(const std::string str);
};

#endif
