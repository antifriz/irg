//
// Created by ivan on 3/12/15.
//
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <IRG.hpp>

#include "Vector.hpp"

using namespace std;


#define WINDOW_X 200
#define WINDOW_Y 150
#define WINDOW_W 640
#define WINDOW_H 480
#define WINDOW_NAME "Program"


int mouse_x = 0, mouse_y = 0;



typedef IVectorPtr Point;

std::vector<Point> points;


double catchAndMoveOffset = 10;
Point catchAndMovePoint;
bool catchAndMoveState = false;



void display();

void reshape(int, int);

void renderScene();

void myMouse(int, int, int, int);

void myMotion(int x, int y);

void myKeyboard(unsigned char, int, int);

void renderControlPoly();

void draw_bezier(std::vector<Point> points,int divs);

void renderApproxBezier();

void renderInterBezier();

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    glutCreateWindow(WINDOW_NAME);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);

    glutMainLoop();
    return 0;
}


void display() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    renderScene();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width - 1, 0, height - 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}


void renderScene() {
    renderControlPoly();
    if(points.size()<3) return;

    renderApproxBezier();
    renderInterBezier();
}

void renderInterBezier() {
    vector<Point> points2 = Bezier::getHomogeneousControlPoints(points);
    glColor3f(1.0f, 1.0f, 0.0f);
    draw_bezier(points2, (int) (points2.size()*10));
}

void renderApproxBezier() {
    glColor3f(0.0f, 0.0f, 1.0f);
    draw_bezier(points, (int) (points.size()*10));
}

void renderControlPoly() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    {
        for (auto& point: points)
            glVertex2i((GLint) point->get(0), (GLint) point->get(1));
    }
    glEnd();
}





void draw_bezier(std::vector<Point> points,int divs) {
    int n = (int) points.size() -1;
    if(n<1) return;

    std::vector<unsigned long> binomial_coeff =Bezier::getBinomials(n);



    glBegin(GL_LINE_STRIP);
    {
        for (int i = 0; i <= divs; ++i) {
            double t = 1.0/divs * i;
            double x =0, y=0;
            double b;
            for (int j = 0; j <= n; ++j) {

                if(j==0){
                    b=binomial_coeff[j]*pow(1-t,n);
                }
                else if(j==n){
                    b=binomial_coeff[j]*pow(t,n);
                } else
                    b=binomial_coeff[j]*pow(t,j)*pow(1-t,n-j);

                x +=b*points[j]->get(0);
                y += b*points[j]->get(1);
            }
            glVertex2d(x,y);
        }
    }
    glEnd();
}


void myMouse(int button, int state, int x, int y) {
    y = WINDOW_H - y;
    Point currentPoint(new Vector(x,y));

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        points.emplace_back(currentPoint);
        glutPostRedisplay();
    }
        //	Desna tipka - odustani od crtanja.
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        for(Point &point : points){
            if(point->nSub(currentPoint)->norm() < catchAndMoveOffset){
                catchAndMovePoint =  point;
                catchAndMoveState = true;
                return;
            };
        }
    }
    catchAndMoveState = false;
}

void myMotion(int x, int y) {
    if(!catchAndMoveState) return;

    y = WINDOW_H - y;

    catchAndMovePoint->set(0,x);
    catchAndMovePoint->set(1,y);
    glutPostRedisplay();
}


void myKeyboard(unsigned char theKey, int, int) {
    switch (theKey) {
        case 27:
            points.clear();
            glutPostRedisplay();
            break;
        default:
            break;
    }
}
