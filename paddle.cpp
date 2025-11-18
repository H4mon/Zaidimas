#include "Paddle.h"
#include <SFML/Window/Keyboard.hpp>

Paddle::Paddle() {
	setSize(sf::Vector2f(100, 20));
	setFillColor(sf::Color::White);
	setPosition(350, 550);
	speed = 300;
}

void Paddle::update(sf::Time deltaTime) {

	float dSec = deltaTime.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		move(-speed * dSec, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		move(speed * dSec, 0);
	}

	if (getPosition().x < 0) setPosition(0, 550);
	if (getPosition().x > 700) setPosition(700, 550);
}