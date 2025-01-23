#include "Enemy.h"

Enemy::Enemy(float width, float height, Vector2f startPosition, float startSpeed) : position(startPosition), speed(startSpeed)
{
	shape1.setSize({ width, height });
	shape1.setPosition(startPosition);
	shape1.setFillColor(Color::Red);
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(shape1);
}

FloatRect Enemy::getBounds() const
{
	return shape1.getGlobalBounds();
}