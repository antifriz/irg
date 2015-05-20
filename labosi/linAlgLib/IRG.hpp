//
// Created by ivan on 5/18/15.
//

#ifndef IRG_IRG_H
#define IRG_IRG_H

#include "Matrix.hpp"
#include "Vector.hpp"

class IRG{
public:
    static IMatrixPtr translate3D(float dx,float dy, float dz);

    static IMatrixPtr scale3D(float sx,float sy, float sz);

    static IMatrixPtr lookAtMatrix(IVectorPtr eye,IVectorPtr center,IVectorPtr viewUp);;

    static IMatrixPtr buildFrustumMatrix(double l, double r,double b, double t,int n, int f);
};

#endif //IRG_IRG_H
