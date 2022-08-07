#pragma once
typedef struct Gadget {
    unsigned int idx;
    char addr[0x18];
    char mem[0x60];
    unsigned int isAddr;
} gadget_t;

void Block(vec2, char *);
void inBlockText(vec2, const char *);
void textField();
void challDesc();
void textFrame(char*);
void drawTextGadgets();
void copyGadgetToBlock();
void initGadgets();
int answerCheck();
void drawBlocks();
void initBlock();
