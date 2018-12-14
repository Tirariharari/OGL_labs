#ifndef HEADER_H
#define HEADER_H

#define WIN_HEIGHT 750
#define WIN_WIDTH 750

#include <vector>

GLfloat ox_rotation = 0;  //  for oct rotation
GLfloat dx_rotation = 0.5;
GLfloat oy_rotation = 0;
GLfloat dy_rotation = 0;

GLfloat light_pos [] = {0, 0, 0, 1};
bool light_on = true;
GLfloat sun_rotation = 0;
GLfloat dx_sun_rotation = 1;
int sun_mode = 1;
int color_mode = 2;
GLfloat alpha = 1;

GLint opened = 0;
GLuint textures[8];
char *tex_name[] = {
    "textures/texture_1.bmp",
    "textures/texture_2.bmp",
    "textures/texture_3.bmp",
    "textures/texture_4.bmp",
    "textures/texture_5.bmp",
    "textures/texture_6.bmp",
    "textures/texture_7.bmp",
    "textures/texture_8.bmp",
};

#endif // HEADER_H

