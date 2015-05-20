//
// Created by ivan on 5/18/15.
//

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
    m->set(2,2,-(f+n)/(f-n));
    m->set(2,0,(r+l)/(r-l));
    m->set(3,0,(t+b)/(t-b));
    m->set(2,3,-1);
    m->set(3,2,-2*f*n/(f-n));
    return m;
}