
#include "Main.h"

int main(int argc, char* argv[]) {

    MyGame* game = new MyGame();

 
    if (game->Init()) {
        game->Run();
    }

    delete game;
    return 0;
}
