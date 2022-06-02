#include "MyGame.h"

MyGame::MyGame() {
    window = 0;
    renderer = 0;
}

MyGame::~MyGame() {

}

bool MyGame::Init() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("BrickBreaker",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) {
        std::cout << "Error" << SDL_GetError() << std::endl;
        return false;
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Error" << SDL_GetError() << std::endl;
        return false;
    }


void MyGame::Run() {
    board = new MyBoard(renderer);
    paddle = new MyPaddle(renderer);
    ball = new MyBall(renderer);

    NewGame();

    // Main loop
    while (1) {
        // Handler events
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        // Update and render the game
        Update(delta);
        Render(delta);
    }

    delete board;
    delete paddle;
    delete ball;

    Clean();

    SDL_Quit();
}

void MyGame::NewGame() {
    board->CreateLevel();
    ResetPaddle();
}

void MyGame::ResetPaddle() {
    paddlestick = true;
    StickBall();
}

void MyGame::StickBall() {
    ball->x = paddle->x + paddle->width/2 - ball->width/2;
    ball->y = paddle->y - ball->height;
}

void MyGame::Update(float delta) {

    if (mstate&SDL_BUTTON(1)) {
        if (paddlestick) {
            paddlestick = false;
            ball->SetDirection(1, -1);
        }
    }

    if (paddlestick) {
        StickBall();
    }

    CheckBoardCollisions();
    CheckPaddleCollisions();
    CheckBrickCollisions2();

    if (GetBrickCount() == 0) {
        NewGame();
    }

    board->Update(delta);
    paddle->Update(delta);

    if (!paddlestick) {
        ball->Update(delta);
    }
}

void MyGame::SetPaddleX(float x) {
    float newx;
    if (x < board->x) {
   
        newx = board->x;
    } else if (x + paddle->width > board->x + board->width) {
      
        newx = board->x + board->width - paddle->width;
    } else {
        newx = x;
    }
    paddle->x = newx;
}

void MyGame::CheckBoardCollisions() {

    if (ball->y < board->y) {
   
        ball->y = board->y;
        ball->directiony *= -1;
    } else if (ball->y + ball->height > board->y + board->height) {

        ResetPaddle();
    }

    if (ball->x <= board->x) {
     
        ball->x = board->x;
        ball->directionx *= -1;
    } else if (ball->x + ball->width >= board->x + board->width) {
        
        ball->x = board->x + board->width - ball->width;
        ball->directionx *= -1;
    }
}

float MyGame::GetReflection(float hitx) {
 
    if (hitx < 0) {
        hitx = 0;
    } else if (hitx > paddle->width) {
        hitx = paddle->width;
    }


    hitx -= paddle->width / 2.0f;


    return 2.0f * (hitx / (paddle->width / 2.0f));
}


void MyGame::CheckPaddleCollisions() {

    float ballcenterx = ball->x + ball->width / 2.0f;


    if (ball->Collides(paddle)) {
        ball->y = paddle->y - ball->height;
        ball->SetDirection(GetReflection(ballcenterx - paddle->x), -1);

    }
}

void MyGame::CheckBrickCollisions() {
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick = board->bricks[i][j];


            if (brick.state) {

                float brickx = board->brickoffsetx + board->x + i*BOARD_BRICKSWIDTH;
                float bricky = board->brickoffsety + board->y + j*BOARD_BRICKSHEIGHT;

           
                float w = 0.5f * (ball->width + BOARD_BRICKSWIDTH);
                float h = 0.5f * (ball->height + BOARD_BRICKSHEIGHT);
                float dx = (ball->x + 0.5f*ball->width) - (brickx + 0.5f*BOARD_BRWIDTH);
                float dy = (ball->y + 0.5f*ball->height) - (bricky + 0.5f*BOARD_BRHEIGHT);

                if (fabs(dx) <= w && fabs(dy) <= h) {

                    board->bricks[i][j].state = false;

                    float wy = w * dy;
                    float hx = h * dx;

                    if (wy > hx) {
                        if (wy > -hx) {
         
                            BallBrickResponse(3);
                        } else {

                            BallBrickResponse(0);
                        }
                    } else {

                            BallBrickResponse(2);
                        } else {
         
                            BallBrickResponse(1);
                        }
                    }
                    return;
                }
            }
        }
    }
}

void MyGame::CheckBrickCollisions2() {
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick = board->bricks[i][j];

         
            if (brick.state) {
                float brickx = board->brickoffsetx + board->x + i*BOARD_BRICKSWIDTH;
                float bricky = board->brickoffsety + board->y + j*BOARD_BRICKSHEIGHT;

                float ballcenterx = ball->x + 0.5f*ball->width;
                float ballcentery = ball->y + 0.5f*ball->height;

              
                float brickcenterx = brickx + 0.5f*BOARD_BRICKSWIDTH;
                float brickcentery = bricky + 0.5f*BOARD_BRICKSHEIGHT;

                if (ball->x <= brickx + BOARD_BRICKSWIDTH && ball->x+ball->width >= brickx && ball->y <= bricky + BOARD_BRICKSHEIGHT && ball->y + ball->height >= bricky) {
               
                    board->bricks[i][j].state = false;

                    
                    float ymin = 0;
                    if (bricky > ball->y) {
                        ymin = bricky;
                    } else {
                        ymin = ball->y;
                    }

                    float ymax = 0;
                    if (bricky+BOARD_BRHEIGHT < ball->y+ball->height) {
                        ymax = bricky+BOARD_BRHEIGHT;
                    } else {
                        ymax = ball->y+ball->height;
                    }

                    float ysize = ymax - ymin;

                    // Calculate xsize
                    float xmin = 0;
                    if (brickx > ball->x) {
                        xmin = brickx;
                    } else {
                        xmin = ball->x;
                    }

                    float xmax = 0;
                    if (brickx+BOARD_BRICKSWIDTH < ball->x+ball->width) {
                        xmax = brickx+BOARD_BRICKSWIDTH;
                    } else {
                        xmax = ball->x+ball->width;
                    }

                    float xsize = xmax - xmin;

           
                    if (xsize > ysize) {
                        if (ballcentery > brickcentery) {
                           
                            ball->y += ysize + 0.01f; 
                            BallBrickResponse(3);
                        } else {
                       
                            ball->y -= ysize + 0.01f; 
                            BallBrickResponse(1);
                        }
                    } else {
                        if (ballcenterx < brickcenterx) {
                   
                            ball->x -= xsize + 0.01f; 
                            BallBrickResponse(0);
                        } else {
                           
                            ball->x += xsize + 0.01f; 
                            BallBrickResponse(2);
                        }
                    }

                    return;
                }
            }
        }
    }
}

void MyGame::BallBrickResponse(int directionindex) {
   

 
    int mulx = 1;
    int muly = 1;

    if (ball->directionx > 0) {
      
        if (ball->directiony > 0) {
        
     
            if (directionindex == 0 || directionindex == 3) {
                mulx = -1;
            } else {
                muly = -1;
            }
        } else if (ball->directiony < 0) {
         
            if (directionindex == 0 || directionindex == 1) {
                mulx = -1;
            } else {
                muly = -1;
            }
        }
    } else if (ball->directionx < 0) {
      
        if (ball->directiony > 0) {
         
            if (directionindex == 2 || directionindex == 3) {
                mulx = -1;
            } else {
                muly = -1;
            }
        } else if (ball->directiony < 0) {
           
            if (directionindex == 1 || directionindex == 2) {
                mulx = -1;
            } else {
                muly = -1;
            }
        }
    }

    ball->SetDirection(mulx*ball->directionx, muly*ball->directiony);
}

int MyGame::GetBrickCount() {
    int brickcount = 0;
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick = board->bricks[i][j];
            if (brick.state) {
                brickcount++;
            }
        }
    }

    return brickcount;
}

void MyGame::Render(float delta) {
    SDL_RenderClear(renderer);

    board->Render(delta);
    paddle->Render(delta);
    ball->Render(delta);

    SDL_RenderPresent(renderer);
}
