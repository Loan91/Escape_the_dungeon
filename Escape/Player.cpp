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

void Player::update(float deltaTime)
{
	handleInput(deltaTime);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}