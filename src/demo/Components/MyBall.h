#ifndef MYBALL_H_
#define MYBALL_H_

#include "MyEntity.h"

#include <math.h>

const float BALL_VELOCITY = 550;

class MyBall: public MyEntity {
public:
    MyBall(SDL_Renderer* renderer);
    ~MyBall();

    void Update(float delta);
    void Render(float delta);

    void SetDirection(float directionx, float directiony);

    float directionx, directiony;

private:
    SDL_Texture* texture;

};

#endif
