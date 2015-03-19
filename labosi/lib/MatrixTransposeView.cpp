/*
* IRG VJ 1
* MatrixTransposeView.hpp
*
* Class MatrixTransposeView definition, defines implementation of MatrixTransposeView
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/

#include "MatrixTransposeView.hpp"


std::vector<std::vector<double>> MatrixTransposeView::toArray() {
    using std::vector;
    auto v = vector<vector<double>>((unsigned int) this->original->getRowsCount());

    for (int i = 0; i < this->original->getRowsCount(); ++i) {
        v[i] = vector<double>();
        for (int j = 0; j < this->original->getColsCount(); ++j) {
            v[i].push_back(this->original->get(j, i));
        }
    }

    return v;
}

const IMatrixPtr MatrixTransposeView::copy() const {
    IMatrixPtr retMatrix = this->original->newInstance(this->original->getColsCount(), this->original->getRowsCount());

    for (int j = this->getColsCount() - 1; j >= 0; --j)
        for (int i = this->getRowsCount() - 1; i >= 0; --i)
            retMatrix->set(i, j, this->get(i, j));

    return retMatrix;
}
