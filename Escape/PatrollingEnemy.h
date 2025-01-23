#pragma once
#include "Enemy.h"
#include "includes.h"
class PatrollingEnemy : public Enemy
{
private:
	Vector2f startPoint;
	Vector2f endPoint;
	bool movingToEnd;
public:
	PatrollingEnemy(float width, float height, Vector2f startPoint, Vector2f endPoint, float speed);
	void update(float deltaTime, const Map& map) override;
};