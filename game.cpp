#include "Game.h"
#include <SFML/Window/Keyboard.hpp>

Game::Game() : window(sf::VideoMode(800, 600), "Breakout") {

	static sf::Font font;
	if(font.getInfo().family.empty()) {
		font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	}
	lives = 3;
	livesText.setFont(font);
	livesText.setString("Lives: 3");
	livesText.setCharacterSize(24);
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(650, 10);


	resetGame();
}

void Game::resetGame() {
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
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
			if (gameRunning) {
			ball.launch();
		}
			else {
				resetGame();
			}
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
			resetGame();
		}
		}
}

void Game::update(sf::Time deltaTime) {
	paddle.update(deltaTime);
	bricks.checkCollision(ball);

	if (ball.isStuck) {
		ball.followPaddle(paddle);
	}
	else {
		ball.update(deltaTime);
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
			lives = 0;
			gameRunning = false;
		}
	}

	livesText.setString("Lives: " + std::to_string(lives));

	if (bricks.allBricksDestroyed()) {
		resetGame();
	}
}

void Game::draw() {
		window.clear(sf::Color::Black);
		window.draw(paddle);
		window.draw(ball);
		window.draw(bricks);
		window.draw(livesText);
		window.display();
}
