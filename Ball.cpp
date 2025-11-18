#include "Ball.h"

Ball::Ball() {
	setRadius(10);
	setFillColor(sf::Color::Red);
	setPosition(390, 530);
	velocity = sf::Vector2f(0, 0);
	isStuck = true;
}

void Ball::update(sf::Time deltaTime) {
	if (!isStuck) {
		float dSec = deltaTime.asSeconds();
		move(velocity*dSec);
	if (getPosition().x <= 0 || getPosition().x >= 780) {
		velocity.x = -velocity.x;
	}
	if (getPosition().y <= 0) {
		velocity.y = -velocity.y;
	}
}
}
void Ball::launch() {
	if (isStuck) {
		isStuck = false;
		velocity = sf::Vector2f(250, -250);
	}
}