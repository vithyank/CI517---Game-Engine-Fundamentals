#include "MyEntity.h"

MyEntity::MyEntity(SDL_Renderer* renderer) {
    this->renderer = renderer;

    x = 0;
    y = 0;
    width = 1;
    height = 1;
}

MyEntity::~MyEntity() {
}

void MyEntity::Update(float delta) {
}

void MyEntity::Render(float delta) {
}

bool MyEntity::Collides(MyEntity* other) {
    if (x + width > other->x && x < other->x + other->width &&
        y + height > other->y && y < other->y + other->height) {
        return true;
    }
    return false;
}
