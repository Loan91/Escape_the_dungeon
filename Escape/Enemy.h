#pragma once
#include "Entity.h"
#include "includes.h"
class Enemy : public Entity
{
protected:
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Vector2f position;
	float speed;
public:
	Enemy(float width, float height, Vector2f startPosition, float startSpeed);
	void setTexture(const sf::Texture& texture);
	void update(float deltaTime, const Map& map) override = 0;
	void draw(sf::RenderWindow& window) override;

	FloatRect getBounds() const;
};