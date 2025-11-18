#include "Game.h"
#include <SFML/Window/Keyboard.hpp>

Game::Game() : window(sf::VideoMode(800, 600), "Breakout") {
	resetGame();
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
	ball.update(deltaTime);
	bricks.checkCollision(ball);

	if(ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
		ball.velocity.y = -abs(ball.velocity.y);
	}

	if (ball.getPosition().y>600) {
		lives--;
		if (lives > 0) {
			ball.setPosition(390, 530);
			ball.velocity = sf::Vector2f(0, 0);
			ball.isStuck = true;
		}
		else {
			gameRunning = false;
		}
	}

	if (bricks.allBricksDestroyed()) {
		resetGame();
	}
}

void Game::draw() {
		window.clear(sf::Color::Black);
		window.draw(paddle);
		window.draw(ball);
		window.draw(bricks);
		window.display();
}
