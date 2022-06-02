#ifndef MYBOARD_H_
#define MYBOARD_H_

#include "Entity.h"
#include <stdlib.h>
#include <time.h>


#define MYBOARD_WIDTH 12
#define MYBOARD_HEIGHT 12
#define MYBOARD_BRICKSWIDTH 64
#define MYBOARD_BRICKSHEIGHT 24

class Brick {
public:
    int type;
    bool state;
};

class MyBoard: public Entity {
public:
    MyBoard(SDL_Renderer* renderer);
    ~MyBoard();

    void Update(float delta);
    void Render(float delta);
    void CreateLevel();

    float bricksoffsetx, bricksoffsety;

 
    Brick bricks[BOARD_WIDTH][BOARD_HEIGHT];

private:
    SDL_Texture* bricktexture;
    SDL_Texture* sidetexture;
};

#endif
