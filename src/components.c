#include <string.h>
#include <stdio.h>
#include "opengl.h"
#include "define.h"
#include "primitive.h"
#include "components.h"
#include "keyboard.h"

unsigned int selectedGadget = 0;
unsigned int btop = 0;

#define NUM_GADGET 5
//                  idx  disp_name  desc            isAddr
gadget_t gadget[] = {
                    {0, "0x401aa0", "A",             1},
                    {1, "0x401bb0", "B",             1},
                    {2, "0x401027", "pop rdi; ret;", 1},
                    {3, "1",        "1",             0},
                    {4, "2",        "2",             0},
                    };

/*
 * answer[0]は一番下
 * answer[n-1]は一番上
 * ansercheckは一番上からチェックしていく
 * */
#define ANSWER_GADGET 6
char answer[][0x18] = { "0x401bb0", "2", "0x401027", "0x401aa0", "1", "0x401027" };

char textFieldGadget[ANSWER_GADGET][0x100];

block_t block[ANSWER_GADGET];

void
Block(vec2 pos, char *str){
    glColor3ub(70,70,70);
    Rect(pos.x, pos.y, BLOCK_WIDTH, BLOCK_HEIGHT);
    glColor3ub(255,255,255);
    inBlockText(pos, str);
}

void
inBlockText(vec2 pos, const char *str){
    centerTextROMAN24(pos.x + (BLOCK_WIDTH/2), pos.y + (BLOCK_HEIGHT/2) + (BLOCK_HEIGHT/16), str);
}

void
textField(){
    glColor3ub(70, 70, 70);
    Rect(WINDOW_PADDING, TEXTFIELD_TOP, (WINDOW_WIDTH)/2 - 2*WINDOW_PADDING, 500);
}

/*
 * challDesc
 * どのような関数に相当するROPを構築するかを提示
 * challDescriptionの中の文字列に
 * 相当する関数についてROPを組む
 * */
void
challDesc(){
    char challDescription[] = "A(1); B(2);";

    glColor4ub(240, 120, 100, 100);
    Rect(WINDOW_PADDING, WINDOW_PADDING*2, WINDOW_WIDTH/2 - WINDOW_PADDING*2, TEXTFIELD_TOP - 150);
    glColor3ub(0, 0, 0);
    centerTextROMAN24(WINDOW_WIDTH/4, TEXTFIELD_TOP - 100, challDescription);
}

/*
 * textFrame
 * 選択されているgadgetにフレーム
 * */
void
textFrame(char* str){
    // reddish
    glColor3ub(200, 0, 0);
    int len = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)str);
    frame(TEXTFIELD_PADDING-10, TEXTFIELD_TOP + (TEXTFIELD_PADDING - 24) + selectedGadget*40, len + 30, 30);
}

/*
 * drawTextGadgets
 * */
void
drawTextGadgets(){
    textField();
    for(int i = 0; i < NUM_GADGET; i++){
        if(gadget[i].isAddr){
            sprintf(textFieldGadget[i], "%d. %s : %s", gadget[i].idx + 1, gadget[i].addr, gadget[i].mem);
        } else {
            sprintf(textFieldGadget[i], "%d. %s", gadget[i].idx + 1, gadget[i].mem);
        }
        glColor3ub(255, 255, 255);
        Text(TEXTFIELD_PADDING, TEXTFIELD_TOP + TEXTFIELD_PADDING + i*40, textFieldGadget[i], GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(isPressed('j')){
         selectedGadget += 1;
         selectedGadget %= NUM_GADGET;
    }
    if(isPressed('k')){
       if(selectedGadget == 0){
           selectedGadget = (NUM_GADGET-1) - selectedGadget;
       } else {
           selectedGadget -= 1;
       }
    }
    textFrame(textFieldGadget[selectedGadget]);
}

void
copyGadgetToBlock(){
    strcpy(block[btop].s, gadget[selectedGadget].addr);
    btop++; btop %= ANSWER_GADGET;
}

int
answerCheck() {
    for(int i = ANSWER_GADGET-1; i >= 0; i--){
        printf("%s %s\n", block[i].s, answer[i]);
        if(strcmp(block[i].s, answer[i])){
            return -1;
        }
    }
    return 0;
}

void
initGadgets(){
    for(int i = 0; i < ANSWER_GADGET; i++){
        block[i].p.x = (WINDOW_WIDTH)/2;
        block[i].p.y = (TEXTFIELD_TOP + TEXTFIELD_OFS - BLOCK_HEIGHT/2) - i*(BLOCK_HEIGHT+10);
        strcpy(block[i].s, "");
    }
}

void
blockFrame(){
    glColor3ub(50, 100, 200);
    frame(block[btop].p.x, block[btop].p.y, BLOCK_WIDTH, BLOCK_HEIGHT);
}

void
drawBlocks(){
    for(int i = 0; i < ANSWER_GADGET; i++){
        Block(block[i].p, block[i].s);
    }
    blockFrame();
    glColor3ub(0, 0, 0);
    centerTextROMAN24(block[ANSWER_GADGET-1].p.x + BLOCK_WIDTH/2, block[ANSWER_GADGET-1].p.y - 40, "ROP START HERE v");
}

void
initBlock(){
    for(int i = 0; i < ANSWER_GADGET; i++){
        strcpy(block[i].s, "");
    }
    btop = 0;
}
