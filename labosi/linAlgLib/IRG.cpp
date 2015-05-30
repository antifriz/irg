//
// Created by ivan on 5/18/15.
//

#include <assert.h>
#include <math.h>
#include <iostream>
#include "IRG.hpp"

IMatrixPtr IRG::scale3D(float sx,float sy, float sz) {
    MatrixPtr m = MatrixPtr(new Matrix(4, 4));
    m->set(0,0,sx);
    m->set(1,1,sy);
    m->set(2,2,sz);
    m->set(3,3,1);
    return m;
}

IMatrixPtr IRG::translate3D(float dx,float dy, float dz) {
    MatrixPtr m = MatrixPtr(new Matrix(4, 4));
    m->set(0,0,1);
    m->set(1,1,1);
    m->set(2,2,1);
    m->set(3,3,1);
    m->set(3,0,dx);
    m->set(3,1,dy);
    m->set(3,2,dz);
    return m;
}

IMatrixPtr IRG::lookAtMatrix(IVectorPtr eye,IVectorPtr center,IVectorPtr viewUp) {
    IVectorPtr forward = center->nSub(eye)->normalize();
    IVectorPtr side = forward->nVectorProduct(viewUp)->normalize();
    IVectorPtr up = side->nVectorProduct(forward)->normalize();

    IMatrixPtr m2(new Matrix(4,4));

    for (int i = 0; i < 3; ++i)
        m2->set(i,0,side->get(i));
    for (int i = 0; i < 3; ++i)
        m2->set(i,1,up->get(i));
    for (int i = 0; i < 3; ++i)
        m2->set(i,2,-forward->get(i));
    m2->set(3,3,1);


    return translate3D((float) -eye->get(0), (float) -eye->get(1), (float) -eye->get(2))->nMultiply(m2);
}

IMatrixPtr IRG::buildFrustumMatrix(double l, double r,double b, double t,int n, int f) {
    MatrixPtr m = MatrixPtr(new Matrix(4, 4));
    m->set(0,0,2*n/(r-l));

    m->set(1,1,2*n/(t-b));

    m->set(2,0,(r+l)/(r-l));
    m->set(2,1,(t+b)/(t-b));
    m->set(2,2,-(f+n)/(f-n));
    m->set(2,3,-1);

    m->set(3,2,-2*f*n/(f-n));

    return m;
}

bool IRG::isAntiClockwise(const std::vector<IVectorPtr> vertices) {
    assert(vertices.size()==3);
    IVectorPtr a = vertices[0];
    IVectorPtr b = vertices[1];
    IVectorPtr c = vertices[2];
    a->set(2,1);
    b->set(2,1);
    c->set(2,1);

    return b->nVectorProduct(a)->scalarProduct(c)<0;
}

IMatrixPtr  Bezier::generatePolyCoeffMatrix(int n) {
    IMatrixPtr m(new Matrix(n+1,n+1));
    std::vector<unsigned long> masterBinomials = getBinomials(n);
    int prefix;
    for (int i = n; i >=0 ; --i) {
        std::vector<unsigned long> binomials = getBinomials(n-i);
        prefix = (n-i) %2 ? -1 : 1;
        for (int j = 0; j <=n-i; ++j) {
            m->set(j,i,((double)binomials[j]*masterBinomials[i])*prefix);
            prefix=-prefix;
        }
    }
    return m;
}

std::vector<unsigned long>  Bezier::getBinomials(int n) {
    std::vector<unsigned long> binomial_coeff;
    unsigned long a = 1;
    for (int i = 1;i<=n+1;i++) {
        binomial_coeff.push_back(a);
        a=(a*(n-i+1))/i;
    }
    return binomial_coeff;
}

IVectorPtr  Bezier::generatePolyVector(double t, int n) {
    IVectorPtr vector(new Vector(n+1));
    vector->set(n,1);
    for (int i = n; i>=1 ; --i)
        vector->set(n-i,pow(t,i));
    return vector;
}

IMatrixPtr Bezier::generateHomogeneousPolyVectorsMatrix(int n) {
    std::vector<IVectorPtr> container;
    double step = 1.0/n;

    for (int i = 0; i <= n; ++i) {
        container.push_back(generatePolyVector(step*i,n));
    }

    return Matrix::fromContainerOfVectors(container,true);
}

std::vector<IVectorPtr>  Bezier::getHomogeneousControlPoints(std::vector<IVectorPtr> pointsOnCurve) {
    int n = (int) (pointsOnCurve.size()-1);
    IMatrixPtr W = generateWeights(n);
/*    std::cout<<"weights"<<std::endl;
    std::cout<<W->toString()<<std::endl;
    std::cout<<"end_weights"<<std::endl;*/

    IMatrixPtr invWeights = W->nInvert();

/*    std::cout<<"inW"<<std::endl;
    std::cout<<invWeights->toString()<<std::endl;
    std::cout<<"end_inW"<<std::endl;*/

    IMatrixPtr pointsOnCurveMatrix(Matrix::fromContainerOfVectors(pointsOnCurve,true));

    IMatrixPtr controlPointsMatrix =  invWeights->nMultiply(pointsOnCurveMatrix);

/*    std::cout<<"cpmat"<<std::endl;
    std::cout<<controlPointsMatrix->toString()<<std::endl;
    std::cout<<"end_cpmat"<<std::endl;*/

    return Matrix::toContainerOfVectors(controlPointsMatrix,true);
}

IMatrixPtr  Bezier::generateWeights(int n) {
    IMatrixPtr P = generateHomogeneousPolyVectorsMatrix(n);
    IMatrixPtr B = generatePolyCoeffMatrix(n);
    return P->nMultiply(B);
}