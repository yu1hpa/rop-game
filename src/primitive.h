#pragma once
#include <gl/glpng.h>
#include "opengl.h"

typedef struct Vec2{
    int x;
    int y;
} vec2;

typedef struct Block{
    vec2 p;
    char s[0x20];
} block_t;

void Rect(int, int, int, int);
void Text(const int, const int, const char*, void*);
void centerText(int, int, const char*, void*, int);
void inBlockText(vec2, const char*);
void frame(int, int, int, int);
void centerTextROMAN24(int, int, const char*);
void textROMAN24(int, int, const char*);
void PutSprite(int, int, int, pngInfo *);
