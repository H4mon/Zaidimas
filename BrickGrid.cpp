#include "BrickGrid.h"
#include <random>

Brick::Brick(sf::Vector2f position, sf::Vector2f size, sf::Color color, int hitsNeeded) : isDestroyed(false), HP(hitsNeeded), is2HP(hitsNeeded == 2) {
	setPosition(position);
	setSize(size);
	setFillColor(color);
	setOutlineColor(sf::Color::White);
	setOutlineThickness(1);

	if (is2HP) {
		setOutlineThickness(-3);
	}
	else {
		setOutlineThickness(-1);
	}

}
void Brick::hit() {
	HP--;

	if(is2HP && HP == 1) {
		setOutlineThickness(-1);
	}

	if (HP <= 0) {
		isDestroyed = true;
	}
}
bool Brick::getIsDestroyed() const {
	return isDestroyed;
}

int Brick::getHP() const {
	return HP;
}

bool Brick::getis2HP() const {
	return is2HP;
}

BrickGrid::BrickGrid() {
	sf::Vector2f brickSize(70, 30);
	sf::Color colors[] = {
		sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta
	};

	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	for (int row = 0; row < 5; ++row) {
			for(int col=0; col<10; ++col) {
			sf::Vector2f position(col * (brickSize.x + 5) + 25, row * (brickSize.y + 5) + 50);

			int hitsNeeded = (dist(rng) < 0.3f) ? 2 : 1;

			bricks.emplace_back(position, brickSize, colors[row % 5], hitsNeeded);
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
int BrickGrid::checkCollision(Ball& ball) {
	int score = 0;
	bool collide = false;
	for (auto& brick : bricks) {
		if (!brick.getIsDestroyed() && ball.getGlobalBounds().intersects(brick.getGlobalBounds())) {
			brick.hit();

			if (brick.getIsDestroyed()) {
				score += 10;
			}
			else {
				score += 10;
			}
			collide = true;
			break;
		}
	}
	if (collide) {
		ball.velocity.y = -ball.velocity.y;
	}
	return score;
}
bool BrickGrid::allBricksDestroyed() const {
	for (const auto& brick : bricks) {
		if (!brick.getIsDestroyed()) {
			return false;
		}
	}
	return true;
}
void BrickGrid::reset() {
	bricks.clear();

	sf::Vector2f brickSize(70, 30);
	sf::Color colors[] = {
		sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta
	};

	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	for (int row = 0; row < 5; ++row) {
		for (int col = 0; col < 10; ++col) {
			sf::Vector2f position(col * (brickSize.x + 5) + 25, row * (brickSize.y + 5) + 50);

			int hitsNeeded = (dist(rng) < 0.3f) ? 2 : 1;

			bricks.emplace_back(position, brickSize, colors[row % 5], hitsNeeded);
		}
	}
}