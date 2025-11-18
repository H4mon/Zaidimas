#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Brick : public sf::RectangleShape {
private:
	bool isDestroyed;

public:
	Brick(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	void hit();
	bool getIsDestroyed() const;
};

class BrickGrid : public sf::Drawable {
private:
	std::vector<Brick> bricks;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	BrickGrid();
	void checkCollision(Ball& ball);
	bool allBricksDestroyed() const;
	void reset();
};