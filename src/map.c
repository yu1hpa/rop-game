#include <stdio.h>
#include <gl/glpng.h>
#include "opengl.h"
#include "define.h"
#include "keyboard.h"
#include "map.h"
#include "primitive.h"

char map[MAP_CLOUMN][MAP_ROW] = {
    "0000000000",
    "0111111110",
    "0111111010",
    "0001100010",
    "0111110010",
    "0101111010",
    "0101111110",
    "0101000110",
    "0111111110",
    "0010000000",
};

GLuint characterPng[8];
pngInfo characterPngInfo[8];

player_t player = {
    //初期位置
    { MAP_OFS_X + MASS_SIZE, MAP_OFS_Y + MASS_SIZE },
    //方向
    1
                  };
int delayT = 0;
int fixedDlay = 20;

void
loadCharacterImg(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            char filename[0x30];
            sprintf(filename, "./character/%d-%d.png", i, j);
            characterPng[i+4*j] = pngBind(filename, PNG_NOMIPMAP, PNG_ALPHA, &characterPngInfo[i+4*j], GL_CLAMP, GL_NEAREST, GL_NEAREST);
        }
    }
}

void
drawRect(int x, int y){
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x, y+MASS_SIZE);
    glVertex2i(x+MASS_SIZE, y+MASS_SIZE);
    glVertex2i(x+MASS_SIZE, y);
    glEnd();
}

void
drawMap(){
    for (int i = 0; i < MAP_CLOUMN; i++) {
        for (int j = 0; j < MAP_ROW; j++) {
            if ('0' == map[i][j]) {
                glColor3ub(127, 100, 87);
                drawRect(MAP_OFS_X + MASS_SIZE*j, MAP_OFS_Y + MASS_SIZE*i);
            } else if ('1' == map[i][j]) {
                glColor3ub(80, 100, 80);
                drawRect(MAP_OFS_X + MASS_SIZE*j, MAP_OFS_Y + MASS_SIZE*i);
            }
        }
    }
}

void fillAroundMap(){
    glColor3ub(70, 70, 70);
    Rect(0, 0, MAP_OFS_X, WINDOW_HEIGHT);
    Rect(0, 0, WINDOW_WIDTH, MAP_OFS_Y);
    Rect(MAP_OFS_X + MAP_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    Rect(0, MAP_OFS_Y + MAP_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void
drawCharacter(){
    if (isPressed('j')){
        //                              MAP_OFS_X/MASS_SIZE
        int i = (player.pos.x/MASS_SIZE)-(352/32);
        //                              MAP_OFS_Y/MASS_SIZE
        int j = (player.pos.y/MASS_SIZE)-(224/32);
        if(player.pos.x % (MASS_SIZE) == 0 && map[j+1][i] != '0'){
            player.pos.y += MOVING_OFFSET;
        } else if(map[j+1][i] != '0' && map[j+1][i+1] != '0'){
            player.pos.y += MOVING_OFFSET;
        }
        player.arrow = 1;
    }
    if (isPressed('k')){
        //                              MAP_OFS_X/MASS_SIZE
        int i = (player.pos.x/MASS_SIZE)-(352/32);
        //                              MAP_OFS_Y/MASS_SIZE
        int j = ((player.pos.y-1)/MASS_SIZE)-(224/32);
        if(player.pos.x % (MASS_SIZE) == 0 && map[j][i] != '0'){
            player.pos.y -= MOVING_OFFSET;
        } else if(map[j][i] != '0' && map[j][i+1] != '0'){
            player.pos.y -= MOVING_OFFSET;
        }
        player.arrow = 3;
    }
    if (isPressed('l')){
        //                              MAP_OFS_X/MASS_SIZE
        int i = (player.pos.x/MASS_SIZE)-(352/32);
        //                              MAP_OFS_Y/MASS_SIZE
        int j = (player.pos.y/MASS_SIZE)-(224/32);
        if(player.pos.y % (MASS_SIZE) == 0 && map[j][i+1] != '0'){
            player.pos.x += MOVING_OFFSET;
        } else if(map[j][i+1] != '0' && map[j+1][i+1] != '0'){
            player.pos.x += MOVING_OFFSET;
        }
        player.arrow = 0;
    }
    if (isPressed('h')){
        //                              MAP_OFS_X/MASS_SIZE
        int i = ((player.pos.x-1)/MASS_SIZE)-(352/32);
        //                              MAP_OFS_Y/MASS_SIZE
        int j = (player.pos.y/MASS_SIZE) - (224/32);
        if(player.pos.y % (MASS_SIZE) == 0 && map[j][i] != '0'){
            player.pos.x -= MOVING_OFFSET;
        } else if(map[j][i] != '0' && map[j+1][i] != '0'){
            player.pos.x -= MOVING_OFFSET;
        }
        player.arrow = 2;
    }

    static int animetion = 0;
    PutSprite(characterPng[player.arrow+animetion*4], player.pos.x, player.pos.y, &characterPngInfo[player.arrow+animetion]);
    delayT++;
    if(delayT == fixedDlay) {
        animetion = 1 - animetion;
        delayT = 0;
    }
}

int isPlayerOutOfDisp(){
    if(player.pos.x <= MAP_OUTOFRANGE_MIN_X || player.pos.x >= MAP_OUTOFRANGE_MAX_X
            || player.pos.y <= MAP_OUTOFRANGE_MIN_Y || player.pos.y >= MAP_OUTOFRANGE_MAX_Y){
        return 1;
    }
    return 0;
}
