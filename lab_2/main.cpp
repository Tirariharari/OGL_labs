#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

GLfloat sun_pos_x = 0;
GLfloat sun_pos_y = 0;
bool night = false;

static GLfloat vert[] = {
    0, 0,  /// Grass
    0, 375,
    750, 375,
    750, 0,

    0, 750,  ///  Sky
    0, 375,
    750, 375,
    750, 750,

    325, 325,  /// House
    325, 425,
    425, 425,
    425, 325,

    300, 425,  ///  Roof
    375, 470,
    450, 425
};

static GLubyte colors_day [] = {
    123, 160, 91,  ///  Grass
    123, 160, 91,
    123, 160, 91,
    123, 160, 91,

    39, 189, 219,  ///  Sky
    39, 189, 219,
    39, 189, 219,
    39, 189, 219,

    94, 67, 49,  ///  House
    94, 67, 49,
    94, 67, 49,
    94, 67, 49,

    94, 67, 49,  ///  Roof
    94, 67, 49,
    94, 67, 49
};

static GLubyte colors_night [] = {
    63, 79, 40,  /// Grass
    63, 79, 40,
    63, 79, 40,
    63, 79, 40,

    17, 100, 125,   ///  Sky
    17, 100, 125,
    17, 100, 125,
    17, 100, 125,

    54, 54, 28,  /// House
    54, 54, 28,
    54, 54, 28,
    54, 54, 28,

    54, 54, 28,  ///  Roof
    54, 54, 28,
    54, 54, 28
};

void drawSun(int x, int y, int siz, int ap) {
    glBegin(GL_POLYGON);
        for(int i=0; i<ap; i++) {
            double ang = PI*2/ap*i;
            glVertex2d(siz * sin(ang) + x, siz * cos(ang) + y);
        }
    glEnd();
}

void Draw () {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, vert);
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, (night)?colors_night:colors_day);

    /// Отрисовка неба, травы и дома
    glDrawArrays(GL_QUADS, 0, 12);
    glDrawArrays(GL_TRIANGLES, 12, 3);

    /// Отрисовка солнца в зависимости от времени
    if (!night) {
        glColor3ub (250, 221, 115);
        drawSun(sun_pos_x, sun_pos_y, 50, 20);
    }
    else{
        glColor3ub (255, 253, 223);
        drawSun(sun_pos_x, sun_pos_y, 50, 20);
        glColor3ub (17, 100, 125);
        drawSun(sun_pos_x-25, sun_pos_y, 30, 20);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glutSwapBuffers();
}

void ClearScreen () {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

    Draw ();
}

void TimerFunction (int value) {
    glutPostRedisplay();
    glutTimerFunc(10,TimerFunction,1);
    sun_pos_x-=1;
    if (sun_pos_x < 10) {
        sun_pos_x = 730;
        if (night)
            night = false;
        else
            night = true;
    }
}

int main(int argc,char** argv) {
    sun_pos_x = 730;
    sun_pos_y = 600;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750,750);
    glutCreateWindow("House");
    glutDisplayFunc(Draw);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(5, TimerFunction, 0.5);
    ClearScreen();
    glutMainLoop();
    return 0;
}
