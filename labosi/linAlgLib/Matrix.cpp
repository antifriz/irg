/*
* IRG VJ 1
* Matrix.hpp
*
* Class Matrix definition
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include "Matrix.hpp"
#include "Vector.hpp"

Matrix::Matrix(int rows, int cols) : cols(cols), rows(rows) {
    using std::vector;
    this->elements = vector<vector<double>>((unsigned int) cols);
    for (int j = cols - 1; j >= 0; --j) {
        this->elements[j] = vector<double>((unsigned int) rows);
        for (int i = rows - 1; i >= 0; --i)
            this->elements[j][i] = 0;
    }
}


const IMatrixPtr Matrix::copy() const {
    return IMatrixPtr(new Matrix(this->rows, this->cols, this->elements, true));
}

const IMatrixPtr Matrix::newInstance(int const rows, int const cols) const {
    return IMatrixPtr(new Matrix(rows, cols));
}

#define MATRIX_H_STRING_DELIMITER_CELL (' ')
#define MATRIX_H_STRING_DELIMITER_ROW ('|')

const MatrixPtr Matrix::parseSimple(const std::string str) {
    using namespace std;

    stringstream ss(str);
    string item;
    vector<vector<double>> values(1);
    int row = 0;
    values[0] = vector<double>();


    int rowCount = -1;

    while (getline(ss, item, MATRIX_H_STRING_DELIMITER_CELL)) {
        if (item[0] == MATRIX_H_STRING_DELIMITER_ROW) {
            if (rowCount == -1)
                rowCount = (int) values[0].size();
            else if (rowCount != (int) values[row].size())
                throw "bad Matrix::parseSimple call, string not formatted well";
            row++;
            values.push_back(vector<double>());

            continue;
        }

        char *endptr;
        double d = strtod(item.c_str(), &endptr);
        if (*endptr)
            throw "bad Vector::parseSimple call; input string not valid";
        values[row].push_back(d);
    }

    vector<vector<double>> v((unsigned int) rowCount);

    for (int i = 0; i < rowCount; ++i) {
        v.push_back(vector<double>());
        for (int j = 0; j < (int) values.size(); ++j) {
            v[i].push_back(values[j][i]);
        }
    }

    return MatrixPtr(new Matrix((int) values.size(), rowCount, v, true));
}

MatrixPtr Matrix::fromContainerOfVectors(const std::vector<IVectorPtr> container, bool rowVectors) {
    assert(rowVectors);
    assert(container.size()>0);
    MatrixPtr m(new Matrix((int) container.size(),container.at(0)->getDimension()));
    for (size_t i = 0; i < container.size(); ++i) {
        auto &v = container.at((unsigned long) i);
        for (int j = 0; j < v->getDimension(); ++j) {
            m->set((int) i,j,v->get(j));
        }
    }
    return m;
}

std::vector<IVectorPtr> Matrix::toContainerOfVectors(const IMatrixPtr & matrix, bool rowVectors){
    assert(rowVectors);
    std::vector<IVectorPtr> container;

    for (int i = 0; i < matrix->getRowsCount(); ++i) {
        IVectorPtr v(new Vector(matrix->getColsCount()));
        for (int j = 0; j < matrix->getColsCount(); ++j) {
            v->set(j,matrix->get(i,j));
        }
        container.push_back(v);
    }
    return container;
}
