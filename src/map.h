#pragma once
#define MAP_ROW 10
#define MAP_CLOUMN 10
#define MASS_SIZE 32
#define MAP_WIDTH MAP_ROW*MASS_SIZE
#define MAP_HEIGHT MAP_CLOUMN*MASS_SIZE
#define MOVING_OFFSET 8
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define MAP_OFS_X (WINDOW_WIDTH/2)-(MAP_WIDTH/2)
#define MAP_OFS_Y (WINDOW_HEIGHT/2)-(MAP_HEIGHT/2)
#define MAP_BASE MAP_OFS_X
#define MAP_TOP MAP_BASE+MAP_ROW*MASS_SIZE
#define MAP_OUTOFRANGE_MIN_X MAP_OFS_X-MASS_SIZE
#define MAP_OUTOFRANGE_MAX_X MAP_OFS_X+MAP_WIDTH
#define MAP_OUTOFRANGE_MIN_Y MAP_OFS_Y-MASS_SIZE
#define MAP_OUTOFRANGE_MAX_Y MAP_OFS_Y+MAP_HEIGHT

#include "primitive.h"
typedef struct Player{
    vec2 pos;
    /*0:右, 1:下, 2:左, 3:上*/
    unsigned int arrow;
}player_t;

void loadCharacterImg();
void drawCharacter();
void drawMap();
int isPlayerOutOfDisp();
void fillAroundMap();
