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
#include <map>

using namespace std;


#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_W 1366
#define WINDOW_H 768
#define WINDOW_NAME "Program"


typedef struct {
    double x;
    double y;
    double angle;
    double angleDelta;
    double distance;
    double distanceFactor;
    double thickness;
    double thicknessFactor;
} TurtleState;

class Turtle {
private:
public:
    Turtle(TurtleState &state) : state(state) { }

private:
    TurtleState state;
    stack<TurtleState> state_stack;

public:

    void save_to_stack(){
        state_stack.push(state);
    }
    void load_from_stack(){
        state = state_stack.top();
        state_stack.pop();
    }

    void modifyThickness(){
        state.thickness*=state.thicknessFactor;
    }
    void modifyLength(){
        state.distance*=state.distanceFactor;
    }


    void move(bool leave_trace) {
        if (leave_trace) {
            glLineWidth((GLfloat) state.thickness);
            glBegin(GL_LINES);
            glVertex2d(state.x, state.y);
            //cout<<"line"<<endl;
            //std::cout<<state.x<<" "<<state.y<<std::endl;
        }
        state.x += state.distance * cos(state.angle);
        state.y += state.distance * sin(state.angle);
        if (leave_trace) {
            //std::cout<<state.x<<" "<<state.y<<std::endl;
            glVertex2d(state.x, state.y);
            glEnd();
        }
    }
    void rotate( bool is_ccw){
        state.angle+=(is_ccw?1:-1)*state.angleDelta;
    }

    void make_move(char c){
        //cout<<"making move"<<endl;
        switch (c){
            case 'F':
                move(true);
                break;
            case 'f':
                move(false);
                break;
            case '+':
                rotate(true);
                break;
            case '-':
                rotate(false);
                break;
            case 'w':
                modifyThickness();
                break;
            case 's':
                modifyLength();
                break;
            case '[':
                save_to_stack();
                break;
            case ']':
                load_from_stack();
                break;
            default:
                break;
        }
    }


    void make_moves(std::string str){
        for(char c:str)
            make_move(c);
    }


};



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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    renderScene();

    glutSwapBuffers();
}

int current_window_w = WINDOW_W;
int current_window_h = WINDOW_H;


int maxLimit = 36;
bool u_boji = true;
/*
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
}*/

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
/*
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
}*/
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

std::string LS(const string& aksiom,map<char,string> &rules, int depth){
    string out_str(aksiom);
    while(depth>0)
    {
        depth--;

        string tmp;
        for(string::iterator it = out_str.begin();it!=out_str.end();it++)
        {
            map<char,string>::iterator mapit = rules.find(*it);
            if(mapit ==rules.end()){
                tmp.push_back(*it);
                continue;
            }

            string& to_replace = mapit->second;
            tmp.insert(tmp.end(),to_replace.begin(),to_replace.end());
        }
        out_str = tmp;
    }
    return out_str;
}

int biljka = 0;
void hrast_u_jesenje() {
    TurtleState state;
    state.distanceFactor=0.6;
    state.angleDelta = 50.0*M_PI/180.0;
    state.thicknessFactor=0.7;

    state.thickness = 10;
    state.distance = 330;
    state.x = current_window_w/2;
    state.y = 10;
    state.angle= M_PI/2;

    Turtle turtle(state);

    int depth = 15;
    map<char,string> rules;
    string aksiom = "FX";
    rules.insert(pair<char,string>('X',"sw[-FX]+FX"));

    string niz = LS(aksiom,rules,depth);

    glColor3f(0,0,1.0f);

    turtle.make_moves(niz);
}



void jablan_na_povjetarcu() {
    TurtleState state;
    state.distanceFactor=0.6;
    state.angleDelta = 22.5*M_PI/180.0;
    state.thicknessFactor=1;

    state.thickness = 1;
    state.distance = 13;
    state.x = current_window_w/2;
    state.y = 10;
    state.angle= M_PI/2;

    Turtle turtle(state);

    int depth = 4;
    map<char,string> rules;
    string aksiom = "F";
    rules.insert(pair<char,string>('F',"FF-[-F+F+F]+[+F-F-F]"));

    string niz = LS(aksiom,rules,depth);

    glColor3f(0,0,1.0f);

    turtle.make_moves(niz);
}



void nesto_savanasto() {
    TurtleState state;
    state.distanceFactor=0.65;
    state.angleDelta = 30.0*M_PI/180.0;
    state.thicknessFactor=0.7;

    state.thickness = 10;
    state.distance = 200;
    state.x = current_window_w/2;
    state.y = 10;
    state.angle= M_PI/2;

    Turtle turtle(state);

    int depth = 13;
    map<char,string> rules;
    string aksiom = "FX";
    rules.insert(pair<char,string>('X',"sw[-FY]+FX"));
    rules.insert(pair<char,string>('Y',"FX+FY-FX"));

    string niz = LS(aksiom,rules,depth);
    cout<<"generirao"<<endl;
    glColor3f(0,1.0f,0);

    turtle.make_moves(niz);
}



void biljka4() {
    TurtleState state;
    state.distanceFactor=0.6;
    state.angleDelta = 20.0*M_PI/180.0;
    state.thicknessFactor=1;

    state.thickness = 1;
    state.distance = 7;
    state.x = current_window_w/3;
    state.y = 10;
    state.angle= M_PI/3;

    Turtle turtle(state);

    int depth = 6;
    map<char,string> rules;
    string aksiom = "F";
    rules.insert(pair<char,string>('F',"F[+F]F[-F][F]"));

    string niz = LS(aksiom,rules,depth);

    glColor3f(0,1.0f,0);

    turtle.make_moves(niz);
}

void renderScene() {
    switch (biljka){
        case 0:
            glViewport(0, 0, (GLsizei) current_window_w/2, (GLsizei) current_window_h/2);
            nesto_savanasto();
            glViewport(current_window_w/2, 0, (GLsizei) current_window_w/2, (GLsizei) current_window_h/2);
            biljka4();
            glViewport(current_window_w/2, current_window_h/2, (GLsizei) current_window_w/2, (GLsizei) current_window_h/2);
            jablan_na_povjetarcu();
            glViewport(0, current_window_h/2, (GLsizei) current_window_w/2, (GLsizei) current_window_h/2);
            hrast_u_jesenje();
        case 1:
            hrast_u_jesenje();
            break;
        case 2:
            jablan_na_povjetarcu();
            break;
        case 3:
            nesto_savanasto();
            break;
        case 4:
            biljka4();
            break;
        default:
            assert(false);
    }

}



void myMouse(int button, int state, int x, int y) {
    y = WINDOW_H - y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        glutPostRedisplay();
    }
        //	Desna tipka - odustani od crtanja.
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    } /*else if (button == 3) {
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
    }*/
}

void myMotion(int x, int y) {
    y = WINDOW_H - y;

}


void myKeyboard(unsigned char theKey, int, int) {
    switch (theKey) {
        case '1':
            biljka = 1;
            glutPostRedisplay();
            break;
        case '2':
            biljka = 2;
            glutPostRedisplay();
            break;
        case '3':
            biljka = 3;
            glutPostRedisplay();
            break;
        case '4':
            biljka = 4;
            glutPostRedisplay();
            break;
        case '0':
        case'5':
            biljka = 0;
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
    //update_uv(u_center, v_center);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width - 1, 0, height - 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    glutPostRedisplay();
}
