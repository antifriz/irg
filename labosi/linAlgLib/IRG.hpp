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

    static bool isAntiClockwise(const std::vector<IVectorPtr> vertices);
};

class Bezier{
public:
    static std::vector<unsigned long> getBinomials(int n);


    static IMatrixPtr generatePolyCoeffMatrix(int n);

    static IVectorPtr generatePolyVector(double t, int n);

    static IMatrixPtr generateHomogeneousPolyVectorsMatrix(int n);

    static IMatrixPtr generateWeights(int n);

    static std::vector<IVectorPtr> getHomogeneousControlPoints(std::vector<IVectorPtr> pointsOnCurve);
};

#endif //IRG_IRG_H
