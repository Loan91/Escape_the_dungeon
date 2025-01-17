#pragma once
#include "Entity.h"
class Enemy : public Entity
{
protected:
	RectangleShape shape;
	Vector2f position;
	float speed;
public:
	Enemy(float width, float height, Vector2f startPosition, float startSpeed);
	void update(float deltaTime) override = 0;
	void draw(sf::RenderWindow& window) override;

	FloatRect getBounds() const;
};

