#include "Enemy.h"

Enemy::Enemy(float width, float height, Vector2f startPosition, float startSpeed) : position(startPosition), speed(startSpeed)
{
	shape.setSize({ width, height });
	shape.setPosition(startPosition);
	shape.setFillColor(Color::Red);
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

FloatRect Enemy::getBounds() const
{
	return shape.getGlobalBounds();
}