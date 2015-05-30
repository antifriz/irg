//
// Created by ivan on 5/30/15.
//

#ifndef IRG_OBJECT3D_H
#define IRG_OBJECT3D_H

#include <memory>
#include <algorithm>
#include <IRG.hpp>
#include <math.h>
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>
#include <map>
#include <sstream>
#include "Vector.hpp"
#include "Triangle.h"
#include "mutuals.h"
class Object3D;
typedef shared_ptr<Object3D> Object3DPtr;


class Object3D : public std::enable_shared_from_this<Object3D> {
private:
    static Object3DPtr current;

    vector<shared_ptr<Triangle>> faces;
    vector<VertexPtr> vertices;
    map<IVectorPtr,IVectorPtr> vertexMap;
    vector<IVectorPtr> vertexNormals;


#define WINDOW_X 200
#define WINDOW_Y 150
#define WINDOW_W 640
#define WINDOW_H 480
#define WINDOW_NAME "Program"

    static void glutRenderScene();


    static void glutDisplay();


    static void glutKeyboard(unsigned char theKey, int, int);


    static void glutReshape(int width, int height);

protected:
    Object3D() {
    }


    std::size_t vertexIndex(IVectorPtr vertex);

public:
    static int inacica;
    static int odbacivanje;


    void determineFaceVisibilities1(IVectorPtr eye);

    void determineFaceVisibilities2(IVectorPtr eye);

    static void timer(int value);

    static void glutShow(const Object3DPtr &ptr);


    static Object3DPtr create();

    Object3DPtr copy();

    void addVertex(VertexPtr vertex);

    void addFaceFromVertexIDs(std::size_t idx1, std::size_t idx2, std::size_t idx3);

    static Object3DPtr loadFromOBJ(char *fname);

    Vertex::Relation convexVertexRelation(IVectorPtr vertex) {
        bool isEdge = false;
        for (auto& face: faces) {
            auto relation = face->vertexRelation(vertex);
            if (relation == Vertex::Relation::Out)
                return Vertex::Relation::Out;
            isEdge |= (relation == Vertex::Relation::Edge);
        }
        return isEdge ? Vertex::Relation::Edge : Vertex::Relation::In;
    }

    string dumpOBJ();;

    double extremeVertex(Vertex::Axis axis, bool isMax);

    void calculateVertexNormals();

    Object3DPtr normalize();



    static void setConstantShadingColor(IVectorPtr normalizedNormal, IVectorPtr position, IVectorPtr observerPos);

    IVectorPtr getNormal(VertexPtr &v);
};



#endif //IRG_OBJECT3D_H
