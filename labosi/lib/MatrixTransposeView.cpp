/*
* IRG VJ 1
* MatrixTransposeView.hpp
*
* Class MatrixTransposeView definition, defines implementation of MatrixTransposeView
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/

#include <vector>
#include <string>
#include "MatrixTransposeView.hpp"

const IMatrix& MatrixTransposeView::set(int const col, int const row, double const val) {
    this->original.set(row,col,val);
    return *this;
}

IMatrix MatrixTransposeView::newInstance(int const col, int const row) const {
    throw "Ovo nema smisla";
}

std::vector<std::vector<double>> MatrixTransposeView::toArray() {
    auto v = std::vector<std::vector<double>>((unsigned int)this->original.getRowsCount());

    for (int i = this->original.getRowsCount(); i>=0;i--) {
        v[i] = std::vector<double>((unsigned int)this->original.getColsCount());
        for(int j = this->original.getColsCount();j>=0;j--)
           v[i][j] = this->original.get(j,i);
    }

    return v;
}