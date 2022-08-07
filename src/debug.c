#include "opengl.h"
#include "define.h"
void debugLine(){
    glColor3ub(200, 200, 0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2i(WINDOW_WIDTH/2, 0);
    glVertex2i(WINDOW_WIDTH/2, WINDOW_HEIGHT);
    glEnd();
}

void debugLineH(int y){
    glColor3ub(200, 200, 0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2i(0, y);
    glVertex2i(WINDOW_WIDTH, y);
    glEnd();
}

void debugLineV(int x){
    glColor3ub(200, 200, 0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2i(x, 0);
    glVertex2i(x, WINDOW_HEIGHT);
    glEnd();
}
