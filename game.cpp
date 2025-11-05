3include "Game.h"
#include <SFML/Window/Keyboard.hpp>

Game::Game() : window(sf::VideoMode(800, 600), "Breakout") {
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
			ball.launch();
		}
		}
}

void Game::update() {
	paddle.update();
	ball.update();
}

void Game::draw() {
		window.clear(sf::Color::Black);
		window.draw(paddle);
		window.draw(ball);
		bricks.draw(bricks);
		window.display();
}
