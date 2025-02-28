#include "mysteryship.h"

Mysteryship::Mysteryship()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

Mysteryship::~Mysteryship()
{
    UnloadTexture(image);
}

void Mysteryship::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if(side == 0){
        position.x = 0;
        speed = 3;
    }
    else{
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    alive = true;
}   

void Mysteryship::Update()
{
    if(alive){
        position.x += speed;
        if(position.x < 0 || position.x > GetScreenWidth() - image.width){
            alive = false;
        }
    }
}

void Mysteryship::Draw()
{
    if(alive){
        DrawTextureV(image, position, WHITE);
    }
}
