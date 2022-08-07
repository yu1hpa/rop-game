#include "opengl.h"
#include <stdio.h>

char keych;

void
Keyboard(unsigned char key, int x, int y){
    keych = key;
}

int
isPressed(unsigned char key){
    if(keych == key){
        keych = -1;
        return 1;
    } else {
        return 0;
    }
}
