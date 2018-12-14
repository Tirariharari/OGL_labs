#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glaux.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "header.h"

GLvoid LoadGLTextures() {
    AUX_RGBImageRec *tex;
    glGenTextures(8, &textures[0]);

    for(int i=0; i<8; i++){
        tex = auxDIBImageLoad(tex_name[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->sizeX, tex->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
    }
}

void TimerFunction (int value) {
    glutPostRedisplay();
    glutTimerFunc(10,TimerFunction,1);
    ox_rotation+=dx_rotation;
    oy_rotation+=dy_rotation;
    sun_rotation += dx_sun_rotation;
}

void glutNormalKeys(unsigned char key, int x, int y) {
    switch(key)
    {
    case 'a':
        dx_rotation = -0.5;
        break;
    case 'd':
        dx_rotation = 0.5;
        break;
    case 'w':
        dy_rotation = -0.5;
        break;
    case 's':
        dy_rotation = 0.5;
        break;
    case 'q':
        dy_rotation = 0;
        dx_rotation = 0;
        break;
    case 'e':
        if (!opened)
            opened = 2;
        else
            opened = 0;
        break;
    case 'r':
        if (sun_mode>=0)
        {
            sun_mode--;
            dx_sun_rotation--;
        }
        else
        {
            sun_mode = 1;
            dx_sun_rotation=1;
        }
        break;
    case 'z':
        exit(0);
        break;
    case 'f':
        if (light_on)
            glDisable(GL_LIGHT0);
        else
            glEnable(GL_LIGHT0);
        light_on = !light_on;
        break;
    case '1':
        color_mode = 1;
        break;
    case '2':
        color_mode = 2;
        break;
    case '3':
        color_mode = 3;
        break;
    case '4':
        if (alpha == 0.5)
            alpha = 1;
        else
            alpha = 0.5;
        break;
    default:
        break;
    }
}

void Draw () {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //  Light and sphere
    glLoadIdentity();
    glColor4f(1.0, 0.0, 0.0, alpha);
    glTranslatef (0, 0, -30);
    glRotatef((sun_rotation), 0, 1, 0);
    glTranslatef (0, 0, -30);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();
    glColor3d(1,0,0);
    gluQuadricDrawStyle(quadObj, GLU_LINE);
    gluSphere(quadObj, 2, 20, 10);

    //  Oct
    glLoadIdentity();
    glTranslatef (0, 0, -20);
    glRotatef((ox_rotation), 0, 1, 0);
    glRotatef((oy_rotation), 1, 0, 0);

    switch (color_mode){
    case 1:{
        glBegin(GL_TRIANGLES);
            glColor4f(0.0, 1.0, 0.0, alpha);  /// 123 - green
            glNormal3d(-1, -1, 1);
            glVertex3f(0+opened, 10+opened, 0-opened);
            glVertex3f(0+opened, 0+opened, -10-opened);
            glVertex3f(10+opened, 0+opened, 0-opened);

            glColor4f(1.0, 0.0, 0.0, alpha);  ///134 - red
            glNormal3d(-1, -1, -1);
            glVertex3f(0+opened, 10+opened, 0+opened);
            glVertex3f(10+opened, 0+opened, 0+opened);
            glVertex3f(0+opened, 0+opened, 10+opened);

            glColor4f(0.0, 0.0, 1.0, alpha);  /// 145 - blue
            glNormal3d(1, -1, -1);
            glVertex3f(0-opened, 10+opened, 0+opened);
            glVertex3f(0-opened, 0+opened, 10+opened);
            glVertex3f(-10-opened, 0+opened, 0+opened);

            glColor4f(0.0, 1.0, 1.0,alpha);  /// 236 - light blue
            glNormal3d(1, -1, -1);
            glVertex3f(0+opened, 0-opened, -10-opened);
            glVertex3f(10+opened, 0-opened, 0-opened);
            glVertex3f(0+opened, -10-opened, 0-opened);

            glColor4f(1.0, 1.0, 0.0, alpha);  /// 346 - yellow
            glNormal3d(-1, 1, -1);
            glVertex3f(0+opened, 0-opened, 10+opened);
            glVertex3f(10+opened, 0-opened, 0+opened);
            glVertex3f(0+opened, -10-opened, 0+opened);

            glColor4f(1.0, 0.0, 1.0, alpha);  /// 456 - purple
            glNormal3d(-1, -1, 1);
            glVertex3f(0-opened, 0-opened, 10+opened);
            glVertex3f(-10-opened, 0-opened, 0+opened);
            glVertex3f(0-opened, -10-opened, 0+opened);

            glColor4f(1.0, 0.5, 0.0, alpha);  /// 125 - orange
            glNormal3d(-1, 1, -1);
            glVertex3f(0-opened, 10+opened, 0-opened);
            glVertex3f(0-opened, 0+opened, -10-opened);
            glVertex3f(-10-opened, 0+opened, 0-opened);

            glColor4f(1.0, 0.0, 0.0, alpha);  /// 256 - rgb
            glNormal3d(1, 1, 1);
            glVertex3f(0-opened, 0-opened, -10-opened);
            glColor4f(0.0, 1.0, 0.0, alpha);
            glVertex3f(-10-opened, 0-opened, 0-opened);
            glColor4f(0.0, 0.0, 1.0, alpha);
            glVertex3f(0-opened, -10-opened, 0-opened);

        glEnd();
        break;
    }
    case 2:{
        glEnable(GL_TEXTURE_2D);
        glColor4f(1.0, 1.0, 1.0, alpha);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glBegin(GL_TRIANGLES);
            glNormal3f(-1, -1, 1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 10+opened, 0-opened);
            glTexCoord2f(1, 0);
            glVertex3f(0+opened, 0+opened, -10-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(10+opened, 0+opened, 0-opened);

            glNormal3f(-1, -1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 10+opened, 0+opened);
            glTexCoord2f(1, 0);
            glVertex3f(10+opened, 0+opened, 0+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0+opened, 0+opened, 10+opened);

            glNormal3f(1, -1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 10+opened, 0+opened);
            glTexCoord2f(1, 0);
            glVertex3f(0-opened, 0+opened, 10+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(-10-opened, 0+opened, 0+opened);

            glNormal3f(1, -1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 0-opened, -10-opened);
            glTexCoord2f(1, 0);
            glVertex3f(10+opened, 0-opened, 0-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0+opened, -10-opened, 0-opened);

            glNormal3f(-1, 1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 0-opened, 10+opened);
            glTexCoord2f(1, 0);
            glVertex3f(10+opened, 0-opened, 0+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0+opened, -10-opened, 0+opened);

            glNormal3f(-1, -1, 1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 0-opened, 10+opened);
            glTexCoord2f(1, 0);
            glVertex3f(-10-opened, 0-opened, 0+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0-opened, -10-opened, 0+opened);

            glNormal3f(-1, 1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 10+opened, 0-opened);
            glTexCoord2f(1, 0);
            glVertex3f(0-opened, 0+opened, -10-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(-10-opened, 0+opened, 0-opened);

            glNormal3f(1, 1, 1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 0-opened, -10-opened);
            glTexCoord2f(1, 0);
            glVertex3f(-10-opened, 0-opened, 0-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0-opened, -10-opened, 0-opened);

        glEnd();
        glDisable(GL_TEXTURE_2D);
        break;
    }
    case 3:{
        glEnable(GL_TEXTURE_2D);
        glColor4f(1.0, 1.0, 1.0, alpha);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glBegin(GL_TRIANGLES);
            glNormal3d(-1, -1, 1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 10+opened, 0-opened);
            glTexCoord2f(1, 0);
            glVertex3f(0+opened, 0+opened, -10-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(10+opened, 0+opened, 0-opened);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glBegin(GL_TRIANGLES);
            glNormal3d(-1, -1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 10+opened, 0+opened);
            glTexCoord2f(1, 0);
            glVertex3f(10+opened, 0+opened, 0+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0+opened, 0+opened, 10+opened);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBegin(GL_TRIANGLES);
            glNormal3d(1, -1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 10+opened, 0+opened);
            glTexCoord2f(1, 0);
            glVertex3f(0-opened, 0+opened, 10+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(-10-opened, 0+opened, 0+opened);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glBegin(GL_TRIANGLES);
            glNormal3d(1, -1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 0-opened, -10-opened);
            glTexCoord2f(1, 0);
            glVertex3f(10+opened, 0-opened, 0-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0+opened, -10-opened, 0-opened);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glBegin(GL_TRIANGLES);
            glNormal3d(-1, 1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0+opened, 0-opened, 10+opened);
            glTexCoord2f(1, 0);
            glVertex3f(10+opened, 0-opened, 0+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0+opened, -10-opened, 0+opened);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textures[5]);
        glBegin(GL_TRIANGLES);
            glNormal3d(-1, -1, 1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 0-opened, 10+opened);
            glTexCoord2f(1, 0);
            glVertex3f(-10-opened, 0-opened, 0+opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0-opened, -10-opened, 0+opened);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textures[6]);
        glBegin(GL_TRIANGLES);
            glNormal3d(-1, 1, -1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 10+opened, 0-opened);
            glTexCoord2f(1, 0);
            glVertex3f(0-opened, 0+opened, -10-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(-10-opened, 0+opened, 0-opened);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textures[7]);
        glBegin(GL_TRIANGLES);
            glNormal3d(1, 1, 1);
            glTexCoord2f(0, 0);
            glVertex3f(0-opened, 0-opened, -10-opened);
            glTexCoord2f(1, 0);
            glVertex3f(-10-opened, 0-opened, 0-opened);
            glTexCoord2f(0.5, 1);
            glVertex3f(0-opened, -10-opened, 0-opened);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        break;
    }
    default:
        break;
    }

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (GLdouble)w/h, 1, 90);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, (GLdouble)w, (GLdouble)h);

    Draw ();
}

int main(int argc,char** argv) {
    std::cout << "w - turn up\ns - turn down\na - turn left\nd - turn right\nq - stop rotation\ne - open octahedron\nf - invert the light\nr - change sun mode\nz - exit\n" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Octahedron");
    glutDisplayFunc(Draw);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(5, TimerFunction, 0.5);
    glutKeyboardFunc(glutNormalKeys);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glClearColor(0,0,0,0);
    LoadGLTextures();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);

    return 0;
}
