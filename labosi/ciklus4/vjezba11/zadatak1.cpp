//
// Created by ivan on 3/12/15.
//
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <complex>
#include <stack>

using namespace std;


#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_W 1024
#define WINDOW_H 720
#define WINDOW_NAME "Program"


void display();

void reshape(int, int);

void renderScene();

void myMouse(int, int, int, int);

void myMotion(int x, int y);

void myKeyboard(unsigned char, int, int);


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

int current_window_w = WINDOW_W;
int current_window_h = WINDOW_H;


int maxLimit = 36;
bool u_boji = true;

void colorScheme2(int n) {
    if (n == -1) {
        glColor3f(0, 0, 0);
    } else if (maxLimit < 16) {
        int r = (int) ((n - 1) / (double) (maxLimit - 1) * 255 + 0.5);
        int g = 255 - r;
        int b = ((n - 1) % (maxLimit / 2)) * 255 / (maxLimit / 2);
        glColor3f(r / 255.f, g / 255.f, b / 255.f);
    } else {
        int lim = maxLimit < 32 ? maxLimit : 32;
        int r = (n - 1) * 255 / lim;
        int g = ((n - 1) % (lim / 4) * 255 / (lim / 4));
        int b = ((n - 1) % (lim / 8)) * 255 / (lim / 8);
        glColor3f(r / 255.f, g / 255.f, b / 255.f);
    }
}

void colorScheme1(int n) {
    if (n == -1)
        glColor3f(0, 0, 0);
    else
        glColor3f(1, 1, 1);
}

bool kvadratna = true;

int divergenceTestKvadratna(complex<double> c, int limit) {
    complex<double> z(0.f, 0.f);
    for (int i = 1; i <= limit; i++) {
        z = z * z + c;
        if (abs(z) > 4) return i;
    }
    return -1;
}

int divergenceTestKubna(complex<double> c, int limit) {
    complex<double> z(0.f, 0.f);
    for (int i = 1; i <= limit; i++) {
        z = z * z * z + c;
        if (abs(z) > 4) return i;
    }
    return -1;
}

double u_center = -0.5;
double v_center = 0;

double u_radius = 1.5;
double v_radius = 1.2;

double u_radius_default = 1.5;

double zoom_factor = 1;
double zoom_factor_scroll = 0.1;
/*double u_max=1.;
double u_min=-2.;
double v_max=-1.2;
double v_min=1.2;*/
stack<pair<complex<double>, double>> prev_zooms;

void update_uv(double u_center_new, double v_center_new) {
    u_center = u_center_new;
    v_center = v_center_new;

    u_radius = u_radius_default / pow(2, zoom_factor - 1);
    v_radius = u_radius * (current_window_h / (double) current_window_w);
}

void update_uv(complex<double> c) {
    update_uv(c.real(), c.imag());
}

complex<double> get_uv(int x, int y) {
    double u = (x / (float) current_window_w) * (2 * u_radius) + u_center - u_radius;
    double v = (y / (float) current_window_h) * (2 * v_radius) + v_center - v_radius;

    return complex<double>(u, v);
}

void renderScene() {
    for (int y = 0; y < current_window_h; y++) {
        for (int x = 0; x < current_window_w; x++) {

            int n = (kvadratna ? divergenceTestKvadratna : divergenceTestKubna)(get_uv(x, y), maxLimit);
            (u_boji?colorScheme2:colorScheme1)(n);

            glBegin(GL_POINTS);
            glVertex2d(x, y);
            glEnd();
        }
    }
}


void myMouse(int button, int state, int x, int y) {
    y = WINDOW_H - y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        glutPostRedisplay();
    }
        //	Desna tipka - odustani od crtanja.
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    } else if (button == 3) {
        if (state == GLUT_UP) return;
        prev_zooms.push(pair<complex<double>, double>(complex<double>(u_center, v_center), zoom_factor));
        complex<double> c = get_uv(x, y);
        zoom_factor += zoom_factor_scroll;
        update_uv(c);
        glutPostRedisplay();
    } else if (button == 4) {
        if (state == GLUT_UP) return;
        if (prev_zooms.empty()) return;
        complex<double> c = prev_zooms.top().first;
        zoom_factor = prev_zooms.top().second;
        prev_zooms.pop();
        update_uv(c);
        glutPostRedisplay();
    }
}

void myMotion(int x, int y) {
    y = WINDOW_H - y;

}


void myKeyboard(unsigned char theKey, int, int) {
    switch (theKey) {
        case '1':
            kvadratna = true;
            glutPostRedisplay();
            break;
        case '2':
            kvadratna = false;
            glutPostRedisplay();
            break;
        case 'c':
            u_boji ^= true;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}


void reshape(int width, int height) {
    current_window_w = width;
    current_window_h = height;
    update_uv(u_center, v_center);

    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width - 1, 0, height - 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}
