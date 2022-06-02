

#include "MyBoard.h"

MyBoard::MyBoard(SDL_Renderer* renderer): Entity(renderer) {
    SDL_Surface* surface = IMG_Load("breakbricks.png");
    bricktexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("border.png");
    sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    srand(time(0));

    x = 16;
    y = 0;
    width = 768;
    height = 600;

    bricksoffsetx = 0;
    bricksoffsety = 16;
}

Board::~Board() {
  
    SDL_DestroyTexture(bricktexture);
    SDL_DestroyTexture(sidetexture);
}

void Board::Update(float delta) {

}

void Board::Render(float delta) {
    // Render bricks
    for (int i=0; i<MYBOARD_WIDTH; i++) {
        for (int j=0; j<MYBOARD_HEIGHT; j++) {
            Brick brick = bricks[i][j];

            // Check if the brick exists
            if (!brick.state)
                continue;

            SDL_Rect srcrect;

            srcrect.x = (brick.type % 2) * BOARD_BRICKSWIDTH;
            srcrect.y = (brick.type / 2) * BOARD_BRICKSHEIGHT;
            srcrect.w = BOARD_BRWIDTH;
            srcrect.h = BOARD_BRHEIGHT;

            SDL_Rect dstrect;
            dstrect.x = bricksoffsetx + x + i * BOARD_BRICKSWIDTH;
            dstrect.y = bricksoffsety + y + j * BOARD_BRICKSHEIGHT;
            dstrect.w = BOARD_BRICKSWIDTH;
            dstrect.h = BOARD_BRICKSHEIGHT;

            SDL_RenderCopy(renderer, bricktexture, &srcrect, &dstrect);
        }
    }


    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 16;
    dstrect.h = 600;
    SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);

    dstrect.x = 800 - 16;
    dstrect.y = 0;
    dstrect.w = 16;
    dstrect.h = 600;
    SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);
}


//simple level creator
void Board::CreateLevel() {
    for (int i=0; i<MYBOARD_WIDTH; i++) {
        for (int j=0; j<MYBOARD_HEIGHT; j++) {
            Brick brick;

            brick.type = rand() % 4;    
            
            brick.state = true;         
            bricks[i][j] = brick;
        }
    }
}
