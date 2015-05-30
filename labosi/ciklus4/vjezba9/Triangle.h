//
// Created by ivan on 5/30/15.
//

#ifndef IRG_TRIANGLE_H
#define IRG_TRIANGLE_H

#include <GL/glut.h>
#include <vector>
#include <memory>
#include "Vector.hpp"
#include "mutuals.h"

class Triangle;
typedef shared_ptr<Triangle> TrianglePtr;

class Triangle {
private:
    vector<VertexPtr> vertices;
    IVectorPtr normal;
    double D;
protected:
    Triangle() {
    }

public:
    bool visible;


    virtual Vertex::Relation vertexRelation(IVectorPtr vertex) const;


    static shared_ptr<Triangle> Create(const VertexPtr & a, const VertexPtr & b, const VertexPtr & c);

    void recalculatePlaneData();

    double getPlaneD() const;

    const IVectorPtr getPolyCenter() const;

    const IVectorPtr getPlaneNormal() const;

    const IVectorPtr vertexAt(std::size_t idx) const;

    const vector<VertexPtr> & getVertices() const;
};



#endif //IRG_TRIANGLE_H
