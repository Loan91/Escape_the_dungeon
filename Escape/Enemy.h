#pragma once
#include "Entity.h"
#include "includes.h"
class Enemy : public Entity
{
protected:
	RectangleShape shape1;
	Vector2f position;
	float speed;
public:
	Enemy(float width, float height, Vector2f startPosition, float startSpeed);
	void update(float deltaTime, const Map& map) override = 0;
	void draw(sf::RenderWindow& window) override;

	FloatRect getBounds() const;
};