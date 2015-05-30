//
// Created by ivan on 5/30/15.
//

#ifndef IRG_MUTUALS_H
#define IRG_MUTUALS_H

using namespace std;

template<typename T>
static shared_ptr<T> _Create() {
    struct make_shared_ret : public T {
    };
    return make_shared<make_shared_ret>();
}

class Vertex;
typedef shared_ptr<Vertex> VertexPtr;


class Vertex : public Vector {
private:
public:
    const IVectorPtr &getNormal() const {
        return normal;
    }

    void setNormal(IVectorPtr &normal) {
        Vertex::normal = normal;
    }

private:
    IVectorPtr normal;
public:
    static VertexPtr Create(double x, double y, double z){
        VertexPtr v(new Vertex(x,y,z));
        return v;
    }

    Vertex(double e1, double e2, double e3) : Vector(e1, e2, e3) { }

    enum Relation {
        In, Out, Edge
    };
    enum Axis {
        X, Y, Z
    };

    static int axisId(Axis axis) {
        return (int) axis;
    }
};



#endif //IRG_MUTUALS_H
