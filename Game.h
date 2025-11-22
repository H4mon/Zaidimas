#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "BrickGrid.h"
#include <fstream>

class Game {
private:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    BrickGrid bricks;

    enum GameState {START, PLAYING, LOSE, WIN, PAUSE};
    GameState currentState;

    int score;
    int lives;
    int highScore;
    sf::Text scoreText;
    sf::Text livesText;
	sf::Text highScoreText;
    sf::Text messageText;
    sf::Text pauseText;
    sf::Font font;
    bool gameRunning;
    
    void events();
    void update(sf::Time deltaTime);
    void draw();
    void resetGame();
    void drawStart();
    void drawLose();
    void drawWin();
	void drawPause();
	void loadHighScore();
	void saveHighScore();
	void updateHighScore();

public:
    Game();
    void run();
};