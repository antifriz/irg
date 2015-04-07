/*
* IRG VJ 1
* Vector.hpp
*
* Class Vector declaration, inherits AbstractVector
*
* @author Ivan Jurin
* @version 1.0 12/03/15
*/
#ifndef VECTOR_H_
#define VECTOR_H_

#include "AbstractVector.hpp"

#define VECTOR_H_READONLY_DEFAULT false
#define VECTOR_H_IMMUTABLE_DEFAULT true


class Vector : public AbstractVector {
private:
    std::vector<double> elements;
    int dimension;
    bool readOnly;

    Vector(): dimension(0),readOnly(VECTOR_H_READONLY_DEFAULT){

    }


public:
    Vector(double e1):Vector()
    {
        elements.push_back(e1);
        dimension = (int) elements.size();
    }
    Vector(double e1,double e2):Vector(e1)
    {
        elements.push_back(e2);
        dimension = (int) elements.size();
    }
    Vector(double e1,double e2,double e3):Vector(e1,e2)
    {
        elements.push_back(e3);
        dimension = (int) elements.size();
    }

    typedef shared_ptr<Vector> VectorPtr;

    static VectorPtr Create(double e1){
        return std::make_shared<Vector>(e1);
    }

    static VectorPtr Create(double e1,double e2){
        return std::make_shared<Vector>(e1,e2);
    }

    static VectorPtr Create(double e1,double e2,double e3){
        return std::make_shared<Vector>(e1,e2,e3);
    }



    /*
    * constructor which takes three values:
    *   - is vector readonly
    *   - can array be passed by reference // it is ignored so vector always copies input
    *   - array to be initialized with
    */
    Vector(bool readOnly, bool inputImmutable, const std::vector<double> &inputArray)
            : elements(inputArray),
              dimension((int) inputArray.size()),
              readOnly(readOnly) {
    }

    /*
    * constructor which takes one value:
    *   - array to be initialized with
    * other options default to defined values
    */
    Vector(const std::vector<double> &initializerVector)
            : Vector(VECTOR_H_READONLY_DEFAULT, VECTOR_H_IMMUTABLE_DEFAULT, initializerVector) {
    }




    /*
    * gets vector element at given index
    */
    double get(int idx) const {
        return elements[idx];
    }

    /*
    * if vector is not readonly sets value at given index, else throws exception
    */
    const IVectorPtr set(int, double);


    /*
    * gets vector dimension
    */
    int getDimension() const {
        return dimension;
    }


    /*
    * creates copy of this vector
    */
    const IVectorPtr copy() const {
        return IVectorPtr(new Vector(readOnly, true, this->elements));
    }

    /*
    * creates new instance of Vector with given dimension
    */
    const IVectorPtr newInstance(int dimension) const {
        return IVectorPtr(new Vector(vector<double>((unsigned int) dimension)));
    }


    /*
    * creates new instance of Vector with given string
    */
    static const VectorPtr parseSimple(const std::string);

};

typedef shared_ptr<Vector> VectorPtr;

#endif

