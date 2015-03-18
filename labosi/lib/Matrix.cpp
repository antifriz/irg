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
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include "Matrix.hpp"

Matrix::Matrix(const int rows, const int cols) : cols(cols), rows(rows) {
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
                rowCount = values[0].size();
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

    return MatrixPtr(new Matrix(values.size(), rowCount, v, true));
}
