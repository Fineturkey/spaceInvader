#include <raylib.h>
#include "game.h"


int main() {
    int windowWidth = 750;
    int windowHeight = 750;
    Color grey = {29, 29, 27, 255};

    InitWindow(windowWidth, windowHeight, "C++ Space Invaders");
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false) {

        game.HandleInput();

        game.Update();
        BeginDrawing();
        ClearBackground(grey);           
        game.Draw();
        EndDrawing();
    }

    CloseWindow(); 
}

//comment

