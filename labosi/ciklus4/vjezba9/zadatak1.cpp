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
#include "Object3D.h"
#include "Triangle.h"





Object3DPtr model;




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
    Object3DPtr obj =model->normalize();
    obj->calculateVertexNormals();
    Object3D::glutShow(obj);
    return 0;
}