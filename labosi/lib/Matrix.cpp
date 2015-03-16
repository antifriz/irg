/*
* IRG VJ 1
* Matrix.hpp
*
* Class Matrix definition
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#include <vector>
#include <string>
#include "Matrix.hpp"



const IMatrix& Matrix::set(int const col, int const row, double const val) {
    elements[col][row] = val;
    return *this;
}

IMatrix Matrix::copy() const {
    return IMatrix();
}

IMatrix Matrix::newInstance(int const i, int const i1) const {
    return IMatrix();
}

Matrix Matrix::parseSimple(const std::string str) {
    return nullptr;
}

Matrix::Matrix(int const i, int const i1) {

}

Matrix::Matrix(int const i, int const i1, std::vector<std::vector<double>> const vector, bool const i2) {

}

Matrix::Matrix(Matrix const& aConst) {

}
