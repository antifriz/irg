//
// Created by ivan on 3/12/15.
//
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>

#include "Vector.hpp"

using namespace std;


#define IZVAN -1
#define RUB 0
#define UNUTAR 1


int stanje = 1;
bool popunjavanje = true;
bool konveksnost = false;

typedef struct {
    IVectorPtr vrh;
    IVectorPtr brid;
    bool lijevi;
} polyElemT;

typedef vector<polyElemT> polyT;
typedef IVectorPtr tocka2dT;
typedef IVectorPtr brid2dT;

polyT poly;


void display();

void reshape(int, int);

void renderScene();

void myMouse(int, int, int, int);

void myKeyboard(unsigned char, int, int);

void izracunajKoefKonvPoly();

int odnosTockeIBrida(tocka2dT& tocka, brid2dT& brid, bool isCw);

int odnosTockeIPoligona(tocka2dT& tocka);

bool isCwPoly();

bool jeKonveksan(polyT& t);

bool zadrzavaKonveksnost(tocka2dT& vrh);


void nacrtajPopunjeniPoly();

#define WINDOW_X 200
#define WINDOW_Y 150
#define WINDOW_W 640
#define WINDOW_H 480
#define WINDOW_NAME "Program"

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

    glutMainLoop();
    return 0;
}


void display() {
    if (konveksnost)
        glClearColor(0.5f, 1.0f, 0.5f, 1.0f);
    else
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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
    glColor3f(0.0f, 0.0f, 0.0f);
    if (popunjavanje) {
        nacrtajPopunjeniPoly();
    } else {
        glBegin(GL_LINE_LOOP);
        {

            for (auto& elem: poly) {
                glVertex2i((GLint) elem.vrh->get(0), (GLint) elem.vrh->get(1));
            }
        }
        glEnd();

    }
}

void nacrtajPopunjeniPoly() {
    if (poly.size() < 3) return;

    bool isCW = isCwPoly();

    double xmin, xmax, ymin, ymax;

    xmin = xmax = poly.front().vrh->get(0);
    ymin = ymax = poly.front().vrh->get(1);
    for (auto it = poly.begin() + 1; it < poly.end(); it++) {
        if (xmin > it->vrh->get(0)) xmin = it->vrh->get(0);
        if (xmax < it->vrh->get(0)) xmax = it->vrh->get(0);
        if (ymin > it->vrh->get(1)) ymin = it->vrh->get(1);
        if (ymax < it->vrh->get(1)) ymax = it->vrh->get(1);
    }

    for (auto y = ymin; y <= ymax; y++) {
        auto L = xmin, D = xmax;
        auto it0 = poly.end() - 1;
        for (auto it = poly.begin(); it < poly.end(); it++) {

            if (it0->brid->get(0) == 0) {
                if (it0->vrh->get(1) == y) {
                    L = it0->vrh->get(0);
                    D = it->vrh->get(0);
                    if (L > D) swap(L, D);
                    break;
                }
            } else {
                auto x = round(-it0->brid->get(1) * y - it0->brid->get(2)) / it0->brid->get(0);
                (isCW && it0->lijevi) || (!isCW && !it0->lijevi) ? (L = max(L, x)) : (D = min(D, x));
            }
            it0 = it;
        }

        glBegin(GL_LINES);
        {
            glVertex2d(L, y);
            glVertex2d(D, y);
        }
        glEnd();
    }
}


void myMouse(int button, int state, int x, int y) {
    // ako je pritisnuta lijeva tipka misa
    y = WINDOW_H - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        tocka2dT vrh = Vector::Create(x, y, 1);

        if (stanje == 1) {
            if (konveksnost && !zadrzavaKonveksnost(vrh)) {
                cout << "Vrh odbijen, poligon ne bi bio konveksan" << endl;
                return;
            }

            polyElemT elem;
            elem.vrh = vrh;
            poly.push_back(elem);

            cout << "Dodana tocka: " << x << " " << y << endl;


            izracunajKoefKonvPoly();

            glutPostRedisplay();
        } else {
            switch (odnosTockeIPoligona(vrh)) {
                case UNUTAR:
                    cout << "Unutar poligona" << endl;
                    break;
                case RUB:
                    cout << "Rub poligona" << endl;
                    break;
                case IZVAN:
                default:
                    cout << "Izvan poligona" << endl;
                    break;
            }
        }


    }
        //	Desna tipka - odustani od crtanja.
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    }
}

void myKeyboard(unsigned char theKey, int, int) {
    switch (theKey) {
        case 'k':
            if (stanje != 1) {
                cout << "promjena zastavice konveksnost moguca samo u stanju 1" << endl;
                break;
            }
            if (konveksnost) {
                konveksnost = false;
            } else {
                if (!jeKonveksan(poly)) {
                    cout << "postavljanje konveksnosti na true nije moguce, poligon nije konveksan" << endl;
                    break;
                }
                konveksnost = true;
            }

            glutPostRedisplay();
            break;

        case 'p':
            if (stanje == 1) {
                popunjavanje ^= 1;
                cout << "popunjavanje postavljeno na: " << popunjavanje << endl;
            } else {
                cout << "popunjavanje nije moguce postaviti" << endl;
                break;
            }
            glutPostRedisplay();
            break;
        case 'n':
            if (stanje == 1) {
                if (poly.size() < 3) {
                    cout << "potrebne su bar tri tocke za prijelaz u stanje 2" << endl;
                    break;
                }
                stanje = 2;


            } else {
                popunjavanje = false;
                cout << "popunjavanje postavljeno na: " << popunjavanje << endl;
                konveksnost = false;
                cout << "konveksnost postavljena na: " << konveksnost << endl;
                poly.clear();
                stanje = 1;
            }
            cout << "stanje postavljeno na: " << stanje << endl;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}


void izracunajKoefKonvPoly() {
    auto it0 = poly.end();
    it0--;
    for (auto it = poly.begin(); it < poly.end(); it++) {
        it0->brid = it0->vrh->nVectorProduct(it->vrh);
        it0->lijevi = it0->vrh->get(1) < it->vrh->get(1);
        it0 = it;
    }
}


bool isCwPoly() {
    //pod pretpostavkom da znamo da je konveksan
    auto it0 = poly.end() - 1;

    for (auto it = poly.begin(); it < poly.end(); it++) {
        double sp = it->brid->scalarProduct(it0->vrh);
        if (sp == 0) continue;
        return sp < 0;
    }
    return true;
}


bool zadrzavaKonveksnost(tocka2dT& vrh) {
    if (poly.size() < 3) return true;

    if (odnosTockeIBrida(vrh, (poly.end() - 2)->brid, isCwPoly()) == IZVAN) return false;

    if (odnosTockeIBrida(vrh, poly.front().brid, isCwPoly()) == IZVAN) return false;

    return odnosTockeIBrida(vrh, poly.back().brid, isCwPoly()) != UNUTAR;
}

int odnosTockeIBrida(tocka2dT& tocka, brid2dT& brid, bool isCw) {
    auto sp = tocka->scalarProduct(brid);

    cout << "ispitujem odnos" << endl;


    // je li na rubu
    if (sp == RUB)
        return RUB;

    // s obzirom na orijentaciju ispitaj je li izvan, ako je izadi
    return isCw ? sp > 0 : sp < 0 ? IZVAN : UNUTAR;
}


int odnosTockeIPoligona(tocka2dT& tocka) {
    cout << "pokret1" << endl;

    if (poly.begin() + 1 >= poly.end())
        return UNUTAR;
    cout << "pokret" << endl;
    bool isCw = isCwPoly();
    bool edge = false;
    for (auto it = poly.begin(); it < poly.end(); it++) {
        auto odnos = odnosTockeIBrida(tocka, it->brid, isCw);

        // je li na rubu
        if (odnos == RUB) {
            edge = true;
            continue;
        }
        if (odnos == IZVAN)
            return IZVAN;
    }
    return edge ? RUB : UNUTAR;
}

bool jeKonveksan(polyT& t) {
    return true;
}
