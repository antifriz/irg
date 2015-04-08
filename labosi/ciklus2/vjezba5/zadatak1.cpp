//
// Created by ivan on 3/12/15.
//
#include <vector>
#include <iostream>
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>
#include <memory>

#include "Vector.hpp"

string getCommand();

void executeNormalize();

void executeVertexBodyRelation(string s);

void executeUnknownCommand(string cmdStr);

void waitForCommand();

void showUsage();

using namespace std;


template<typename T>
static shared_ptr<T> _Create() {
    struct make_shared_ret : public T {
    };
    return make_shared<make_shared_ret>();
}

typedef IVectorPtr VertexPtr;

class Vertex : public Vector {
public:
    enum Relation {
        In, Out, Edge
    };
};


class Triangle;

typedef shared_ptr<Triangle> TrianglePtr;

class Triangle {
private:
    vector<VertexPtr> vertices;
    IVectorPtr normal;
    double D;
protected:
    Triangle(){}
public:
    virtual Vertex::Relation vertexRelation(VertexPtr vertex) const {
        auto relation = normal->scalarProduct(vertex) + D;
        return relation > 0 ? Vertex::Relation::Out : (relation < 0) ? Vertex::Relation::In : Vertex::Relation::Edge;
    };




    static TrianglePtr Create(const VertexPtr& a, const VertexPtr& b, const VertexPtr& c) {
        TrianglePtr ptr = _Create<Triangle>();

        ptr->vertices.reserve(3);
        ptr->vertices.push_back(a);
        ptr->vertices.push_back(b);
        ptr->vertices.push_back(c);

        ptr->normal = (b->nSub(a))->nVectorProduct(c->nSub(a));

        ptr->D = -(a->scalarProduct(ptr->normal));
        return ptr;
    }

    double getPlaneD() const {
        return D;
    }

    const IVectorPtr getPlaneNormal() const {
        return normal;
    }


};

class Object3D;

typedef shared_ptr<Object3D> Object3DPtr;

class Object3D {
private:
    vector<TrianglePtr> faces;
    vector<VertexPtr> vertices;

protected:
   Object3D(){}

public:

    static Object3DPtr Create() {
        return _Create<Object3D>();
    }

    void addVertex(VertexPtr vertex) {
        vertices.push_back(vertex);
    }

    void addFaceFromVertexIDs(size_t idx1, size_t idx2, size_t idx3) {
        try {
            faces.push_back(Triangle::Create(vertices.at(idx1), vertices.at(idx2), vertices.at(idx3)));
        } catch (out_of_range o) {
            throw "Unsupported file format";
        }
    }

    static Object3DPtr loadFromOBJ(char *fname) {
        if (!boost::algorithm::ends_with(fname, ".obj"))
            throw "Unsupported file extension";

        ifstream objFile(fname);
        if (!objFile.is_open())
            throw "Unable to open file";

        Object3DPtr retObj = Create();

        char type;
        double x, y, z;
        while (objFile >> type >> x >> y >> z) {
            switch (type) {
                case 'v':
                    retObj->addVertex(Vertex::Create(x, y, z));
                    break;
                case 'f':
                    retObj->addFaceFromVertexIDs((size_t) (x - 1), (size_t) (y - 1), (size_t) (z - 1));
                    break;
                case '#':
                    break;
                default:
                    throw "Unsupported file format";
            }
        }
        return retObj;
    }

    Vertex::Relation convexVertexRelation(VertexPtr vertex) {
        bool isEdge = false;
        for (auto& face: faces) {
            auto relation = face->vertexRelation(vertex);
            if (relation == Vertex::Relation::Out)
                return Vertex::Relation::Out;
            isEdge |= (relation == Vertex::Relation::Edge);
        }
        return isEdge ? Vertex::Relation::Edge : Vertex::Relation::In;
    }
};

Object3DPtr model;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        showUsage();
        exit(1);
    }

    try {
        model = Object3D::loadFromOBJ(argv[1]);
    } catch (string s) {
        cout << s << endl;
        exit(1);
    }

    waitForCommand();
    return 0;
}

void waitForCommand() {
    while (true) {
        auto cmdStr = getCommand();

        if (cmdStr.find("normalize") == 0)
            executeNormalize();
        else if (cmdStr.find("v ") == 0)
            executeVertexBodyRelation(cmdStr.substr(2));
        else if (cmdStr.find("quit") == 0)
            break;
        else
            executeUnknownCommand(cmdStr);
    }
}

void executeUnknownCommand(string cmdStr) {
    cout << "Command: "<<cmdStr<<" is invalid command"<<endl;
    cout << "usage:" << endl;
    cout << "v X Y Z" << endl;
    cout << "normalize" << endl;
    cout << "quit" << endl;
}

void showUsage() {
    cout << "usage:" << endl;
    cout << "prog OBJ_FILE" << endl;
}

void executeVertexBodyRelation(string s) {
    string msg;
    switch(model->convexVertexRelation(Vertex::parseSimple(s)))
    {
        case Vertex::Relation::Out:
            msg = "Tocka je izvan tijela";
            break;
        case Vertex::Relation::In:
            msg = "Tocka je unutar tijela";
            break;
        case Vertex::Relation::Edge:
        default:
            msg = "Tocka je na rubu tijela";
            break;
    }
    cout<<msg<<endl;
}

void executeNormalize() {

}

string getCommand() {
    cout << "> ";

    string command;
    getline(cin,command);
    return command;
}