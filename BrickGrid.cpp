#include "BrickGrid.h"

Brick::Brick(sf::Vector2f position, sf::Vector2f size, sf::Color color) : isDestroyed(false) {
	setPosition(position);
	setSize(size);
	setFillColor(color);
	setOutlineColor(sf::Color::White);
	setOutlineThickness(1);
}
void Brick::hit() {
	isDestroyed = true;
}
bool Brick::getIsDestroyed() const {
	return isDestroyed;
}

BrickGrid::BrickGrid() {
	sf::Vector2f brickSize(70, 30);
	sf::Color colors[] = {
		sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan
	};
	for (int row = 0; row < 5; ++row) {
			for(int col=0; col<10; ++col) {
			sf::Vector2f position(col * (brickSize.x + 5) + 25, row * (brickSize.y + 5) + 50);
			bricks.emplace_back(position, brickSize, colors[row % 6]);
				}
	}
}
void BrickGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& brick : bricks) {
		if (!brick.getIsDestroyed()) {
			target.draw(brick, states);
		}
	}
}
void BrickGrid::checkCollision(Ball& ball) {
	for (auto& brick : bricks) {
		if (!brick.getIsDestroyed() && ball.getGlobalBounds().intersects(brick.getGlobalBounds())) {
			brick.hit();
			break;
		}
	}
}
bool BrickGrid::allBricksDestroyed() const {
	for (const auto& brick : bricks) {
		if (!brick.getIsDestroyed()) {
			return false;
		}
	}
	return true;
}