#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    BrickGrid bricks;
    
    void events();
    void update(sf::Time deltaTime);
    void draw();

public:
    Game();
    void run();
};