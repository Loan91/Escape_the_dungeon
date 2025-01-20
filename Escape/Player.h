#pragma once
#include "includes.h"
#include "Entity.h"

class Player : public Entity
{
private:
	float speed;
	RectangleShape shape;
public: 
	Player(float width, float height, Vector2f startPosition, float startSpeed);
	void handleInput(float deltaTime);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	Vector2f getPosition() const
	{
		return shape.getPosition();
	}
	FloatRect getBounds() const
	{
		return shape.getGlobalBounds();
	}
	void increaseSpeed(float amount);
};

