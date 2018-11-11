#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

GLfloat sun_pos_x = 0;
GLfloat sun_pos_y = 0;
bool night = true;

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
    glPointSize(1);
    /// Отрисовка домика, неба и травы
    if (night)
        glColor3ub (63, 79, 40);
    else
        glColor3ub (123, 160, 91);
    glBegin (GL_QUADS);  /// ТРАВА
        glVertex2d (0, 0);
        glVertex2d (0, 375);
        glVertex2d (750, 375);
        glVertex2d (750, 0);
    glEnd ();

    if (night)
        glColor3ub (17, 100, 125);
    else
        glColor3ub (39, 189, 219);
    glBegin (GL_QUADS);  /// НЕБО
        glVertex2d (0, 750);
        glVertex2d (0, 375);
        glVertex2d (750, 375);
        glVertex2d (750, 750);
    glEnd ();

    if (night)
        glColor3ub (54, 54, 28);
    else
         glColor3ub (94, 67, 49);
    glBegin (GL_QUADS);  /// ДОМ (стены)
        glVertex2d (325, 325);
        glVertex2d (325, 425);
        glVertex2d (425, 425);
        glVertex2d (425, 325);
    glEnd ();

    glBegin (GL_POLYGON);  /// ДОМ (крыша)
        glVertex2d (300, 425);
        glVertex2d (375, 470);
        glVertex2d (450, 425);
    glEnd ();
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
