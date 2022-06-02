
#ifndef MYENTITY_H_
#define MYENTITY_H_

#include "SDL.h"
#include "SDL_image.h"

class MyEntity {
public:
    MyEntity(SDL_Renderer* renderer);
    virtual ~MyEntity();

    float x, y, width, height;

    virtual void Update(float delta);
    virtual void Render(float delta);

    bool Collides(MyEntity* other);
protected:
    SDL_Renderer* renderer;

};

#endif
