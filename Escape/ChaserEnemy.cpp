#include "ChaserEnemy.h"

ChaserEnemy::ChaserEnemy(float width, float height, Vector2f startPosition, float startSpeed, Player& target) : Enemy(width, height, startPosition, startSpeed), target(target) {}

void ChaserEnemy::update(float deltaTime)
{
	Vector2f direction = target.getPosition() - shape.getPosition();
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction = direction / length;
	}
	shape.move(direction * speed * deltaTime);
}


