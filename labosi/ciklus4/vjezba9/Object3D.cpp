//
// Created by ivan on 5/30/15.
//

#include <iostream>
#include "Object3D.h"


enum { KonstantnoSjencanje, GouraudovoSjencanje } sjencanje = KonstantnoSjencanje;
bool z_spremnik = true;
double defaultAngle = 18.4349488 / 180.0 * M_PI;
double angle = defaultAngle;
double increment = 0.01;
double r = 3.16227766;

double scale = 0.5f;


void Object3D::calculateVertexNormals() {
    for (VertexPtr vertex: this->vertices) {
        IVectorPtr normal(new Vector(0.f, 0.f, 0.f));
        for (TrianglePtr &face:this->faces) {
            for (VertexPtr n:face->getVertices()) {
                if (n->get(0) == vertex->get(0) && n->get(1) == vertex->get(1) && n->get(2) == vertex->get(2)) {
                    normal->add(face->getPlaneNormal()->normalize());
                    break;
                }
            }
        }
        normal = normal->normalize();
        vertex->setNormal(normal);
    }
}

string Object3D::dumpOBJ() {
    std::ostringstream os;
    for (auto &v: vertices)
        os << "v " << v->get(0) << " " << v->get(1) << " " << v->get(2) << std::endl;
    for (auto &f: faces)
        os << "f " << vertexIndex(f->vertexAt(0)) + 1 << " " << vertexIndex(f->vertexAt(1)) + 1 << " " <<
        vertexIndex(f->vertexAt(2)) + 1 << std::endl;
    return os.str();
}

double Object3D::extremeVertex(Vertex::Axis axis, bool isMax) {
    if (isMax)
        return (*max_element(vertices.begin(), vertices.end(), [axis](VertexPtr a, VertexPtr b) {
            return a->get(Vertex::axisId(axis)) < b->get(Vertex::axisId(axis));
        }))->get(Vertex::axisId(axis));
    else
        return (*min_element(vertices.begin(), vertices.end(), [axis](VertexPtr a, VertexPtr b) {
            return a->get(Vertex::axisId(axis)) < b->get(Vertex::axisId(axis));
        }))->get(Vertex::axisId(axis));
}

Object3DPtr Object3D::normalize() {
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

    for (auto &vertex: vertices)
        vertex->sub(midV)->scalarMultiply(scaleFactor);
    for (auto &face:faces)
        face->recalculatePlaneData();

    return shared_from_this();
}

Object3DPtr  Object3D::loadFromOBJ(char *fname) {
    if (!boost::algorithm::ends_with(fname, ".obj"))
        throw "Unsupported file extension";

    std::ifstream objFile(fname);
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
                retObj->addFaceFromVertexIDs((std::size_t) (x - 1), (std::size_t) (y - 1), (std::size_t) (z - 1));
                break;
            case '#':
                break;
            default:
                throw "Unsupported file format";
        }
    }
    return retObj;
}

void Object3D::addFaceFromVertexIDs(std::size_t idx1, std::size_t idx2, std::size_t idx3) {
    try {
        faces.push_back(Triangle::Create(vertices.at(idx1), vertices.at(idx2), vertices.at(idx3)));
    } catch (std::out_of_range o) {
        throw "Unsupported file format";
    }
}

void Object3D::addVertex(VertexPtr vertex) {
    vertices.push_back(vertex);
}

Object3DPtr Object3D::copy() {
    auto obj = create();
    obj->faces = faces;
    obj->vertices = vertices;
    return obj;
}

Object3DPtr  Object3D::create() {
    return _Create<Object3D>();
}

void  Object3D::glutShow(const Object3DPtr &ptr) {
    current = ptr;

    int myargc = 0;
    glutInit(&myargc, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    glutCreateWindow(WINDOW_NAME);

    glutDisplayFunc(glutDisplay);
    glutReshapeFunc(glutReshape);
    glutKeyboardFunc(glutKeyboard);
    //glutTimerFunc(30,timer,0);


    glutMainLoop();
}

void  Object3D::timer(int value) {
    angle += 0.01;
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void Object3D::determineFaceVisibilities2(IVectorPtr eye) {
    for (shared_ptr<Triangle> &face:faces)
        face->visible = eye->nSub(face->getPolyCenter())->scalarProduct(face->getPlaneNormal()) > 0;
}

void Object3D::determineFaceVisibilities1(IVectorPtr eye) {
    for (shared_ptr<Triangle> &face:faces)
        face->visible = face->getPlaneNormal()->scalarProduct(eye) + face->getPlaneD() > 0;
}

std::size_t Object3D::vertexIndex(IVectorPtr vertex) {
    auto it = find(vertices.begin(), vertices.end(), vertex);
    return (std::size_t) distance(vertices.begin(), it);
}

void  Object3D::glutReshape(int width, int height) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch (inacica) {
        case 1:
            glFrustum(-scale, +scale, -scale, +scale, 1, 100);

            break;
        case 2:
            break;
        default:
            throw "Unknown inacica";
    }
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);

}

void  Object3D::glutKeyboard(unsigned char theKey, int, int) {
    switch (theKey) {
        case 'r':
            angle += increment;
            glutPostRedisplay();
            break;

        case 'l':
            angle -= increment;
            glutPostRedisplay();
            break;
        case 'k':
            sjencanje = KonstantnoSjencanje;
            glutPostRedisplay();
            break;

        case 'g':
            sjencanje = GouraudovoSjencanje;
            glutPostRedisplay();
            break;
        case 'z':
            z_spremnik ^= true;
            glutPostRedisplay();
            break;
        case 'i':
            Object3D::inacica = 1;
            glutPostRedisplay();
            break;
        case 'j':
            Object3D::inacica = 2;
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

void  Object3D::glutDisplay() {

    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glutRenderScene();

    glutSwapBuffers();
}

int Object3D::odbacivanje = 2;


Object3DPtr  Object3D::current = NULL;
int  Object3D::inacica = 1;

void  Object3D::glutRenderScene() {
    std::cout<<"Inacica: "<<inacica<<endl;
    std::cout<<"Sjencanje: "<< sjencanje <<endl;
    IMatrixPtr m;

    switch (inacica) {
        case 2: {
            shared_ptr<IVector> eye = IVectorPtr(new Vector(r * cos(angle), 4, r * sin(angle)));
            auto tp = IRG::lookAtMatrix(eye, IVectorPtr(new Vector(0, 0, 0)), IVectorPtr(new Vector(0, 1, 0)));
            auto pr = IRG::buildFrustumMatrix(-scale, +scale, -scale, +scale, 1, 100);
            m = tp->nMultiply(pr);

            if (Object3D::odbacivanje == 2)
                current->determineFaceVisibilities1(eye);
            else if (Object3D::odbacivanje == 3)
                current->determineFaceVisibilities2(eye);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
        }
            break;
        case 1:
            m = Matrix::parseSimple("1 0 0 0 | 0 1 0 0 | 0 0 1 0 | 0 0 0 1");
            gluLookAt(r * cos(angle), 4, r * sin(angle), 0, 0, 0, 0, 1, 0);

            glFrontFace(GL_CCW);
            glPolygonMode(GL_FRONT, GL_FILL);
            glEnable(GL_CULL_FACE);

            glEnable(GL_LIGHTING);
            {

                GLfloat ambientColor[] = {0.f, 0.f, 0.f, 1.0f};
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
                GLfloat lightVector[] = {4.f, 5.f, 3.f, 1.0f};
                glLightfv(GL_LIGHT0, GL_POSITION, lightVector);
                GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
                glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
                GLfloat diffuse[] = {0.8f, 0.8f, 0.f, 1.0f};
                glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
                GLfloat specular[] = {0.f, 0.f, 0.f, 1.0f};
                glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
                glEnable(GL_LIGHT0);

            }

            {
                GLfloat ambient[] = {1.f, 1.f, 1.f, 1.0f};
                glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
                GLfloat diffuse[] = {1.f, 1.f, 1.f, 1.0f};
                glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
                GLfloat specular[] = {0.01f, 0.01f, 0.01f, 1.0f};
                glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
                glMaterialf(GL_FRONT, GL_SHININESS, 96.f);
                glShadeModel((sjencanje == KonstantnoSjencanje) ? GL_FLAT : GL_SMOOTH);
            }
            break;
        default:
            throw "Unknown inacica";
    }
    if (z_spremnik)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);



    //glColor3f(1,0,0);
    {
        for (shared_ptr<Triangle> face:Object3D::current->faces) {
            if (inacica == 2 && (Object3D::odbacivanje == 2 || Object3D::odbacivanje == 3) && !face->visible)
                continue;

            vector<IVectorPtr> vertices;
            for (IVectorPtr vertex0:face->getVertices()) {
                IVectorPtr vectorPtr(new Vector(vertex0->get(0), vertex0->get(1), vertex0->get(2), 1));
                IVectorPtr a4 = vectorPtr->toRowMatrix(false)->nMultiply(m)->toVector(false)->nFromHomogeneous();
                vertices.push_back(a4);
            }

            /*              IVectorPtr center = face->getPolyCenter()->toRowMatrix(false)->nMultiply(m)->toVector(false)->nFromHomogeneous();
                          glBegin(GL_POINTS);
                              glVertex3f((GLfloat) center->get(0), (GLfloat) center->get(1), (GLfloat) center->get(2));
                          glEnd();*/


            if (inacica == 2 && odbacivanje == 4 && !IRG::isAntiClockwise(vertices))
                continue;
            if (inacica == 2 && sjencanje == KonstantnoSjencanje) {
                setConstantShadingColor(face->getPlaneNormal()->normalize(), face->getPolyCenter(),
                                        IVectorPtr(new Vector(r * cos(angle), 4, r * sin(angle))));
            }

            const vector<VertexPtr> & rawVertices = face->getVertices();

            int i =0;
            glBegin(GL_POLYGON);
            for (IVectorPtr v :vertices) {

                if (inacica == 1) {
                    IVectorPtr n;
                    if(sjencanje == GouraudovoSjencanje)
                        n= rawVertices.at(i)->getNormal();
                    else
                        n=face->getPlaneNormal();
                    glNormal3f((GLfloat) n->get(0), (GLfloat) n->get(1), (GLfloat) n->get(2));
                } else if (sjencanje == GouraudovoSjencanje) {
                    setConstantShadingColor(rawVertices.at(i)->getNormal(), v,
                                            IVectorPtr(new Vector(r * cos(angle), 4, r * sin(angle))));
                }
                glVertex3f((GLfloat) v->get(0), (GLfloat) v->get(1), (GLfloat) v->get(2));
                ++i;
            }
            glEnd();
        }
    }
}

IVectorPtr multiplyByIndex(IVectorPtr a, IVectorPtr b) {
    assert(a->getDimension() == b->getDimension());
    IVectorPtr res(new Vector(a->getDimension()));
    for (int i = 0; i < a->getDimension(); i++)
        res->set(i, a->get(i) * b->get(i));
    return res;
}

IVectorPtr lightPosition(new Vector(4, 5, 3));

IVectorPtr lightAmbient(new Vector(0.2, 0.2, 0.2));
IVectorPtr lightDiffuse(new Vector(0.8, 0.8, 0));
IVectorPtr lightSpecular(new Vector(0, 0, 0));

IVectorPtr materialAmbient(new Vector(1, 1, 1));
IVectorPtr materialDiffuse(new Vector(1, 1, 1));
IVectorPtr materialSpecular(new Vector(0.01, 0.01, 0.01));

double cosinusPower = 96;

IVectorPtr ambientComponent = multiplyByIndex(lightAmbient, materialAmbient);
IVectorPtr diffuseComponent = multiplyByIndex(lightDiffuse, materialDiffuse);
IVectorPtr specularComponent = multiplyByIndex(lightSpecular, materialSpecular);


void Object3D::setConstantShadingColor(IVectorPtr normalizedNormal, IVectorPtr position, IVectorPtr observerPos) {
    IVectorPtr enteringRayV = lightPosition->nSub(position)->normalize();

    IVectorPtr exitingRayV = enteringRayV->nScalarMultiply(normalizedNormal->scalarProduct(normalizedNormal) * 2)->nSub(
            enteringRayV);

    double diffuseCosFactor = enteringRayV->scalarProduct(normalizedNormal);
    if (diffuseCosFactor < 0) diffuseCosFactor = 0;
    IVectorPtr diffuse = diffuseComponent->nScalarMultiply(diffuseCosFactor);

    double specularCosFactor = exitingRayV->scalarProduct(observerPos->nSub(position)->normalize());
    if (specularCosFactor <= 0) specularCosFactor = 0; else specularCosFactor = pow(specularCosFactor, cosinusPower);
    IVectorPtr specular = specularComponent->nScalarMultiply(specularCosFactor);

    /*cout <<ambientComponent->toString()<<endl;
    cout <<diffuse->toString()<<endl;
    cout <<specular->toString()<<endl;*/
    IVectorPtr sumComponent = ambientComponent->nAdd(diffuse->nAdd(specular));
    cout<<sumComponent->toString()<<endl;
    glColor3d(sumComponent->get(0), sumComponent->get(1), sumComponent->get(2));
}


IVectorPtr Object3D::getNormal(VertexPtr &v) {
    /*IVectorPtr n;
    for (int i = 0; i < (int) current->vertices.size(); i++) {
        IVectorPtr vc = current->vertices.at(i);
        if (vc->get(0) == v->get(0) && vc->get(1) == v->get(1) && vc->get(2) == v->get(2)) {
            n = current->vertexNormals.at((unsigned long) i);
        }
    }*/
    return v->getNormal();
}