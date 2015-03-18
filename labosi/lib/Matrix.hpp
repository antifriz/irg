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
using std::string;

class Matrix : public AbstractMatrix {
protected:
    int cols;
    int rows;
    vector<vector<double>> elements;
public:
    typedef shared_ptr<Matrix> MatrixPtr;

    Matrix(const int, const int);

    /*
    * rawData is representation of matrix, constructor always copies the rawData into Matrix class
    */
    Matrix(int rows, int cols, const vector<vector<double>> &rawData, bool)
            : cols(cols), rows(rows), elements(rawData) {
    };


    virtual int getRowsCount() const {
        return rows;
    }

    virtual int getColsCount() const {
        return cols;
    }


    virtual double get(int row, int col) const {
        return elements[col][row];
    };

    virtual const IMatrixPtr set(int row, int col, double val) {
        elements[col][row] = val;
        return this->shared_from_this();
    }


    virtual const IMatrixPtr copy() const;

    virtual const IMatrixPtr newInstance(int, int) const;


    static const MatrixPtr parseSimple(const string str);

    virtual const string whoAmI() const {
        return "Matrix";
    }
};

typedef shared_ptr<Matrix> MatrixPtr;

#endif
