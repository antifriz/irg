/*
* IRG VJ 1
* Vector.hpp
*
* Class Vector implementation, inherits AbstractVector
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#include <string>
#include <sstream>
#include "Vector.hpp"

const IVector& Vector::set(const int idx, const double value) {
    if (this->readOnly)
        throw "calling Vector::set() on readOnly vector is forbidden";
    elements[idx] = value;
    return *this;
};

#define VECTOR_H_STRING_DELIMITER (' ')

Vector Vector::parseSimple(const std::string str) {
    using namespace std;


    stringstream ss(str);
    string item;
    vector<double> values;
    while (getline(ss, item, VECTOR_H_STRING_DELIMITER)) {
        char *endptr;
        double d = strtod(item.c_str(), &endptr);
        if (*endptr)
            throw "bad Vector::parseSimple call; input string not valid";
        values.push_back(d);
    }

    return Vector(values);
}
