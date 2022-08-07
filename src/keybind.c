#include "opengl.h"
#include "status.h"
#include "deltatime.h"
#include "define.h"
#include "keyboard.h"
#include "primitive.h"
#include "easing.h"

Status keybindStat;
unsigned int isShowKeybind = 0;


/*
 * keybindPanel
 * キー操作の方法を示すパネル
 * */
void
keybindPanel(int x, int y){
    glColor4ub(255, 255, 255, 100);
    Rect(x, y, WINDOW_WIDTH, WINDOW_HEIGHT/2);
    char s[][0x30] = {
        "E : Display KeyBind",
        "F : Store a gadget" ,
        "B : Check an answer",
        "Q : Clear blocks"
        };
    glColor3ub(0, 0, 0);
    for(int i = 0; i < 4; i++){
        textROMAN24(x+50, 50+i*50, s[i]);
    }
}

// 第一引数に deltaTを渡す
void
showKeybind(deltat_t deltaT){
    if(isPressed('e')){
        isShowKeybind ^= 1;
    }
    static double t = 0;
    if(keybindStat == CLOSE){
        keybindPanel((WINDOW_WIDTH+200), 0);
        if(isShowKeybind){
            keybindStat = EIN;
            isShowKeybind = 0;
        }
    }
    else if(keybindStat == EIN){
        //動き
        t += normDelta(deltaT, NORMDELTA);
        keybindPanel((WINDOW_WIDTH+200) - easeOutBack(t) * KEYBIND_SHOW_WIDTH, 0);
        if(t >= 1){
            keybindStat = OPEN;
            t = 0;
        }
    }
    else if(keybindStat == OPEN){
        keybindPanel((WINDOW_WIDTH+200) - KEYBIND_SHOW_WIDTH, 0);
        if(isShowKeybind){
            keybindStat = EOUT;
        }
    }
    else if(keybindStat == EOUT){
        t += normDelta(deltaT, NORMDELTA);
        keybindPanel((WINDOW_WIDTH+200) - KEYBIND_SHOW_WIDTH + easeOutBack(t) * KEYBIND_SHOW_WIDTH, 0);
        if(t >= 1){
            keybindStat = CLOSE;
            isShowKeybind = 0;
            t = 0;
        }
    }
}
