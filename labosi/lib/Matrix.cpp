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
#include "Matrix.hpp"

Matrix::Matrix(const int cols, const int rows) : cols(cols), rows(rows) {
    this->elements = vector<vector<double>>((unsigned int) cols);
    for (int j = cols - 1; j >= 0; --j) {
        this->elements[j] = vector<double>((unsigned int) rows);
        for (int i = rows - 1; i >= 0; --i)
            this->elements[j][i] = 0;
    }
}



IMatrix Matrix::copy() const {
    return Matrix(this->cols, this->rows, this->elements, true);
}

IMatrix Matrix::newInstance(int const cols, int const rows) const {
    return Matrix(cols, rows);
}

#define MATRIX_H_STRING_DELIMITER_CELL (' ')
#define MATRIX_H_STRING_DELIMITER_ROW ('|')

Matrix Matrix::parseSimple(const std::string str) {
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
            else if (rowCount != values[row].size())
                throw "bad Matrix::parseSimple call, string not formatted well";
            row++;
            values.push_back(vector<double>());
            continue;
        }

        char *endptr;
        double d = strtod(item.c_str(), &endptr);
        if (*endptr)
            throw "bad Vector::parseSimple call; input string not valid";
        values[0].push_back(d);
    }

    auto v = values;

    for (int i = rowCount; i >= 0; i--) {
        v[i] = std::vector<double>(values.size());
        for (int j = values.size(); j >= 0; j--)
            v[i][j] = values[j][i];
    }

    return Matrix(rowCount, v.size(), v, true);
}

