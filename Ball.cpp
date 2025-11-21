#include "Ball.h"

Ball::Ball() {
	setRadius(10);
	setFillColor(sf::Color::Red);
	setPosition(390, 530);
	velocity = sf::Vector2f(0, 0);
	isStuck = true;
	launchDirX = 1;
}

void Ball::setLaunchDirection(int dir) {
	launchDirX = dir;
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
		velocity = sf::Vector2f(250.f*(launchDirX), -250.f);
	}
}

void Ball::followPaddle(const Paddle& paddle) {
	if (isStuck) {
		float paddleCenterX = paddle.getPosition().x + paddle.getSize().x / 2;
		float ballX = paddleCenterX - getRadius();
		setPosition(ballX, paddle.getPosition().y - getRadius() * 2);
	}
}