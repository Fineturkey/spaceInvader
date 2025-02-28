#pragma once 
#include <raylib.h>

class Alien {
    public:
    Alien(int type, Vector2 position);
        void Draw();
        void Update(int direction);
        int GetType(); 
        static void UnLoadImages(); 
        Rectangle getRect();
        static Texture2D alienImages[3];
        int type;
        Vector2 position;
    private:
};