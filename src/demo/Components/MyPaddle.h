#ifndef MYPADDLE_H_
#define MYPADDLE_H_

#include "MyEntity.h"

class MyPaddle: public MyEntity {
public:
    MyPaddle(SDL_Renderer* renderer);
    ~MyPaddle();

    void Update(float delta);
    void Render(float delta);

private:
    SDL_Texture* texture;
};

#endif
