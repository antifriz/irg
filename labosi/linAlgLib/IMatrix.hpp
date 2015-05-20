/*
* IRG VJ 1
* IVector.hpp
*
* Interface IMatrix declaration, contains declarations of all methods that matrix implementation must contain
*
* @author Ivan Jurin
* @version 1.0 15/03/15
*/
#ifndef I_MATRIX_H_
#define I_MATRIX_H_

#include "ForwardDeclarations.h"
#include "IVector.hpp"

class IMatrix : public std::enable_shared_from_this<IMatrix> {
public:

    virtual int getRowsCount() const = 0;

    virtual int getColsCount() const = 0;

    virtual double get(int, int) const = 0;

    virtual const IMatrixPtr set(int, int, double) = 0;

    virtual const IMatrixPtr copy() const = 0;

    virtual const IMatrixPtr newInstance(int, int) const = 0;

    virtual const IMatrixPtr nTranspose(bool) = 0;

    virtual const IMatrixPtr add(const IMatrixPtr) = 0;

    virtual const IMatrixPtr nAdd(const IMatrixPtr) const = 0;

    virtual const IMatrixPtr sub(const IMatrixPtr) = 0;

    virtual const IMatrixPtr nSub(const IMatrixPtr) const = 0;

    virtual const IMatrixPtr nMultiply(const IMatrixPtr) const = 0;

    virtual double determinant() const = 0;

    virtual const IMatrixPtr subMatrix(int, int, bool) = 0;

    virtual const IMatrixPtr nInvert() const = 0;

    virtual std::vector<std::vector<double>> toArray() const = 0;

    virtual const IVectorPtr toVector(bool) = 0;


    virtual const std::string toString() const = 0;

    virtual const std::string toString(int) const = 0;

    virtual IMatrixPtr const multiplyByConstant(double constant) = 0;

    virtual const std::string whoAmI() const = 0;



};


#endif