/*
* IRG VJ 1
* MatrixTransposeView.hpp
*
* Class MatrixTransposeView declaration, declares implementation of IMatrix interface
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#include "MatrixSubMatrixView.hpp"

const IMatrixPtr MatrixSubMatrixView::set(int row, int col, double val) {
    int realCol = col < this->excludedCol ? col : col + 1;
    int realRow = row < this->excludedRow ? row : row + 1;
    this->original->set(realRow, realCol, val);
    return this->shared_from_this();
}


double MatrixSubMatrixView::get(int row, int col) const {
    int realCol = col < this->excludedCol ? col : col + 1;
    int realRow = row < this->excludedRow ? row : row + 1;
    return this->original->get(realRow, realCol);
}

const IMatrixPtr MatrixSubMatrixView::copy() const {
    IMatrixPtr retMatrix = this->original->newInstance(this->original->getRowsCount() - 1, this->original->getColsCount() - 1);
    for (int j = this->original->getColsCount() - 1; j >= 0; --j)
        if (this->excludedCol != j)
            for (int i = this->original->getRowsCount() - 1; i >= 0; ++i)
                if (this->excludedRow != i)
                    retMatrix->set(j, i, this->get(j, i));
    return retMatrix;
}
