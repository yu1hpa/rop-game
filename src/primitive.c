#include "opengl.h"
#include "primitive.h"
#include "define.h"
#include <string.h>

void Rect(int x, int y, int sx, int sy){
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x, y + sy);
    glVertex2i(x + sx, y + sy);
    glVertex2i(x + sx, y);
    glEnd();
}

void Text(const int x, const int y, const char *str, void *font){
    glRasterPos2i(x, y);
    for (int i = 0; i < strlen(str); i++) {
        glutBitmapCharacter(font, str[i]);
    }
}

void centerText(int x, int y, const char *str, void *font, int fonth){
    int len = glutBitmapLength(font, (unsigned char*)str);
    int tx = x - len / 2;
    int ty = y + fonth / 2;
    Text(tx, ty, str, font);
}

void centerTextROMAN24(int x, int y, const char *str){
    centerText(x, y, str, GLUT_BITMAP_TIMES_ROMAN_24, 12);
}

void textROMAN24(int x, int y, const char *str){
    Text(x, y, str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void frame(int x, int y, int sx, int sy){
    glLineWidth(5.0);
    //左側の縦棒
    glBegin(GL_LINES);
    glVertex2i(x, y);
    glVertex2i(x, y + sy);
    glEnd();
    //上側の横棒
    glBegin(GL_LINES);
    glVertex2i(x - 2.5, y);
    glVertex2i(x + sx + 2.5, y);
    glEnd();
    //右側の縦棒
    glBegin(GL_LINES);
    glVertex2i(x + sx, y);
    glVertex2i(x + sx, y + sy);
    glEnd();
    //下側の横棒
    glBegin(GL_LINES);
    glVertex2i(x - 2.5, y + sy);
    glVertex2i(x + sx + 2.5, y + sy);
    glEnd();
}

void PutSprite(int num, int x, int y, pngInfo *info){
    int w, h;
    w = info->Width;
    h = info->Height;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, num);
    glColor4ub(255, 255, 255, 255);

    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex2i(x, y);

    glTexCoord2i(0, 1);
    glVertex2i(x, y + h);

    glTexCoord2i(1, 1);
    glVertex2i(x + w, y + h);

    glTexCoord2i(1, 0);
    glVertex2i(x + w, y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
