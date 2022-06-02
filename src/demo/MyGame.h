
#ifndef MYGAME_H_
#define MYGAME_H_

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <stdio.h>

#include "MyBoard.h"
#include "MyPaddle.h"
#include "MyBall.h"

#define FPS_DELAY 500

class MyGame {
public:
    MyGame();
    ~MyGame();

    void Run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* texture;

    // Timing
    unsigned int lasttick, fpstick, fps, framecount;

    // Test
    float testx, testy;

    MyBoard* board;
    MyPaddle* paddle;
    MyBall* ball;
    bool paddlestick;

  
    void Update(float delta);
    void Render(float delta);

    void NewGame();
    void ResetPaddle();
    void StickBall();

    void SetPaddleX(float x);
    void CheckBoardCollisions();
    float GetReflection(float hitx);
    void CheckPaddleCollisions();
    void CheckBrickCollisions();
    void CheckBrickCollisions2();    
    void BallBrickResponse(int directionindex);
    int GetBrickCount();
};

#endif
