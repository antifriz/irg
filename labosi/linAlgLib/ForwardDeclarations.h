//
// Created by Ivan on 18-Mar-15.
//

#ifndef _LINALGLIBTEST_FORWARDDECLARATIONS_H_
#define _LINALGLIBTEST_FORWARDDECLARATIONS_H_

#include <vector>
#include <string>
#include <memory>

class IMatrix;

class IVector;

typedef std::shared_ptr<IMatrix> IMatrixPtr;
typedef std::shared_ptr<IVector> IVectorPtr;

#endif //_LINALGLIBTEST_FORWARDDECLARATIONS_H_
