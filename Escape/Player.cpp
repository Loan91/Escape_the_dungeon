#include "Player.h"

Player::Player(float width, float height, Vector2f startPosition, float startSpeed) : speed(startSpeed)
{
	shape.setSize({ width, height });
	shape.setPosition(startPosition);
	shape.setFillColor(Color::Blue);
}

void Player::handleInput(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		shape.move(0.0f, -speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		shape.move(0.0f, speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		shape.move(-speed, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		shape.move(speed, 0.0f);
	}
}

void Player::increaseSpeed(float amount)
{
	speed += amount;
}

void Player::update(float deltaTime)
{
	handleInput(deltaTime);
	Vector2f position = shape.getPosition();
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + shape.getSize().x > 1920) position.x = 1920 - shape.getSize().x;
	if (position.y + shape.getSize().y > 1080) position.y = 1080 - shape.getSize().y;
	shape.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}