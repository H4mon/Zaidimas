#include "Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>

Game::Game() : window(sf::VideoMode(800, 600), "Breakout") {

	static sf::Font font;
	if(font.getInfo().family.empty()) {
		font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	}

	loadHighScore();

	lives = 3;
	livesText.setFont(font);
	livesText.setString("Lives: 3");
	livesText.setCharacterSize(24);
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(650, 10);

	score = 0;
	scoreText.setFont(font);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 10);

	highScoreText.setFont(font);
	highScoreText.setString("High Score: " + std::to_string(highScore));
	highScoreText.setCharacterSize(24);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setPosition(300, 10);

	currentState = START;

	messageText.setFont(font);
	messageText.setCharacterSize(24);
	messageText.setFillColor(sf::Color::White);
	messageText.setPosition(200, 250);

	pauseText.setFont(font);
	pauseText.setCharacterSize(30);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setString("PAUSED\n\nPress R to Restart\nPress E to Exit");
	pauseText.setPosition(250, 200);

	resetGame();
}

void Game::loadHighScore() {
	std::ifstream file("highscore.txt");
	if (file.is_open()) {
		file >> highScore;
	}
	else {
		highScore = 0;
	}
}

void Game::saveHighScore() {
	std::ofstream file("highscore.txt");
	if (file.is_open()) {
		file << highScore;
	}
}

void Game::updateHighScore() {
	if (score > highScore) {
		highScore = score;
		saveHighScore();
	}
}

void Game::resetGame() {
	score = 0;
	lives = 3;
	gameRunning = true;

	paddle.setPosition(350, 550);
	ball.setPosition(390, 530);
	ball.velocity = sf::Vector2f(0, 0);
	ball.isStuck = true;
	bricks = BrickGrid();
}

void Game::run() {
	sf::Clock clock;
		while (window.isOpen()) {
			sf::Time deltaTime = clock.restart();
		events();
		update(deltaTime);
		draw();
		}
}

void Game::events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed) {

			if (event.key.code == sf::Keyboard::Escape) {
				if (currentState == PLAYING) {
					currentState = PAUSE;
				}
				else if (currentState == PAUSE) {
					currentState = PLAYING;
				}
			}

			if (currentState == START || currentState == LOSE || currentState == WIN) {

				if (event.key.code == sf::Keyboard::Space) {
					resetGame();
					currentState = PLAYING;
				}
			}

			else if (currentState == PLAYING) {
				if (event.key.code == sf::Keyboard::Space) {
					ball.launch();
				}
			}
			else if (currentState == PAUSE) {
				if (event.key.code == sf::Keyboard::E) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::R) {
					resetGame();
					currentState = PLAYING;
				}
			}
		}
	}
}

void Game::update(sf::Time deltaTime) {

	if (currentState != PLAYING) return;

	paddle.update(deltaTime, ball);

	if (ball.isStuck) {
		ball.followPaddle(paddle);
	}
	else {
		ball.update(deltaTime);
		score += bricks.checkCollision(ball);
	}

	if(ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
		ball.velocity.y = -abs(ball.velocity.y);
	}

	if (ball.getPosition().y>600) {
		lives--;
		if (lives > 0) {
			paddle.setPosition(350, 550);
			ball.velocity = sf::Vector2f(0, 0);
			ball.isStuck = true;
			ball.followPaddle(paddle);
		}
		else {
			updateHighScore();
			currentState = LOSE;
		}
	}
	scoreText.setString("Score: " + std::to_string(score));
	livesText.setString("Lives: " + std::to_string(lives));
	highScoreText.setString("High Score: " + std::to_string(highScore));

	if (bricks.allBricksDestroyed()) {
		updateHighScore();
		currentState = WIN;
	}
}

void Game::drawPause() {
	sf::RectangleShape overlay(sf::Vector2f(800, 600));
	overlay.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(overlay);
	window.draw(pauseText);
}

void Game::drawStart() {
	messageText.setString("BREAKOUT\n\nPress SPACE to start");
	messageText.setPosition(250, 200);
	window.draw(messageText);
}
void Game::drawLose() {
	messageText.setString("GAME OVER\n\nFinal Score: "+std::to_string(score)+"\n\nPress SPACE to play again");
	messageText.setPosition(200, 200);
	window.draw(messageText);
}
void Game::drawWin() {
	messageText.setString("YOU WIN!\n\nFinal Score: " + std::to_string(score) + "\n\nPress SPACE to play again");
	messageText.setPosition(250, 200);
	window.draw(messageText);
}

void Game::draw() {

	window.clear(sf::Color::Black);

	if (currentState == START) drawStart();
	else if (currentState == PLAYING) {
		window.draw(paddle);
		window.draw(ball);
		window.draw(bricks);
		window.draw(scoreText);
		window.draw(livesText);
		window.draw(highScoreText);
	}
	else if (currentState == LOSE) drawLose();
	else if (currentState == WIN) drawWin();
	else if (currentState == PAUSE) {
		window.draw(paddle);
		window.draw(ball);
		window.draw(bricks);
		window.draw(scoreText);
		window.draw(livesText);
		window.draw(highScoreText);
		drawPause();
	}

	window.display();
}
