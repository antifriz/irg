//
// Created by ivan on 3/12/15.
//
#include <GL/glut.h>
#include <vector>

using namespace std;

// moguce boje
enum boje {
    crvena, zelena, plava, cijan, zuta, magneta, BROJ_BOJA
};

// trenutna boja
boje boja = crvena;

// struktura koja definira trokut
typedef struct t {
    int Lx[3];
    int Ly[3];
    boje boja;
} trokutS;

// trenutni trokut koji se crta
trokutS trenutniTrokut;

// stanje trenutnog trokuta koji se crta
int zadavanje_trokuta__stanje = 0;

// lista nacrtanih trokuta
vector<trokutS> trokuti;

void display();

void reshape(int, int);

void renderScene();

void myMouse(int, int, int, int);

void myPassiveMouse(int, int);

void myKeyboard(unsigned char, int, int);

void mjenjajBoju(boje);

void nacrtajPokazivacaBoje();

void nacrtajTrokut(trokutS);


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(200, 200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Primjer 1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
    glutPassiveMotionFunc(myPassiveMouse);
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
    for (auto trokut : trokuti)
        nacrtajTrokut(trokut);

    // kao sto pise
    nacrtajPokazivacaBoje();

    // ako je trokut u procesu crtanja
    if (zadavanje_trokuta__stanje) {
        // nacrtaj trokut u procesu crtanja
        glBegin(GL_LINE_STRIP);
        {
            glVertex2i(trenutniTrokut.Lx[0], trenutniTrokut.Ly[0]);
            glVertex2i(trenutniTrokut.Lx[1], trenutniTrokut.Ly[1]);
            if (zadavanje_trokuta__stanje == 2)
                glVertex2i(trenutniTrokut.Lx[2], trenutniTrokut.Ly[2]);
        }
        glEnd();
    }
}

void nacrtajTrokut(trokutS s) {

    //zadaj boju i nacrtaj tri vrha
    mjenjajBoju(s.boja);
    glBegin(GL_TRIANGLES);
    {
        glVertex2i(s.Lx[0], s.Ly[0]);
        glVertex2i(s.Lx[1], s.Ly[1]);
        glVertex2i(s.Lx[2], s.Ly[2]);
    }
    glEnd();
}


void nacrtajPokazivacaBoje() {
    const int sirina = 5;

    // u gornjem desnom kutu nacrtaj pokazivaca boje

    int width = glutGet(GLUT_WINDOW_WIDTH);

    mjenjajBoju(boja);
    glBegin(GL_QUADS);
    {
        glVertex2i(width - 1, 0);
        glVertex2i(width - 1, sirina);
        glVertex2i(width - 1 - sirina, sirina);
        glVertex2i(width - 1 - sirina, 0);
    }
    glEnd();
}

void mjenjajBoju(boje boja) {

    switch (boja) {
        case crvena:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;

        case zelena:
            glColor3f(0, 1, 0);
            break;

        case plava:
            glColor3f(0, 0, 1);
            break;

        case cijan:
            glColor3f(0, 1, 1);
            break;

        case zuta:
            glColor3f(1, 0, 1);
            break;

        case magneta:
            glColor3f(1, 1, 0);
            break;

        default:
            break;
    }
}


void myMouse(int button, int state, int x, int y) {
    // ako je pritisnuta lijeva tipka misa
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //	spremaj tocke trokuta
        trenutniTrokut.Lx[zadavanje_trokuta__stanje] = x;
        trenutniTrokut.Ly[zadavanje_trokuta__stanje] = y;
        zadavanje_trokuta__stanje++;
        zadavanje_trokuta__stanje %= 3;

        if (!zadavanje_trokuta__stanje) {
            trenutniTrokut.boja = boja;
            trokuti.push_back(trenutniTrokut);
        } else {

            trenutniTrokut.Lx[zadavanje_trokuta__stanje] = x;
            trenutniTrokut.Ly[zadavanje_trokuta__stanje] = y;
        }

        glutPostRedisplay();
    }
        //	Desna tipka - odustani od crtanja.
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        zadavanje_trokuta__stanje = 0;
        glutPostRedisplay();
    }

}

void myPassiveMouse(int x, int y)
{
    // za povlacenje linije do trenutne pozicije misa
    if (zadavanje_trokuta__stanje > 0) {
        trenutniTrokut.Lx[zadavanje_trokuta__stanje] = x;
        trenutniTrokut.Ly[zadavanje_trokuta__stanje] = y;
        //treba nacrtati liniju do pokazivaca
        glutPostRedisplay();
    }
}

void myKeyboard(unsigned char theKey, int, int) {
    switch (theKey) {
        case 'n':
            boja = (boje) ((int) boja + 1);
            if (boja >= BROJ_BOJA) boja = crvena;
            mjenjajBoju(boja);
            glutPostRedisplay();
            break;

        case 'p':
            boja = (boje) ((int) boja - 1);
            if (boja < 0) boja = (boje) ((int) BROJ_BOJA - 1);
            mjenjajBoju(boja);
            glutPostRedisplay();
            break;
        default:
            break;
    }
}
