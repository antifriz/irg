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


std::vector<std::vector<double>> MatrixTransposeView::toArray() {
    auto v = std::vector<std::vector<double>>((unsigned int) this->original.getRowsCount());

    for (int i = this->original.getRowsCount(); i >= 0; i--) {
        v[i] = std::vector<double>((unsigned int) this->original.getColsCount());
        for (int j = this->original.getColsCount(); j >= 0; j--)
            v[i][j] = this->original.get(j, i);
    }

    return v;
}

IMatrix MatrixTransposeView::copy() const {
    IMatrix retMatrix = this->original.newInstance(this->original.getRowsCount(), this->original.getColsCount());
    for (int j = this->getColsCount() - 1; j >= 0; --j)
        for (int i = this->getRowsCount() - 1; i >= 0; ++i)
            retMatrix.set(j, i, this->get(i, j));
    return retMatrix;
}
