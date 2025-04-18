#pragma once
#include "Enemy.h"
#include "Player.h"
#include "includes.h"
class ChaserEnemy : public Enemy
{
private:
	Player& target;
public:
	ChaserEnemy(float width, float height, Vector2f startPosition, float startSpeed, Player& target, const sf::Texture& texture);
	void update(float deltaTime, const Map& map) override;
};