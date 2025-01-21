#pragma once
#include "includes.h"
#include "Map.h"

class Entity
{
public:
	virtual void update(float deltaTime, const Map& map) = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
};

