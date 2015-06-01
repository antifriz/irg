//
// Created by ivan on 5/30/15.
//

#include "Triangle.h"

shared_ptr<Triangle>  Triangle::Create(const VertexPtr & a, const VertexPtr & b, const VertexPtr & c) {
    shared_ptr<Triangle> ptr = _Create<Triangle>();

    ptr->vertices.reserve(3);
    ptr->vertices.push_back(a);
    ptr->vertices.push_back(b);
    ptr->vertices.push_back(c);

    ptr->recalculatePlaneData();
    return ptr;
}

void Triangle::recalculatePlaneData() {
    auto && a = vertices[0];
    auto && b = vertices[1];
    auto && c = vertices[2];

    this->normal = (b->nSub(a))->nVectorProduct(c->nSub(a))->normalize();
    this->D = -(a->scalarProduct(this->normal));
}

const IVectorPtr Triangle::getPolyCenter() const {
    return vertexAt(0)->nAdd(vertexAt(1))->nAdd(vertexAt(2))->scalarMultiply(1/3.0f);
}

Vertex::Relation  Triangle::vertexRelation(IVectorPtr vertex) const {
    auto relation = normal->scalarProduct(vertex) + D;
    return relation > 0 ? Vertex::Relation::Out : (relation < 0) ? Vertex::Relation::In : Vertex::Relation::Edge;
}

const IVectorPtr Triangle::vertexAt(std::size_t idx) const {
    return vertices.at(idx);
}

const vector<VertexPtr> &Triangle::getVertices() const {
    return vertices;
}

const IVectorPtr Triangle::getPlaneNormal() const {
    return normal;
}

double Triangle::getPlaneD() const {
    return D;
}