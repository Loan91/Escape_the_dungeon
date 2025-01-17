#pragma once
#include "Enemy.h"
#include "Player.h"
class ChaserEnemy : public Enemy
{
private:
	Player& target;
public:
	ChaserEnemy(float width, float height, Vector2f startPosition, float startSpeed, Player& target);
	void update(float deltaTime) override;
};

