#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Brick : public sf::RectangleShape {
private:
	bool isDestroyed;
	int HP;
	bool is2HP;

public:
	Brick(sf::Vector2f position, sf::Vector2f size, sf::Color color, int hitsNeeded);
	void hit();
	bool getIsDestroyed() const;
	int getHP() const;
	bool getis2HP() const;
};

class BrickGrid : public sf::Drawable {
private:
	std::vector<Brick> bricks;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	BrickGrid();
	int checkCollision(Ball& ball);
	bool allBricksDestroyed() const;
	void reset();
};