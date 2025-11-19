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

    enum GameState {START, PLAYING, LOSE, WIN};
    GameState currentState;

    int score;
    int lives;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text messageText;
    sf::Font font;
    bool gameRunning;
    
    void events();
    void update(sf::Time deltaTime);
    void draw();
    void resetGame();
    void drawStart();
    void drawLose();
    void drawWin();

public:
    Game();
    void run();
};