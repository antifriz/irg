//
// Created by ivan on 3/12/15.
//
#include <GL/glut.h>
#include <vector>
#include <iostream>

using namespace std;

// struktura koja definira liniju
typedef struct t {
    int Lx[2];
    int Ly[2];
} linijaS;

// trenutna linija koja se crta
linijaS trenutnaLinija;

// stanje trenutne linije koja se crta
int zadavanje_linije__stanje = 0;

// lista nacrtanih linija
vector<linijaS> linije;

// zastavica kontrola
int kontrola = false;

// zastavica odsijecanje
int odsijecanje = false;

void display();

void reshape(int, int);

void renderScene();

void myMouse(int, int, int, int);

void myPassiveMouse(int, int);

void myKeyboard(unsigned char, int, int);

void nacrtajLiniju(linijaS);


void linijaBresenham(int, int, int, int);

void linijaBresenhamKPlus(int, int, int, int);

void linijaBresenhamKMinus(int, int, int, int);

linijaS *odsijeciCohenSutherland(linijaS *);

int dohvatiCSKodTocke(int, int);

int window_width = 200;
int window_height = 200;
int subwindow_x1 = 50;
int subwindow_x2 = 150;
int subwindow_y1 = 50;
int subwindow_y2 = 150;

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Primjer 1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);

    glutMainLoop();
}

void display() {
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
    glOrtho(0, width - 1, height - 1, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}


void renderScene() {

    // nacrtaj nacrtane trokute
    for (auto linija : linije)
        nacrtajLiniju(linija);

}

void nacrtajLiniju(linijaS r) {

    int preskoci = 0;
    linijaS *s = odsijecanje ? odsijeciCohenSutherland(&r) : &r;

    if (s == nullptr) return;

    //crtanje linije bresenhamovim algoritmom
    linijaBresenham(s->Lx[0], s->Ly[0], s->Lx[1], s->Ly[1]);

    // crtaj primitivima samo ako je kontrola == true
    if (!kontrola) return;
    // linija GL primitivima, 4 slikovna elementa desno
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    {
        glVertex2i(s->Lx[0] + 4, s->Ly[0]);
        glVertex2i(s->Lx[1] + 4, s->Ly[1]);
    }
    glEnd();
}

inline linijaS *odsijeciCohenSutherland(linijaS *s) {
    int kodS = dohvatiCSKodTocke(s->Lx[0], s->Ly[0]);
    int kodE = dohvatiCSKodTocke(s->Lx[1], s->Ly[1]);

    //ako je cijela linija unutar podprozora, nacrtaj ju
    if (!kodS && !kodE) return s;

    int result = kodE & kodS;
    if (!result) return nullptr;


}

inline int dohvatiCSKodTocke(int x, int y) {
    int kod = 0;
    if (x < subwindow_x1) kod |= 1000;
    if (x > subwindow_x2) kod |= 0100;
    if (y < subwindow_y1) kod |= 0010;
    if (y > subwindow_y2) kod |= 0001;
    return kod;
}

void linijaBresenham(int xs, int ys, int xe, int ye) {
    glColor3f(0, 0, 0);
    glBegin(GL_POINTS);
    {
        if (xs <= xe)
            (ys <= ye ? linijaBresenhamKPlus : linijaBresenhamKMinus)(xs, ys, xe, ye);
        else
            (ys >= ye ? linijaBresenhamKPlus : linijaBresenhamKMinus)(xe, ye, xs, ys);
    }
    glEnd();
}

void linijaBresenhamKPlus(int xs, int ys, int xe, int ye) {
    if (ye - ys <= xe - xs) {

        int a = 2 * (ye - ys);
        int yc = ys;
        int yf = -(xe - xs);
        int korekcija = -2 * (xe - xs);

        for (int x = xs; x <= xe; ++x) {
            glVertex2i(x, yc);
            yf += a;
            if (yf >= 0) {
                yc++;
                yf += korekcija;
            }
        }
    } else {
        int k;
        k = xs;
        xs = ys;
        ys = k;
        k = xe;
        xe = ye;
        ye = k;

        int a = 2 * (ye - ys);
        int yc = ys;
        int yf = -(xe - xs);
        int korekcija = -2 * (xe - xs);

        for (int x = xs; x <= xe; ++x) {
            glVertex2i(yc, x);
            yf += a;
            if (yf >= 0) {
                yc++;
                yf += korekcija;
            }
        }
    }

}

void linijaBresenhamKMinus(int xs, int ys, int xe, int ye) {
    if (-(ye - ys) <= xe - xs) {

        int a = 2 * (ye - ys);
        int yc = ys;
        int yf = (xe - xs);
        int korekcija = 2 * (xe - xs);

        for (int x = xs; x <= xe; ++x) {
            glVertex2i(x, yc);
            yf += a;
            if (yf <= 0) {
                yc--;
                yf += korekcija;
            }
        }
    } else {
        int k;
        k = xe;
        xe = ys;
        ys = k;
        k = xs;
        xs = ye;
        ye = k;

        int a = 2 * (ye - ys);
        int yc = ys;
        int yf = (xe - xs);
        int korekcija = 2 * (xe - xs);

        for (int x = xs; x <= xe; ++x) {
            glVertex2i(yc, x);
            yf += a;
            if (yf <= 0) {
                yc--;
                yf += korekcija;
            }
        }
    }

}

void myMouse(int button, int state, int x, int y) {
    // ako je pritisnuta lijeva tipka misa
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        //	spremaj tocke trokuta
        trenutnaLinija.Lx[zadavanje_linije__stanje] = x;
        trenutnaLinija.Ly[zadavanje_linije__stanje] = y;
        zadavanje_linije__stanje ^= 1;

        if (!zadavanje_linije__stanje) {
            linije.push_back(trenutnaLinija);
            cout << "Tocka 2: " << x << ", " << y << endl;
        } else
            cout << "Tocka 1: " << x << ", " << y << endl;

        glutPostRedisplay();
    }
        //	Desna tipka - odustani od crtanja.
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        zadavanje_linije__stanje = 0;
        glutPostRedisplay();
    }

}

void myKeyboard(unsigned char theKey, int, int) {
    switch (theKey) {
        case 'k':
            kontrola ^= 1;
            glutPostRedisplay();
            break;

        case 'o':
            odsijecanje ^= 1;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}
