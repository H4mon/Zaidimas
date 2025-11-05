#pragma once
#include <SFML/Graphics.hpp>

class Paddle : public sf::RectangleShape {
private:
	float speed;

public:
	Paddle();
	void update();
};