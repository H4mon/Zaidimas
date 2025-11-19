#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball : public sf::CircleShape {
public:
	sf::Vector2f velocity;
	bool isStuck;

public:
	Ball();
	void update(sf::Time deltaTime);
	void launch();
	void followPaddle(const Paddle& paddle);
	void setLaunchDirection(int dir);
	int getLaunchDirection() const;

private:
	int launchDirX; 
};
