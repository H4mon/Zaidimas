#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "BrickGrid.h"

class Game {
private:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    BrickGrid bricks;

    int score;
    int lives;
    bool gameRunning;
    
    void events();
    void update(sf::Time deltaTime);
    void draw();
    void resetGame();

public:
    Game();
    void run();
};