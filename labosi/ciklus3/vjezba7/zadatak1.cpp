//
// Created by ivan on 3/12/15.
//
#include <GL/glut.h>

#include <vector>
#include <iostream>
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>
#include <memory>
#include <sstream>

#include "Vector.hpp"
#include "IRG.hpp"

string getCommand();

void executeNormalize();

void executeVertexBodyRelation(string s);

void executeUnknownCommand(string cmdStr);

void waitForCommand();

void showUsage();

using namespace std;

double defaultAngle = 18.4349488;
double angle = defaultAngle;
double increment = 0.05;
double r = 3.16227766;

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
    enum Axis {
        X, Y, Z
    };

    static int axisId(Axis axis) {
        return (int) axis;
    }
};


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

        ptr->recalculatePlaneData();
        return ptr;
    }

    void recalculatePlaneData(){
        auto && a = vertices[0];
        auto && b = vertices[1];
        auto && c = vertices[2];

        this->normal = (b->nSub(a))->nVectorProduct(c->nSub(a));
        this->D = -(a->scalarProduct(this->normal));
    }

    double getPlaneD() const {
        return D;
    }

    const IVectorPtr getPlaneNormal() const {
        return normal;
    }

    VertexPtr vertexAt(size_t idx) {
        return vertices.at(idx);
    }

    const vector<VertexPtr> & getVertices() const{
        return vertices;
    }
};

class Object3D;

typedef shared_ptr<Object3D> Object3DPtr;

class Object3D : public enable_shared_from_this<Object3D> {
private:
    static Object3DPtr current;

    vector<TrianglePtr> faces;
    vector<VertexPtr> vertices;


#define WINDOW_X 200
#define WINDOW_Y 150
#define WINDOW_W 640
#define WINDOW_H 480
#define WINDOW_NAME "Program"

    static void glutRenderScene(){

        IMatrixPtr m;

        switch(inacica)
        {
            case 2:
            {
                auto tp =IRG::lookAtMatrix(IVectorPtr(new Vector(r*cos(angle),4,r*sin(angle))),IVectorPtr(new Vector(0,0,0)),IVectorPtr(new Vector(0,1,0)));
                auto pr = IRG::buildFrustumMatrix(-0.5f,+0.5f,-0.5f,+0.5f,1,100);
                m = tp->nMultiply(pr);
                //std::cout<<m->toString()<<std::endl;

            }
                break;
            case 1:
                m = Matrix::parseSimple("1 0 0 0 | 0 1 0 0 | 0 0 1 0 | 0 0 0 1");
                gluLookAt(3,4,1,0,0,0,0,1,0);
                break;
            default:
                throw "Unknown inacica";
        }
        //glFrontFace(GL_CCW);
        glPolygonMode(GL_FRONT,GL_LINE);
        glEnable(GL_CULL_FACE);

        glColor3f(1,0,0);
        {
            for(TrianglePtr face:Object3D::current->faces)
            {
                glBegin(GL_POLYGON);

                for (VertexPtr vertex0:face->getVertices())
                {
                    IVectorPtr vectorPtr(new Vector(vertex0->get(0),vertex0->get(1),vertex0->get(2),1));
                    IVectorPtr a4 = vectorPtr->toRowMatrix(false)->nMultiply(m)->toVector(false)->nFromHomogeneous();
                    glVertex3f((GLfloat) a4->get(0), (GLfloat) a4->get(1), (GLfloat) a4->get(2));
                }
                glEnd();
            }
        }
    }


    static void glutDisplay() {

        glClearColor(0,1,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        glutRenderScene();

        glutSwapBuffers();
    }


    static void glutKeyboard(unsigned char theKey, int, int) {
        switch (theKey) {
            case 'r':
                angle +=increment;
                glutPostRedisplay();
                break;

            case 'l':
                angle -=increment;
                glutPostRedisplay();
                break;
            case 27:
                angle = defaultAngle;
                glutPostRedisplay();
                break;
            default:
                break;
        }
    }


    static void glutReshape(int width, int height) {

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        switch(inacica)
        {
            case 1:
                glFrustum(-0.5f,+0.5f,-0.5f,+0.5f,1,100);
                break;
            case 2:
                break;
            default:
                throw "Unknown inacica";
        }
        glMatrixMode(GL_MODELVIEW);
        glViewport(0,0,width,height);

    }

protected:
    Object3D() {
    }


    size_t vertexIndex(VertexPtr vertex) {
        auto it = find(vertices.begin(), vertices.end(), vertex);
        return (size_t) distance(vertices.begin(), it);
    }

public:
    static int inacica;


    static void glutShow(const Object3DPtr &ptr){
        current = ptr;

        int myargc = 0;
        glutInit(&myargc, NULL);
        glutInitDisplayMode(GLUT_DOUBLE);
        glutInitWindowSize(WINDOW_W, WINDOW_H);
        glutInitWindowPosition(WINDOW_X, WINDOW_Y);
        glutCreateWindow(WINDOW_NAME);

        glutDisplayFunc(glutDisplay);
        glutReshapeFunc(glutReshape);
        glutKeyboardFunc(glutKeyboard);

        glutMainLoop();
    }


    static Object3DPtr create() {
        return _Create<Object3D>();
    }

    Object3DPtr copy() {
        auto obj = create();
        obj->faces = faces;
        obj->vertices = vertices;
        return obj;
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

        Object3DPtr retObj = create();

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

    string dumpOBJ() {
        ostringstream os;
        for (auto& v: vertices)
            os << "v " << v->get(0) << " " << v->get(1) << " " << v->get(2) << endl;
        for (auto& f: faces)
            os << "f " << vertexIndex(f->vertexAt(0)) + 1 << " " << vertexIndex(f->vertexAt(1)) + 1 << " " << vertexIndex(f->vertexAt(2)) + 1 << endl;
        return os.str();
    };

    double extremeVertex(Vertex::Axis axis, bool isMax) {
        if (isMax)
            return (*max_element(vertices.begin(), vertices.end(), [axis](VertexPtr a, VertexPtr b) {
                return a->get(Vertex::axisId(axis)) < b->get(Vertex::axisId(axis));
            }))->get(Vertex::axisId(axis));
        else
            return (*min_element(vertices.begin(), vertices.end(), [axis](VertexPtr a, VertexPtr b) {
                return a->get(Vertex::axisId(axis)) < b->get(Vertex::axisId(axis));
            }))->get(Vertex::axisId(axis));
    }

    Object3DPtr normalize() {
        auto maxX = extremeVertex(Vertex::Axis::X, true);
        auto maxY = extremeVertex(Vertex::Axis::Y, true);
        auto maxZ = extremeVertex(Vertex::Axis::Z, true);
        auto minX = extremeVertex(Vertex::Axis::X, false);
        auto minY = extremeVertex(Vertex::Axis::Y, false);
        auto minZ = extremeVertex(Vertex::Axis::Z, false);
        auto midX = maxX / 2 + minX / 2;
        auto midY = maxY / 2 + minY / 2;
        auto midZ = maxZ / 2 + minZ / 2;
        auto midV = Vector::Create(midX, midY, midZ);

        auto rangeX = maxX - minX;
        auto rangeY = maxY - minY;
        auto rangeZ = maxZ - minZ;

        auto scaleFactor = 2 / max({rangeX, rangeY, rangeZ});

        for (auto& vertex: vertices)
            vertex->sub(midV)->scalarMultiply(scaleFactor);
        for(auto & face:faces)
            face->recalculatePlaneData();

        return shared_from_this();
    }
};

Object3DPtr  Object3D::current = NULL;
int  Object3D::inacica = 1;

Object3DPtr model;


int main(int argc, char *argv[]) {

    if (argc != 3) {
        showUsage();
        exit(1);
    }

    Object3D::inacica = atoi(argv[2]);

    try {
        model = Object3D::loadFromOBJ(argv[1]);
    } catch (string s) {
        cout << s << endl;
        exit(1);
    }
    Object3D::glutShow(model->normalize());
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
    cout << "Command: " << cmdStr << " is invalid command" << endl;
    cout << "usage:" << endl;
    cout << "v X Y Z" << endl;
    cout << "normalize" << endl;
    cout << "quit" << endl;
}

void showUsage() {
    cout << "usage:" << endl;
    cout << "prog OBJ_FILE INACICA" << endl;
}

void executeVertexBodyRelation(string s) {
    string msg;
    switch (model->convexVertexRelation(Vertex::parseSimple(s))) {
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
    cout << msg << endl;
}

void executeNormalize() {
    auto obj = model->copy();
    obj->normalize();
    cout << obj->dumpOBJ() << endl;
}

string getCommand() {
    cout << "> ";

    string command;
    getline(cin, command);
    return command;
}
