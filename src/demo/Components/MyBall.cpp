#include "MyBall.h"

MyBall::MyBall(SDL_Renderer* renderer): Entity(renderer) {
    SDL_Surface* surface = IMG_Load("bounceball.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

  
    width = 24;
    height = 24;
    x = 0;
    y = 0;

    SetDirection(1, 1);
}

MyBall::~MyBall() {
   
    SDL_DestroyTexture(texture);
}

void MyBall::Update(float delta) {
    x += directionx * delta;
    y += directiony * delta;
}

void MyBall::Render(float delta) {
    SDL_Rect rect;
    rect.x = (int)(x + 0.5f);
    rect.y = (int)(y + 0.5f);
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(renderer, texture, 0, &rect);
}

void MyBall::SetDirection(float directionx, float directiony) {
    
    float length = sqrt(directionx * directionx + directiony * directiony);
    this->directionx = BALL_VELOCITY * (directionx / directionlength);
    this->directiony= BALL_VELOCITY * (directiony / length);
}
