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

#include "AbstractMatrix.hpp"

class Matrix : public AbstractMatrix {
protected:
    int cols;
    int rows;
    std::vector<std::vector<double>> elements;
public:
    typedef std::shared_ptr<Matrix> MatrixPtr;

    Matrix(int, int);

    /*
    * rawData is representation of matrix, constructor always copies the rawData into Matrix class
    */
    Matrix(int rows, int cols, const std::vector<std::vector<double>> &rawData, bool)
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


    static const MatrixPtr parseSimple(const std::string str);

    virtual const std::string whoAmI() const {
        return "Matrix";
    }

    static MatrixPtr fromContainerOfVectors( const std::vector<IVectorPtr> container,bool rowVectors);
    static std::vector<IVectorPtr> toContainerOfVectors(const IMatrixPtr & matrix, bool rowVectors);
};

typedef std::shared_ptr<Matrix> MatrixPtr;

#endif
