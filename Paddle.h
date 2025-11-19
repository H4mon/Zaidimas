#pragma once
#include <SFML/Graphics.hpp>

class Ball;

class Paddle : public sf::RectangleShape {
private:
	float speed;

public:
	Paddle();
	void update(sf::Time deltaTime, Ball& ball);
};