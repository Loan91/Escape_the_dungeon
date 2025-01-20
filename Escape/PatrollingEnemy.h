#pragma once
#include "Enemy.h"
class PatrollingEnemy : public Enemy
{
private: 
	Vector2f startPoint;
	Vector2f endPoint;
	bool movingToEnd;
public:
	PatrollingEnemy(float width, float height, Vector2f startPoint, Vector2f endPoint, float speed);
	void update(float deltaTime) override;
};

