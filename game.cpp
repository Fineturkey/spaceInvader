#include "game.h"
#include <iostream>

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    LastAlienFire = 0;
    mysteryship.Spawn();
    timeLastSpawn = 0;
    mysteryshipSpawnInterval = GetRandomValue(10, 20);
}
Game::~Game()
{
    Alien::UnLoadImages();
}

void Game::Update()
{

    double currentTime = GetTime();
    if(currentTime - timeLastSpawn > mysteryshipSpawnInterval){
        mysteryship.Spawn();
        timeLastSpawn = GetTime();
        mysteryshipSpawnInterval = GetRandomValue(10, 20);
    }

    for(auto& laser: spaceship.lasers){
        laser.Update();
    }

    MoveAliens();
    AlienShootLaser();

    for(auto& laser: alienLasers){
        laser.Update();
    }
    DeleteInactiveLasers();
    mysteryship.Update();
}
void Game::Draw()
{
    spaceship.Draw();
    for(auto& laser: spaceship.lasers){
        laser.Draw();
    }

    for(auto& obstacle: obstacles){
        obstacle.Draw();
    }

    for(auto& alien: aliens){
        alien.Draw();
    }

    for(auto& laser: alienLasers){
        laser.Draw();
    }

    mysteryship.Draw();  
}

void Game::HandleInput(){
    if(IsKeyDown(KEY_LEFT)){
        spaceship.MoveLeft();
    }
    else if(IsKeyDown(KEY_RIGHT)){
        spaceship.MoveRight();
    }
    else if(IsKeyDown(KEY_SPACE)){
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if(!it -> active){
            it = spaceship.lasers.erase(it);
        }
        else{
            it++;
        }
    }
    for(auto it = alienLasers.begin(); it != alienLasers.end();){
        if(!it -> active){
            it = alienLasers.erase(it);
        }
        else{
            it++;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - obstacleWidth * 4) / 5;

    for(int i = 0; i < 4; i++){
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 11; col++){

            int alienType;
            if(row == 0){
                alienType = 2;
            }
            else if(row == 1 || row == 2){
                alienType = 1;
            }
            else{
                alienType = 3;
            }
            float x = 75 + col * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }

    return aliens;
}

void Game::MoveAliens()
{
    for(auto& alien: aliens){
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()){
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if(alien.position.x <0){
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens){
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if(currentTime - LastAlienFire >= alienLaserShootInterval && !aliens.empty()){
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width/2,
                                    alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        LastAlienFire = GetTime();
    }
}
