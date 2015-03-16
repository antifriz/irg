/*
* IRG VJ 1
* MatrixTransposeView.hpp
*
* Class MatrixTransposeView declaration, declares implementation of IMatrix interface
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#include <vector>
#include <string>
#include "MatrixSubMatrixView.hpp"

IMatrix MatrixSubMatrixView::newInstance(int const i, int const i1) const {
    throw "nema smisla";
}

std::vector<std::vector<double>> MatrixSubMatrixView::toArray() {
    //todo
    return nullptr;
}

const IMatrix& MatrixSubMatrixView::set(int const col, int const row, double const val) {
    this->original.set(this->colIndexes[col],this->rowIndexes[row],val);
    return *this;
}

MatrixSubMatrixView::MatrixSubMatrixView(const IMatrix& original, int rows, int cols) : original(original){
    this->rowIndexes = vector<int>((unsigned long) rows);
    this->colIndexes = vector<int>((unsigned long) cols);


}

double MatrixSubMatrixView::get(const int col, const int row) const {
    return this->original.get(this->colIndexes[col],this->rowIndexes[row]);
}

IMatrix MatrixSubMatrixView::subMatrix(int const i, int const i1, bool const i2) const {
    throw "nije definirano";
}
