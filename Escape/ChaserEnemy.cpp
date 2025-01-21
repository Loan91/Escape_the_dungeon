#include "ChaserEnemy.h"

ChaserEnemy::ChaserEnemy(float width, float height, Vector2f startPosition, float startSpeed, Player& target) : Enemy(width, height, startPosition, startSpeed), target(target) {}

void ChaserEnemy::update(float deltaTime, const Map& map)
{
	Vector2f direction = target.getPosition() - shape.getPosition();
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction = direction / length;
	}
	shape.move(direction * speed * deltaTime);

	Vector2f position = shape.getPosition();
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + shape.getSize().x > 1920) position.x = 1920 - shape.getSize().x;
	if (position.y + shape.getSize().y > 1080) position.y = 1080 - shape.getSize().y;
	shape.setPosition(position);
}


