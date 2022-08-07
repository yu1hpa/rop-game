#include <gl/glpng.h>
#include "opengl.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "primitive.h"
#include "define.h"
#include "components.h"
#include "deltatime.h"
#include "easing.h"
#include "keyboard.h"
#include "keybind.h"
#include "status.h"
#include "map.h"
#include "main.h"
#if EBUG
#include "debug.h"
#endif


unsigned int isStorePressed = 0;
unsigned int answerCheckFlag = 0;
unsigned int isCorrect = 0;
unsigned int isShowAnswerPanel = 0;
unsigned int isInit = 0;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("ROPchain TURTLE");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);

    //キャラクターの読み込み
    loadCharacterImg();

    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(0.94, 0.94, 0.94, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutTimerFunc(7, Timer, 0);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
    return 0;
}

void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    if(!isPlayerOutOfDisp()){
        drawMap();
        drawCharacter();
        fillAroundMap();
    }
    else {
        static Status isCorrectStat;
        static deltat_t deltaT;

        if(!isInit){
            isInit = 1;
            isCorrect = 0;
            isShowAnswerPanel = 0;
            initTime(&deltaT);
            getTime(&deltaT);
            initGadgets();
        }

        // デルタ時間の取得
        getTime(&deltaT);

        glClear(GL_COLOR_BUFFER_BIT);
        #if EBUG
        debugLine();
        debugLineH(WINDOW_HEIGHT/2);
        debugLineH(TEXTFIELD_TOP + TEXTFIELD_OFS + BLOCK_HEIGHT/2);
        debugLineV(WINDOW_WIDTH/4);
        #endif


        if(isPressed('b')){
           answerCheckFlag = 1;
        }

        glColor3ub(0, 0, 0);
        challDesc();

        if(answerCheckFlag){
            answerCheckFlag = 0;
            if(answerCheck() == -1){
                puts("incorrect");
            } else {
                isCorrect = 1;
                isShowAnswerPanel = 1;
                puts("correct");
            }
        }

        /*
         * 各gadgetをtextFieldに描画
         * */
        drawTextGadgets();

        /*
         * ブロックを描画
         * ブロック：四角形とgadgetのアドレス（または値）の組
         * */
        drawBlocks();

        if(!isCorrect){
            // gadgetをBlockにコピー
            if(isPressed('f')){
                copyGadgetToBlock();
            }
            showKeybind(deltaT);
            if(isPressed('q')){
                initBlock();
            }
        }
        else if(isCorrect){

            //半透明な白色の長方形
            glColor4ub(255, 255, 255, 125);
            Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

            //赤色
            glColor3ub(200, 0, 0);
            static double at = 0;
            if(isCorrectStat == CLOSE){
                glColor3ub(200, 200, 200);
                Text(0, 300, "Congratulation", GLUT_BITMAP_TIMES_ROMAN_24);
                if(isShowAnswerPanel){
                    isCorrectStat = EIN;
                    isShowAnswerPanel = 0;
                }
            }
            else if(isCorrectStat == EIN){
                at += normDelta(deltaT, NORMDELTA);
                centerTextROMAN24(easeInOutCirc(at)*WINDOW_WIDTH/2, WINDOW_HEIGHT/2, "Congratulation");
                if(at >= 1){
                    isCorrectStat = OPEN;
                    at = 0;
                }
            }
            else if(isCorrectStat == OPEN){
                centerTextROMAN24(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, "Congratulation");
                if(isShowAnswerPanel){
                    isCorrectStat = EOUT;
                }
            }

            if(isPressed('q')){
                exit(0);
            }
        }
    }
    glFlush();
}

void Reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScaled(1,-1,1);
    glTranslated(0, -h, 0);
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Timer(int v){
    glutPostRedisplay();
    glutTimerFunc(7, Timer, 0);
}

