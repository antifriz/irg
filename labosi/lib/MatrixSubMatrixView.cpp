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

const IMatrix &MatrixSubMatrixView::set(int const col, int const row, double const val) {
    int realCol = col < this->excludedCol ? col : col + 1;
    int realRow = row < this->excludedRow ? row : row + 1;
    this->original.set(realCol, realRow, val);
    return *this;
}


double MatrixSubMatrixView::get(const int col, const int row) const {
    int realCol = col < this->excludedCol ? col : col + 1;
    int realRow = row < this->excludedRow ? row : row + 1;
    return this->original.get(realCol, realRow);
}

IMatrix MatrixSubMatrixView::copy() const {
    IMatrix retMatrix = this->original.newInstance(this->original.getColsCount() - 1, this->original.getRowsCount() - 1);
    for (int j = this->original.getColsCount() - 1; j >= 0; --j)
        if (this->excludedCol != j)
            for (int i = this->original.getRowsCount() - 1; i >= 0; ++i)
                if (this->excludedRow != i)
                    retMatrix.set(j, i, this->get(j, i));
    return retMatrix;
}
